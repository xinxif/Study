### C语言的概述

语言与命名规则

以前的C语言，还要求把变量声明在块的顶部，其它语句不能放在任何声明的前面。

```c
  int main()
    {
        int doors;//旧规则
        int dogs;
        doors=5
        dogs=3;
      	//其它语句
      
      	//c99和c11遵循c++的惯例，可以把声明放在块中的任何位置。
    }
```

C99和C11允许使用更长的**标识符名**， 但是**编译器只识别前63个字符**。对于**外部标识符**（参阅第12
章）， 只允许使用**31个字符**。实际上， 你可以使用更长的字符， 但是编译器会忽略超出的字符。**小写字母、 大写字母、 数字和下划线（＿）来==命名==**。 而且， 名称的**第1个字符必须是字符或下划线**， ==不能是数字== 。操作系统和C库经常使用以一个或两个下划线字符开始的标识符（如， `＿kcab`)，因此最好避免在自己 的程序中使用这种名称。C语言的名称区分大小写。

C语言关键字中，**粗体表示的是C90标准新增的关键字**，**斜体**表示的C99标准新增的关键字，**粗斜体**表示的是C11标准新增的关键字

|    auto     |   extern   |     short      |         while          |
| :---------: | :--------: | :------------: | :--------------------: |
|   `break`   |  `floa`t   |  **`signed`**  |    ***`_Alignas`***    |
|   `case`    |   `for`    |    `sizeof`    |    ***`_Alignof`***    |
|   `char`    |   `goto`   |    `static`    |    ***`_Atomic`***     |
| **`const`** |    `if`    |    `struct`    |     ***`_Bool`***      |
| `continue`  |  `inline`  |    `switch`    |    ***`_Complex`***    |
|  `default`  |   `int`    |   `typedef`    |    ***`_Generic`***    |
|    `do`     |   `long`   |    `union`     |   ***`_Imaginary`***   |
|  `double`   | `register` |   `unsigned`   |   ***`_Noreturn`***    |
|   `else`    | `restrict` |     `void`     | ***`_static_assert`*** |
| **`enum`**  |  `return`  | **`volatile`** | ***`_Thread_local`***  |

----

### 数据和C

