
## 用于计算逻辑运算表达式的程序流程

### 算法流程：

```mermaid
graph LR
in(Infix Notion with var)--translate-->pnv(Postfix Notion with var)
pnv(Postfix Notion with var)--assign-->pn(Postfix Notion)
pn(Postfix Notion)--repeat-->pnv
pn(PostNotion)--cal-->tt(Truth Table)


```

### Infix Notion Concepts

#### variable

取值为`{true,false}`，由一个或者多个连续字母表示

合法变量：`p` , `q` , `var` , `ksks` , `ty`

不合法变量：`val1` (必须由纯字母构成), `v~ar`(必须由连续字母构成)



#### operator

一共有五种逻辑运算符： $\neg$, $\wedge$, $\lor$, $\rightarrow$, $\Leftrightarrow$ (逻辑非，逻辑合取，逻辑析取，单蕴含，双蕴含)

1. $\neg$

   单目运算符，优先级为**5**

   真值表：

   | $p$     | $\neg p$   |
   | --------- | --------- |
   | $True$  | $False$ |
   | $False$ | $True$  |

   

2. $\wedge$

   CON，合取运算符，双目运算符，优先级为**4**

   真值表：

   | $p$     | $q$     | $p\wedge q$ |
   | --------- | --------- | ------------- |
   | $True$  | $True$  | $True$      |
   | $True$  | $False$ | $False$     |
   | $False$ | $True$  | $False$     |
   | $False$ | $False$ | $False$     |

   

3. $\lor$

   DIS，析取运算符，双目运算符，优先级为**3**

   真值表：

   | $p$     | $q$     | $p\lor q$ |
   | --------- | --------- | ----------- |
   | $True$  | $True$  | $True$    |
   | $True$  | $False$ | $True$    |
   | $False$ | $True$  | $True$    |
   | $False$ | $False$ | $False$   |

   

4. $\rightarrow$

   双目运算符，优先级为**2**

   真值表：

   | $p$     | $q$     | $p \rightarrow q$ |
   | --------- | --------- | ------------------- |
   | $True$  | $True$  | $True$            |
   | $True$  | $False$ | $False$           |
   | $False$ | $True$  | $True$            |
   | $False$ | $False$ | $True$            |

   

5. $\Leftrightarrow$

   双目运算符，优先级为**1**

   真值表：

   | $p$     | $q$     | $p\wedge q$ |
   | --------- | --------- | ------------- |
   | $True$  | $True$  | $True$      |
   | $True$  | $False$ | $False$     |
   | $False$ | $True$  | $False$     |
   | $False$ | $False$ | $True$      |

   

6. $/bigoplus$



### Translate过程

使用逆波兰表达式过程：

准备工作：输出数组 $Output$，符号栈 $SignStack$，变量映射 $VarMap$，变量数组 $VarValue$,  $VarCnt$记录 $VarValue$大小

1. $Output$ 记录最后的逆波兰表达式，在逆波兰表达式中，仅有符号 $Sign$和变量 $Variable$
2. $SignStack$ 用于储存 $operator$
3. $VarMap$，将变量的名字映射到 $VarValue$的一个位置上。同名的变量映射的位置相同，不同名变量映射位置不同。在后续的 $assign$步骤中，variable的值从 $VarValue[VarMap[VariableName]]$中取出
4. $VarValue$，用来存储<u>不同变量</u>的值，顺序储存

 $Variable$类型要求具有：$VarName$名字

 $Operator$类型要求具有：$Priority$优先级，具体类型（左括号/右括号）

逆波兰表达式详细过程：

从左向右依次扫描逐个元素

1. 如果是变量名：
   1. 检查是否有同名变量( $VarMap[VarName]是否为0$)
      1. 如果没有则在 $VarValue$开辟一块新位置， $VarCnt++$，并将其与 $VarMap$绑定( $VarMap[VarName]=VarCnt$)
      2. 如果存在，则不做任何操作
   2. 直接将该元素输出到 $Output$中
2. 如果是符号：
   1. 如果是左括号，直接入栈
   2. 如果是右括号， $SignStack$将栈顶元素一直输出到 $Output$中，直到遇到左括号并将其抵消
   3. 若是其他操作符，将栈顶所有**优先级不小于该操作符**的元素输出（保证栈内元素优先级严格递增）





### Assign过程

对每一个变量进行依次赋值，当每个变量都被赋值之后，进行求解



### Calculate过程

准备过程： $Output$  $VarStack$ 

计算详细过程：

1. 如果是变量：
   1. 直接进入 $VarStack$
2. 如果是符号：
   1. 判断是几目操作符
      1. 一目操作符（ $\neg$）
         1. 从 $VarStack$中取出一个变量 $var$，进行运算后创建一个新的变量( $\neg (var)$)。该变量的值等于计算后的值，名字为 $\neg (var)$,即在原变量扩上一个括号并加上一个取反，重新放入栈中
      2. 双目操作符
         1. 从 $VarStack$中取出两个变量 $var1，var2$，进行运算后创建一个新的变量 $(var1)?(var2)$ 。该变量的值等于计算后的值，名字为 $(var1)?(var2)$,即在原变量扩上一个括号并加上符号，重新放入栈中
3. 计算结束后，





### Repeat过程

进行一个递归的大动作
