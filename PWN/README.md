# CTF WP-PWN

---


## PWN基础：

### 寄存器

例如，r 开头的为 64 位寄存器，如 0x00000000

`rax` `rbx` `rcx` `rdx` `rdi` `rsi` `rsp` `rbp` `rip`
`r8` `r9` `r10` `r11` `r12` `r13` `r14` `r15`
例如，e 开头的是 32 位寄存器，如 0x0000

`eax` `ebx` `ecx` `edx` `edi` `esi` `esp` `ebp` `eip`
其中 eax 是 rax 的低 4 字节，其它的以此类推。

### 数据类型

`1 字节` `BYTE`
`2 字节` `WORD`
`4 字节` `DWORD`
`8 字节` `QWORD`

### 基础汇编语句    

Intel 格式汇编语句的例子：

```
mov rax, 1           ; 将 rax 的值赋值为 1
mov rax, rdi         ; 将 rdi 存储的值赋值给 rax
mov rax, [0x404000]  ; 将 0x404000 存储的内容复制到 rax 里面
mov [rdx], rax       ; 将 rax 的值存储到 rdx 存储的指针指向的地方
```
除此之外比较类似的还有 add sub 等指令。
```
lea  rax, [rdx+0x10] ; 将 rdx+0x10 指针赋值给 rax
push rax             ; 将 rax 的值 push 到栈上面。
pop  rax             ; 将栈顶的值 pop 到 rax 寄存器里面。
```

### VELF 结构   

ELF 文件每个部分都是分段的。

IDA中，按下 `⇧ Shift` `F7` 即可查看

几个比较重要的段（Section）的作用：

- `.text` 段：存储程序的代码，具有可读可执行权限，不可写
- `.bss` 段：存储没有赋初值的全局变量，可读可写
- `.data` 段：存储已经赋初值的全局变量，可读可写
- `.rodata` 段：存储全局常量，比如常量字符串等，仅仅可读