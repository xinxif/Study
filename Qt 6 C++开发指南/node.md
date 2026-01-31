### 第一章

1. `Profile` 是介于`Debug` 和`Release` 之间的性能平衡版本，**可用于调试**。
2. `Shadow Build` 是 `Qt Creator` 提供的一种构建方式，它将编译过程中生成的中间文件和可执行文件输出到**独立于**源码目录的构建目录中，从而**保持源码目录的整洁**，便于同时管理多种构建配置和开发环境。

### 第二章 CUI程序设计基础

1. <img style="width: 1200px;height:300px" src="image\qmake常见变量定义.png">

   - `Qt` 帮助文档中的`qmake Manual` 主题

2. 主程序文件

   - ```c++
     #include"widget.h"
     #include<QApplication>
     int main(int argc,char *argv[])
     {
     	QApplication a(argc,argv); //定义并创建应用程序
         widget w;					//定义并创建窗口对象
         w.show();					//显示窗口
         return a.exec();			//运行应用程序，开始应用程序的消息循环和事件处理
     }
     ```

   - `*.ui`文件经过***UIC* 编译**后生成`*.h`这个文件里定义了一个类，类的名称是`Ui_*`，用`C++`语言描述`UI` 文件中界面组件的属性设置、布局以及信号与槽的关联等内容

     - 窗口界面定义文件，是一个XML文件。用`Qt Designer` 打开`UI` 文件进行窗口界面可视化设计，保存修改后会重新生成`UI` 文件。
     - `retranslateUi()`，其功能是设置界面上各组件的文字属性，如标签的文字、按钮的文字、窗口的标题等。界面上所有与文字设置相关的功能都集中在函数`retranslateUi()`里，在**设计多语言界面时**会用到这个函数。

3. 窗口界面可视化设计

   - 界面组件的属性设置，需要注意以下几点

     - 界面上的每个组件需要有一个唯一的对象名称，程序里访问界面组件时都是通过其对象名称进行的，**自动生成的槽函数名称里也有对象名称**。所以，**组件的对象名称设置好之后一般不要改动**。若需要修改对象名称，涉及的代码需要相应改动。
     - 窗体的对象名称会影响窗口`UI` 类的名称。`dialog.ui` 被`UIC` 编译后生成文件`ui_dialog.h`，窗体的对象名称与文件`ui_dialog.h`中定义的窗口`UI` 类有关。一般不在`Qt Designer` 里修改窗体的对象名称，除非是要重命名一个窗口，那么需要对窗口相关的`4` 个文件都重命名。
     - 设置**窗体**的`font `属性后，**界面上其他组件**的**默认字体就是窗体的字体**，无须再单独设置，除非要为某个组件设置单独的字体，例如组件`plainTextEdit` 的字体大小被单独设置为`20`。
     - 组件的属性都有默认值，一个组件的某个属性被修改后，属性编辑器里的属性名称会以粗体显示。如果要恢复属性的默认值，点击属性值右端的还原按钮即可。

   - <img style="width: 1100px;height:700px" src="image\qt设计师工具.png">

   - <img style="width: 1100px;height:700px" src="image\伙伴关系与tab属性.png">

   - 信号（signal）是在特定情况下被发射的通知

   - 槽（slot）是对信号进行响应的函数。槽就是函数，所以也称为槽函数。槽函数与一般的C++函数一样，可以具有任何参数，也可以被直接调用。槽函数与一般的函数不同的是：槽函数可以与信号关联，当信号被发射时，关联的槽函数被自动运行。

   - ```c++
     QObject::connect(sender, SIGNAL(signal()), receiver, SLOT(slot()));
     ```

     - `connect()`是`QObject` 类的一个**静态函数**，而`QObject` 是大部分`Qt` 类的基类，在实际调用时可以忽略前面的限定符部分。

     - `sender` 是发射信号的对象的名称

     - `signal()`是信号，信号可以看作特殊的函数，需要带有括号，有参数时还需要指明各参数类型；

     - `receiver` 是接收信号的对象的名称

     - `slot()`是槽函数，需要带有括号，有参数时还需要指明各**参数类型**。

     - 当一个信号与多个槽函数关联时，**槽函数按照建立连接时的顺序依次运行**。

     - ```c++
       connect(spinNum, SIGNAL(valueChanged(int)), this, SIGNAL(refreshInfo(int)));
       //一个信号可以连接另一个信号
       ```

     - **当一个信号被发射时**，与其关联的槽函数通常被**立即运行**，就像正常调用函数一样。只有当**信号关联的所有槽函数运行完毕后**，才运行发射信号处后面的代码。

   - `QDialog`

     - ```c++
       //公有的槽函数
       accept();//关闭对话框，表示肯定的选择，如对话框上的“确定”按钮。
       reject();//功能是关闭对话框，表示否定的选择，如对话框上的“取消”按钮。
       close();//功能是关闭对话框。
       
       //QAbstractButton
       clicked(bool)	//信号以复选框当前的选择状态作为参数。
       ```

   - `QMetaObject::connectSlotsByName(Dialog);`

     - 搜索`Dialog` 界面上的所有组件，将名称匹配的信号和槽关联起来，
       - 假设槽函数的名称是：`void on_<object name>_<signal name>(<signal parameters>);`
     - 例如，通过`Go to slot` 对话框，为复选框`chkBoxUnder` 
       - 自动生成的槽函数是：`void on_chkBoxUnder_clicked(bool checked);`
     - 它正好是`chkBoxUnder` 的信号`clicked(bool)`的槽函数。那么，函数`connectSlotsByName()`就会将此
       信号和槽函数关联起来，相当于运行了下面的一条语句：
       - `connect(chkBoxUnder, SIGNAL(clicked(bool)), this, SLOT(on_chkBoxUnder_clicked(bool)));`

   - [图片转ICO](https://www.aconvert.com/cn/icon/png-to-ico/)

     - 将一个后缀为`“.ico”`的图标文件复制到项目根目录下
     - 在项目配置文件（`.pro` 文件）里用`RC_ICONS` 设置图标文件名，即添加如下一行语句：`RC_ICONS = editor.ico`重新构建项目，生成的可执行文件以及窗口的图标就会换成设置的图标。
       - `win32 {}` 条件语句限定其作用范围，以避免在其他操作系统上出现构建问题。
       - `win32 {RC_ICONS = $$PWD/editor.ico}`

   - **`Qt`项目构建过程基本原理**

     - 元对象系统和MOC
       - `Qt` 对标准`C++`语言进行了扩展，引入了元对象系统（meta-object system，MOS），所有从`QObject`继承的类都可以利用元对象系统提供的功能。**元对象系统支持属性、信号与槽、动态类型转换等特性**，第3 章会详细介绍元对象系统的这些特性的使用方法。
       - 我们在`Qt Creator` 中编写程序时使用的`C++`语言，实际上是经过`Qt`扩展的`C++`语言。例如，在示例`samp2_2` 的`Dialog `类的定义中插入一个宏`Q_OBJECT`，这是使用信号与槽机制的类必须插入的一个宏。`Dialog` 类中的`private slots` 部分用于定义私有槽，这是标准`C++`语言中没有的特性。
       - `Qt` 提供了元对象编译器（MOC）。在构建项目时，项目中的头文件会先被`MOC` 预编译。例如，以`Release` 模式构建项目`samp2_2` 后，文件夹`release` 里的文件。其中，`moc_dialog.cpp`是`MOC` 读取文件`dialog.h` 的内容后生成的一个元对象代码文件，==文件`moc_predefs.h` 里是一些宏定义==。结合`moc_dialog.cpp` 和`moc_predefs.h`，`dialog.cpp` 和`ui_dialog.h` 就可以被标准`C++`编译器编译。
         - <img style="width: 1100px;height:500px" src="image\工程文件.png">
         - <img style="width: 1100px;height:300px" src="image\混合编译.png">
     - UI 文件和UIC
       - 可视化设计的窗口`UI` 文件会被用户界面编译器`（UIC）`转换为一个`C++`源程序文件。例如示例项目`samp2_1` 中的文件`widget.ui` 被转换为文件`ui_widget.h`。
       - `UIC` 编译生成的文件与UI 文件在同一个文件夹里，文件`ui_widget.h` 之后会被标准`C++`编译器编译。
     - 资源文件和RCC
       - `Qt` 项目中的资源文件（`.qrc` 文件）会被资源编译器（`RCC`）转换为`C++`程序文件。例如示例项目`samp2_2` 中的资源文件是`res.qrc`，经过`RCC `编译后生成的文件是`qrc_res.cpp`。
     - 标准`C++`编译器
       - 使用 `MOC`、`UIC` 和`RCC` 编译各原始文件的过程称为预编译过程，预编译之后生成的是标准C++语言的程序文件，它们被标准C++编译器编译和连接，最终生成可执行文件。
       - `samp2_3`手动`ui`创建

4. 使用`CMake`构建系统

   - 通过与平台和编译器无关的配置文件控制软件的构建过程，生成本地化的`makefile` 文件或`IDE` 项目

     ```cmake
     cmake_minimum_required(VERSION 3.16)    	#需要的CMake 最低版本
     
     project(samp2_4 VERSION 0.1 LANGUAGES CXX)  #项目版本0.1，编程语言是C++
     
     set(CMAKE_AUTOUIC ON)       #UIC 能被自动执行
     set(CMAKE_AUTOMOC ON)       #MOC 能被自动执行
     set(CMAKE_AUTORCC ON)       #RCC 能被自动执行
     
     set(CMAKE_CXX_STANDARD 17)          #设置编译器需要满足的C++语言标准，设置为C++17
     set(CMAKE_CXX_STANDARD_REQUIRED ON) #要求编译器满足C++标准
     
     find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
     find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
     
     find_package(Qt${Qt_VERSION_MAJOR} REQUIRED COMPONENTS Qt${Qt_VERSION_MAJOR}Sql)
     
     set(PROJECT_SOURCES     #设置变量PROJECT_SOURCES 等于下面的列表
             main.cpp        #也就是项目的源文件列表
             dialog.cpp
             dialog.h
             dialog.ui
     )
     
     if(${QT_VERSION_MAJOR} GREATER_EQUAL 6) #如果是Qt 6 以上的版本
         qt_add_executable(samp2_4           #创建可执行文件samp2_4
             MANUAL_FINALIZATION             #可选参数，手动结束创建目标的过程
             ${PROJECT_SOURCES}              #文件列表来源于变量PROJECT_SOURCES
         )
     # Define target properties for Android with Qt 6 as:
     #    set_property(TARGET samp2_4 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
     #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
     # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
     else()
         if(ANDROID)
             add_library(samp2_4 SHARED
                 ${PROJECT_SOURCES}
             )
     # Define properties for Android with Qt 5 after find_package() calls as:
     #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
         else()
             add_executable(samp2_4
                 ${PROJECT_SOURCES}
             )
         endif()
     endif()
     
     #在连接生成目标samp2_4 时，需要利用前面用find_package()导入的Qt6::Widgets 模块
     target_link_libraries(samp2_4 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
     target_link_libraries(samp2_4 PRIVATE Qt${QT_VERSION_MAJOR}::Sql)
     # Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
     # If you are developing for iOS or macOS you should consider setting an
     # explicit, fixed bundle identifier manually though.
     if(${QT_VERSION} VERSION_LESS 6.1.0)
       set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.samp2_4)
     endif()
     
     set_target_properties(samp2_4 PROPERTIES
         ${BUNDLE_ID_OPTION}
         MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
         MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
         MACOSX_BUNDLE TRUE
         WIN32_EXECUTABLE TRUE
     )
     
     include(GNUInstallDirs)
     install(TARGETS samp2_4
         BUNDLE DESTINATION .
         LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
         RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
     )
     
     if(QT_VERSION_MAJOR EQUAL 6)
         qt_finalize_executable(samp2_4)         #最后生成可执行文件samp2_4
     endif()
     
     ```

     - `CMake` 项目文件`CMakeLists.txt `的内容一般不需要我们手动修改，项目中新增文件时会自动更新源文件列表。
     - 只有用到`Qt` 的某个附加模块时，才需要编写`find_package()`和`target_link_libraries()`函数语句。在`Qt` 帮助文档里的模块介绍部分，会说明这两个函数的写法，

   - `D:\IDE\Qt\Tools\CMake_64\bin` ·`CMake GUI`应用程序路径

     - 可以生成`VS`项目解决方案，需要使用`MSVC`编译套件，系统环境变量也存在`Qt`的`MSVC`编译套件，要在`MinGw`之前。

5. `Qt Creator`使用技巧

   - <img style="width: 1100px;height:400px" src="image\Qt快捷键.png">
   - 禁用 `Qt Creator` 中的`Clang` 代码模型，方法是点击`Help→About Plugins` 菜单项。打开管理已安装插件的对话框，设置取消选用`ClangCodeModel `插件即可。

### 第三章 Qt框架功能概述

#### 元对象系统

1. 元对象系统概述

   - `Qt` 的元对象系统的功能建立在以下`3`个方面
     - `QObject` 类是所有使用元对象系统的类的基类。
     - 必须在一个类的开头部分插入宏 `Q_OBJECT`，这样这个类才可以使用元对象系统的特性。
     - `MOC` 为每个`QObject` 的子类提供必要的代码来实现元对象系统的性。
   - 构建项目时，`MOC` 会读取`C++`源文件，当它发现类的定义里有`Q_OBJECT `宏时，它就**会为这个类生成另一个包含元对象支持代码的`C++`源文件**，这个生成的源文件连同类的实现文件一起被标准`C++`编译器编译和连接。

2. `QObject`

   - `QObject` 类是所有使用元对象系统的类的基类，也就是说，如果一个类的父类或上层父类是`QObject`，它就可以使用信号与槽、属性等特性。

   - <img style="width: 1100px;height:400px" src="image\元对象系统.png">

   - ```c++
     QPushButton btn;
     qDebug() << btn.metaObject()->className();
     // 输出: QPushButton
     qDebug() << QPushButton::staticMetaObject.className();
     
     QObject *obj = new QPushButton;
     if (obj->inherits("QAbstractButton")) {
         qDebug() << "这是一个按钮";
     }
     
     //找所有符合条件的子对象
     auto buttons = win->findChildren<QPushButton*>();
     ```

   - 属性系统

     - 在类的定义代码中可以用宏`Q_PROPERTY` 定义属性，`QObject` 的`setProperty()`函数会设置属性的值或定义动态属性；`property()`函数会返回属性的值。

3. `QMetaObject`

   - 每个 `QObject` 及其子类的实例都有**一个自动创建的元对象**，元对象是`QMetaObject` 类型的**实例**。元对象**存储了类的实例所属类的各种元数据**，包括类信息元数据、方法元数据、属性元数据等，所以，元对象实质上是对类的描述。
   - <img style="width: 1100px;height:600px" src="image\QMetaObject.png">
   - <img style="width: 1100px;height:300px" src="image\QMetaObject2.png">
   - `qobject_cast()`进行动态类型转换
     - 如果自定义的类要支持函数`qobject_cast()`，那么自定义的类需要直接或间接继承自`QObject`，且在类定义中插入宏`Q_OBJECT`。
     - 标准 `C++`语言中有类似的强制类型转换函数`dynamic_cast()`，使用`qobject_cast()`的好处是不需要`C++`编译器开启RTTI 支持。

4. 属性系统

   - 属性是 `Qt C++`的一个扩展的特性，是基于元对象系统实现的，标准`C++`语言中没有属性。在`QObject `的子类中，我们可以使用宏`Q_PROPERTY` 定义属性。
     
     - ```c++
       Q_PROPERTY(type name
               (READ getFunction [WRITE setFunction] |
               MEMBER memberName [(READ getFunction | WRITE setFunction)])
               [RESET resetFunction]
               [NOTIFY notifySignal]
               [REVISION int | REVISION(int[, int])]
               [DESIGNABLE bool]
               [SCRIPTABLE bool]
               [STORED bool]
               [USER bool]
               [BINDABLE bindableProperty]
               [CONSTANT]
               [FINAL]
               [REQUIRED])
       ```
     
     - 宏`Q_PROPERTY` 定义一个值类型为`type`，名称为`name` 的属性，用`READ`、`WRITE` 关键字分别定义属性的读取、写入函数，还有一些其他关键字用于定义属性的一些操作特性。属性值的类型可以是`QVariant` 支持的任何类型，也可以是自定义类型。
     
     - `READ`：指定一个读取属性值的函数，没有MEMBER 关键字时必须设置READ。
     
     - `WRITE`：指定一个设置属性值的函数，只读属性没有WRITE 配置
     
     - `MEMBER`：指定一个成员变量与属性关联，使之成为可读可写的属性，指定后无须再设置READ 和WRITE。
     
     - `RESET`：是可选的，用于指定一个设置属性默认值的函数。
     
     - `NOTIFY`：是可选的，用于设置一个信号，当属性值变化时发射此信号。
     
     - `DESIGNABLE`：表示属性是否在Qt Designer 的属性编辑器里可见，默认值为true。
     
     - `USER`：表示这个属性是不是用户可编辑的属性，默认值为false。通常一个类只有一个USER 设置为true 的属性，例如QAbstractButton 的checked 属性
     
     - `CONSTANT`：表示属性值是一个常数，对于一个对象实例，READ 指定的函数返回值是常数，但是每个实例的返回值可以不一样。具有CONSTANT 关键字的属性不能有WRITE和NOTIFY 关键字。
     
     - `FINAL`：表示所定义的属性不能被子类重载。
     
     - ```c++
       Q_PROPERTY(bool focus READ hasFocus)
       Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled)
       Q_PROPERTY(QCursor cursor READ cursor WRITE setCursor RESET unsetCursor)
       ```
     
   - 属性的使用
   
     - `QObject` 类提供了两个函数直接通过属性名字符串来访问属性，其中`QObject::property()`函数读取属性值，`QObject::setProperty()`函数设置属性值。
   
     - ```c++
       bool isFlat=ui->btnProperty->property("flat").toBool(); //通过属性名读取属性值
       
       ui->btnProperty->setProperty("flat", !isFlat); //通过属性名设置属性值
       
       //ui->btnProperty表示窗口上的一个QPushButton按钮。注意，QObject::property()函数的返回值是QVariant类型，需要转换为具体的类型。
       ```

### 第四章 常用界面组件的使用

1. 常用的界面组件

   - <img style="width: 1100px;height:240px" src="image\Buttons.png">
   - <img style="width: 1100px;height:440px" src="image\输入组件.png">
   - <img style="width: 1100px;height:440px" src="image\InputWidget.png">
   - <img style="width: 1100px;height:340px" src="image\显示类组件.png">
   - <img style="width: 1100px;height:340px" src="image\显示类组件2.png">
   - <img style="width: 1100px;height:740px" src="image\容器类组件.png">
   - `QAxWidget`**是从`QWidget` 间接继承**的，继承关系比较复杂。
   - <img style="width: 1100px;height:340px" src="image\ItemWidget.png">
   - 还有一些界面组件并没有出现在 `Qt Designer` 的组件面板里，例如常用的菜单栏（`QMenuBar`类）、菜单（`QMenu` 类）、工具栏（`QToolBar` 类）、状态栏（`QStatusBar` 类）等组件，对应的几个类都是直接从`QWidget` 继承而来的，
   
2. `QWidget` 类的主要属性和接口函数

   - <img style="width: 1100px;height:540px" src="image\QWidget的主要属性.png">

     - `sizePolicy`
       - `QSizePolicy`类型，它定义了组件在**水平和垂直**方向的尺寸变化策略。`Horizontal Policy`组件在水平方向的尺寸变化策略，`Vertical Policy` 表示组件在垂直方向的尺寸变化策略。其值都是枚举类型`QSizePolicy::Policy`
       - `QSizePolicy::Preferred`：首选尺寸，使用`sizeHint()`函数的返回值作为**最优**尺寸，组件仍然可以缩放，但是放大时不会超过`sizeHint()`函数返回的尺寸。
       - `QSizePolicy::Expanding`：可扩展尺寸，`sizeHint()`函数的返回值是**可变大小**的尺寸，组件可扩展。
       - `QSizePolicy::MinimumExpanding`：最小可扩展尺寸，`sizeHint()`函数的返回值是**最小**尺寸，组件可扩展。
       - `QSizePolicy::Ignored`：忽略尺寸，`sizeHint()`函数的返回值被忽略，**组件占据尽可能大的空间**。
       - 在使用尺寸策略时，`QWidget` 的`sizeHint()`函数会起到很大作用，在组件的父组件尺寸变化时，`sizeHint()`返回组件的建议尺寸。
       - `QSizePolicy` 还有`Horizontal Stretch`（水平延展）属性和`Vertical Stretch`（垂直延展）属性，分别表示水平延展因子和垂直延展因子，它们都是整数值，取值范围是0～255。默认值是0，表示组件保持默认的宽度或高度。
       - <img style="width: 1100px;height:240px" src="image\延展因子.png">
     
   - `QWidget` 作为窗口时的属性

     - <img style="width: 1100px;height:340px" src="image\Widget窗口.png">

     - ```c++
       //当 QWidget 作为独立的窗口时，有如下一些与窗口显示有关的公有槽函数。
       bool close(); //关闭窗口
       void hide(); //隐藏窗口
       void show(); //显示窗口
       void showFullScreen(); //以全屏方式显示窗口
       void showMaximized(); //窗口最大化
       void showMinimized(); //窗口最小化
       void showNormal(); //全屏、最大化或最小化操作之后，恢复正常大小显示
       
           
       //QWidget 中定义的信号只有3 个，定义如下：
       void customContextMenuRequested(const QPoint &pos);
       void windowIconChanged(const QIcon &icon);
       void windowTitleChanged(const QString &title);
       ```



#### 布局管理

1. 布局管理相关的类
   - `QGridLayout`：网格布局，使多个组件按**行和列**实现网格状自动布局。
   - `QFormLayout`：表单布局，与`QGridLayout` 功能类似，适用于**两列组件**的布局管理。
   - ==`QStackedLayout`：堆叠布局。==
     - `QStackedLayout `用于管理多个`QWidget` 类对象，也就是多个页面，但任何时候只有一个页面可见。
     - `QStackedLayout` 的管理效果与`QStackedWidget` 的相似，只是它没有切换页面的按钮，需要另外编程处理页面切换。
   - <img style="width: 1100px;height:240px" src="image\布局管理继承体系.png">
   - 表单布局只适用于两列组件的布局，例如第一列是 `QLabel` 组件，第二列是`QLineEdit`，`QComboBox` 等输入组件，构成一种输入表单。
   - `Horizontal Spacer` 和`Vertical Spacer` 对应的类均是`QSpacerItem`。`QSpacerItem` 可以用于在布局中占位，或填充剩余空间。
   - 分割条组件类 `QSplitter` 是从`QWidget `继承而来的，所以它是一个可见的界面组件。分割条一般用于水平或垂直分割来显示两个容器类组件。
2. 布局可视化设计及其代码原理
   - 任何布局类对象在可视化设计时都有`layoutLeftMargin`、`layoutTopMargin`、`layoutRightMargin` 和
     `layoutBottomMargin` 这4 个边距属性，这4 个**边距属性**用于设置**布局组件与父容器的4 个边距的最小值**，单位是**像素**。水平布局和垂直布局还有一个属性`layoutSpacing`，表示**组件的最小间距**。
   - 网格布局
     - `layoutHorizontalSpacing`：水平方向上组件的最小间距。
     - `layoutVerticalSpacing`：垂直方向上组件的最小间距。
     - `layoutRowStretch`：各行的延展因子，与垂直布局的`layoutStretch` 属性功能相同。
     - `layoutColumnStretch`：各列的延展因子，与水平布局的`layoutStretch `属性功能相同。
     - `layoutRowMinimumHeight`：各行的最小高度，单位是像素，若值是0 则表示自动设置。
     - `layoutColumnMinimumWidth`：各列的最小宽度，单位是像素，若值是0 则表示自动设置。
     - `layoutSizeConstraint`：布局的尺寸限制方式，其值是枚举类型`QLayout::SizeConstraint`，默认设置为`QLayout::SetDefaultConstraint`，也就是**将父组件的最小尺寸作为网格布局的最小尺寸**。
     - `void QGridLayout::addWidget(QWidget *widget, int fromRow, int fromColumn, int rowSpan,int columnSpan, Qt::Alignment alignment = Qt::Alignment())`
       - **`fromRow` 和`fromColumn` 表示组件所在的行号和列号，`rowSpan` 和`columnSpan `表示组件占用的行数和列数，`alignment` 表示默认的对齐方式。**
       - 在设计网格布局的时候，并不意味着每个网格里都必须有组件，网格可以空着，也可以使用水平或垂直间隔组件占位。
   - 分割条
     - `QSplitter`，分割条可以实现水平分割或垂直分割，一般是在两个可以自由改变大小的组件之间进行分割。
     - `QMainWindow::setCentralWidget()`函数将其设置为主窗口的中心组件，也就是填充满主窗口的工作区。
     - `orientation`：方向，即水平分割或垂直分割
     - `opaqueResize`：如果值是`true`，表示拖动分割条时，组件是动态改变大小的
     - `handleWidth`：进行分割操作的拖动条的宽度，单位是像素。
     - `childrenCollapsible`：表示进行分割操作时，子组件的大小是否可以变为0。

#### QString

1. 简介

   - `QString`存储的是一串字符，每个字符是==一个`QChar` 类型==的数据。`QChar` 使用的是`UTF-16` 编码，==一个字符包含`2` 字节数据。==

   - 对于超过65535 的Unicode 编码，`QString` 使用两个连续的`QChar` 字符表示。

   - `Latin1` 字符集是对`ASCII` 字符集的扩展，也是用1 字节编码，它用128～255 表示拉丁字母表中特殊语言字符的编码。

   - `ASCII` 和`Latin1` 都是用`1` 字节编码的，最多只有`256` 个字符，无法表示汉语、日语等其他语言里的字符，因此又出现了`Unicode` 编码。`Unicode` 编码增加一个或多个高字节对`Latin1` 字节进行扩展。当这些高字节数据为`0` 时，低字节数据就是`Latin1` 字符。`Unicode` 支持大多数国家/地区语言文字的编码，所以被广泛使用。

   - `Unicode` 有多种存储方案，其中`UTF-8` 最少用`1` 字节编码，可以使用`1～4 `字节编码；`UTF-16` 最少用`2`字节编码，可以使用`2` 字节或`4` 字节编码。`UTF-8` 可以兼容`Latin1` 编码，所以被广泛使用。`Qt Creator` 存储的`C++`语言头文件和源程序文件都默认使用`UTF-8` 编码。

   - ```c++
     QString str= "dimple,酒窝";
     QChar ch0= str[0]; 		//ch0='d'
     QChar ch7= str.at(7); 	//ch7='酒'
     ```

2. `QChar`的功能

   - <img style="width: 1100px;height:240px" src="image\QChar类.png">

   - <img style="width: 1100px;height:240px" src="image\QChar类2.png">

   - 只有当`QChar` 字符的编码为`0～255` 时，函数`toLatin1()`的转换才有意义。

   - `QChar` 的接口函数`unicode()`用于返回字符的`UTF-16` 编码。也就是char16_t 类型的数。

   - `QChar QChar::fromUcs2(char16_t c)`通过char16_t 类型的编码构造`QChar` 字符。静态函数。

   - ```c++
     QString str= "Hello,北京";
     str[6]= QChar(0x9752); 				//'青'，使用构造函数
     str[7]= QChar::fromUcs2(0x5C9B); 	//'岛'，使用静态函数
     
     //Qt 的源程序文件采用的是UTF-8 编码，源代码中的“青”是2 字节UTF-8 编码，而QChar没有这种类型参数的构造函数。
     str[6]= QChar('青'); 				//错误的代码
     ```

3. `QString`字符串常用操作

   - - 函数`front()`和`back()`。函数`front()`返回字符串中的第一个字符。

     - 函数`left()`和`right()`。函数`left()`从字符串中提取左边`n `个字符，函数`right()`从字符串中提取右边`n` 个字符

     - `first()`与`left()`功能相同，`last()`与`right()`功能相同，`first()`和`last()`是`Qt 6.0` 中引入的函数，执行速度更快。

     - `QString QString::mid(qsizetype pos, qsizetype n = -1)`

       - `pos` 是起始位置，`n` 是返回字符串中的字符个数。如果不指定参数`n`，就返回从`pos`开始到末尾的字符串。

     - `sliced()`与`mid()`的功能相同

       - ```c++
         QString QString::sliced(qsizetype pos, qsizetype n) //返回从位置pos开始的n个字符的字符串
         QString QString::sliced(qsizetype pos) //返回从位置pos 开始到末尾的字符串
         ```

       - 在函数`sliced()`中，如果设置的参数会导致超出字符串的边界，则函数的行为是不确定的，但如果是在边界内，则`sliced()`的执行速度比`mid()`的快

     - `QString QString::section(const QString &sep, qsizetype start, qsizetype end = -1,QString::SectionFlags flags = SectionDefault)`

       - 从字符串中提取以`sep` 作为分隔符，从`start` 段到`end` 段的字符串。

       - ```c++
         QString str2, str1= "学生姓名,男,2003-6-15,汉族,山东";
         str2= str1.section(",",0,0); //str2 ="学生姓名"，第一段的编号为0
         str2= str1.section(",",1,1); //str2 ="男"
         str2= str1.section(",",0,1); //str2 ="学生姓名，男"
         str2= str1.section(",",4,4); //str2 ="山东"
         ```

4. 存储相关的函数

   - 只有`“\0”`，则`isNull()`返回`false`，而`isEmpty()`返回`true`。
   - `resize()`参数`size `大于字符串当前长度，就扩充字符串，但新增的字符是不确定的。
     - `void QString::resize(qsizetype size, QChar fillChar)`
     - 用一个字符填充字符串中扩充的位置。
   - `QString &QString::fill(QChar ch, qsizetype size = -1)`
     - `ch` 是要设置的字符，`size` 是设置的字符串新的长度，如果不设置`size` 参数的值，表示保持字符串长度不变。
     - **会改变字符串的大小**

5. 搜索和判断

   - 函数`indexOf()`和`lastIndexOf()`。函数`indexOf()`的功能是在当前字符串内查找某个字符串首次出现的位置。

     - `qsizetype QString::indexOf(const QString &str, qsizetype from = 0,Qt::CaseSensitivity cs = Qt::CaseSensitive)`
     - 参数`str` 是要查找的字符串，参数`from` 是开始查找的位置，参数`cs` 指定是否区分大小写。

   - `contains()`判断当前字符串是否包含某个字符串，可指定是否区分大小写。

   - `endsWith()`和`startsWith()`

     - 是否以某个字符串开头，否以某个字符串结束

   - `trimmed()`和`simplified()`

     - 函数`trimmed()`会去掉字符串首尾的空格
     - 函数`simplified()`不仅会去掉字符串首尾的空格，还会将中间连续的空用单个空格替换。

   - `chop()`去掉字符串末尾的`n`个字符，`n` 是输入参数。如果`n` 大于或等于字符串实际长度，字符串内容就变为空。

   - `replace()`

     - `QString &QString::replace(qsizetype pos, qsizetype n, const QString &after)`

     - 字符串的`pos` 位置开始替换`n `个字符，替换后的字符串是`after`。该函数会修改当前字符串的内容，并返回字符串对象的引用。

     - ```c++
       QString str1= "Goooogle";
       str1.replace('o', 'e'); //str1 ="Geeeegle"
       ```

   - `remove()`

     - 字符串的`pos` 位置开始移除`n` 个字符
     - 另一种参数形式，即可以移除字符串中某个字符出现的所有实例

6. `QString`字符串与数值的转换

   - `QString`有一些接口函数用于将字符串转换为整数

     - `int toInt(bool *ok = nullptr, int base = 10);`

       - `base` 可以设置为2～36，
       - 如果转换失败，返回值是0。如果要判断转换是否成功，不要根据返回值是否为0 来判断，而是要传递参数`ok`，根据`ok` 的返回值来判断。
       - **==字符串表示的是进制数则base因该设为2==**
       - 

     - `float toFloat(bool *ok = nullptr)`

     - `double toDouble(bool *ok = nullptr)`

     - `setNum()`用于**将整数或浮点数转换为字符串**。`setNum()`是==`overload` 型函数==，有很多种参数形式。

       - `QString &setNum(float n, char format = 'g', int precision = 6)`
       - <img style="width: 1100px;height:180px" src="image\浮点数格式.png">

     - ==**静态函数**==`number()`

       - 参数形式和功能与成员函数`setNum()`的相似

     - **静态函数**`asprintf()`

       - `QString` 的静态函数`asprintf()`用于构造格式化输出各种数据的字符串，类似于标准C 语言中的函数`printf()`。

       - `cformat`格式化字符串中支持汉字，但是**替换格式化字符串中的**`%s `只能==**用`UTF-8` 编码的字符串**==，也就是变量的字符串中不能有汉字，否则会出现乱码。

       - ```c++
         QString UPC = "UPC";
         //QString UPC= "石油大学"; //如果这个字符串中有汉字，str2 会出现乱码
         QString str2= QString::asprintf("Hello,欢迎来到 %s",UPC.toLocal8Bit().data());
         //将QString型变量UPC的UTF-16 编码的字符串转换为本地8位编码的QByteArray型数据，再得到QByteArray数据的char 类型指针
         ```

     - 函数`arg()`

       - `QString arg(int a, int fieldWidth = 0, int base = 10, QChar fillChar = QLatin1Char(' '))`

         - `a` 是要转换为字符串的整数

         - `fieldWidth` 是转换成的字符串占用的最少空格数

         - `base`是转换成的字符串显示进制

         - `fillChar`是当`fieldWidth`大于实际数位宽度时使用的填充字符，默认用空格

         - ```c++
           //格式字符串中占位符出现的顺序可以打乱，甚至可以重复出现，例如，最后一行代码如果是：
           QString str1= QString("%1 年度: %3/%2/%1").arg(Y).arg(M,2,base,ch).arg(D,2,base,ch);
           //那么，str1 的内容为“2021 年度: 03/08/2021”。
           ```

       - `QString arg(const QString &a, int fieldWidth = 0, QChar fillChar = QLatin1Char(' '))`

         - 以`QString` 作为输入参数类型

       - `QString arg(double a, int fieldWidth = 0, char format = 'g', int precision = -1,QChar fillChar = QLatin1Char(' '))`

         - 可以把浮点数转换为字符串

#### QSpinBox和QDoubleSpinBox

1. 属性和接口函数
   - `QSpinBox` 和`QDoubleSpinBox` 都是`QAbstractSpinBox` 的子类，具有很多相同的属性，只是参数类型不同。
   - <img style="width: 1100px;height:340px" src="image\主要属性.png">
   - 从Qt 5.12开始，`QSpinBox` 和`QDoubleSpinBox` 新增了一个`stepType` 属性，表示步长变化的方式，属性值是枚举类型`QAbstractSpinBox::StepType`
     - `QAbstractSpinBox::DefaultStepType`：默认步长，也就是使用属性`singleStep` 设置的固定步长。
     - `QAbstractSpinBox::AdaptiveDecimalStepType`：自适应十进制步长，表示将自动连续调整步
       长值为10^n^，其中n为大于或等于0 的整数。例如，value 属性值为10 以下时，`singleStep`属性值为1；`value` 属性值为100～999 时，`singleStep` 属性值为10。
     - `void QSpinBox::setRange(int minimum, int maximum)`
       - 设置最小值和最大值
   - 信号
     - `void QSpinBox::valueChanged(int i)`
       - value 属性值变化时被发射，传递的参数`i `是变化之后的数值。
     - `void QSpinBox::textChanged(const QString &text)`
       - 显示的文字发生变化时被发射，例如数值变化导致文字变化，`prefix` 或`suffix` 属性变化导致文字变化。

#### 常用的按钮组件

1. 普通按钮（`QPushButton` 类）、工具按钮（`QToolButton` 类）、单选按钮（`QRadioButton` 类）、复选框（`QCheckBox` 类），它们都有共同的父类`QAbstractButton`（**抽象类**）。
   - 这4 种按钮都是可复选的，通过设置属性，普通按钮也可以实现复选框或单选按钮的功能。
2. 各按钮类的接口详解
   - <img style="width: 1100px;height:240px" src="image\QAbstractButton.png">
     - `QPushButton` 的`checkable` 属性默认值是`false`，它一般作为普通按钮使用。
     - `QRadioButton` 和`QCheckBox` 的`checkable` 属性默认值是`true`，它们有复选状态
     - `QCheckBox` 的`autoExclusive` 属性默认值是`false`，所以复选框一般用于非互斥的选项
     - `QRadioButton` 的`autoExclusive` 属性默认值是`true`，所以单选按钮一般用于互斥的选项
   - <img style="width: 1100px;height:140px" src="image\QPushButton.png">
     - 只有当按钮所在的**窗口基类是 `QDialog` 时，`autoDefault` 和`default` 属性才有意义**。
       - 在对话框上，如果一个按钮的`default `属性为`true`，它就是默认按钮，按下`Enter` 键就相当于点击了默认按钮。
       - 如果一个按钮的`autoDefault` 属性为`true`，它就是**自动**默认按钮，当它获得**焦点**时，它就会变成默认按钮。
   - `QCheckBox` 增加了==一个`tristate` 属性，==表示是否允许有`3` 种复选状态，即除了`Checked` 和`Unchecked`，==**还有`PartiallyChecked`**==。可以分别用`QAbstractButton` 定义的函数`isChecked()`和`setChecked()`读取和设置复选状态，也可以分别用`QCheckBox` 中定义的函数`checkState()`和`setCheckState()`读取和设置复选状态。
   - 常用的信号是`clicked()`。如果**按钮是可复选的**，还可以使用`clicked(bool)`信号，`bool` 类型参数是点击按钮后`checked` 属性的值。
     - 按钮的 `checked` 属性值变化时，按钮会发射`toggled(bool)`信号，`bool` 类型参数是变化之后的`checked` 属性的值。点击按钮或运行函数`setChecked()`会导致`checked` 属性值发生变化
   - `QCheckBox` 定义了**一个新信号**，定义如下：`void QCheckBox::stateChanged(int state)`
     - **当复选框的复选状态变化时，组件发射此信号**。如果**复选框的`tristate` 属性设置为`false`，**也就是只有两种复选状态时，`stateChanged()`信号和`toggled()`信号的作用是一样的。

#### QSlider和QProgressBar

1. 滑动型数值**输入**组件，包括滑动条（`QSlider` 类）、卷滚条（`QScrollBar`类）和表盘（`QDial` 类），对应的`3` 个类具有同一个==**父类**==`QAbstractSlider`
   - 具有一些共有的特性。例如`QSlider` 和`QScrollBar` 都有`orientation` 属性，可以设置为水平方向或垂直方向。
   - 进度条（`QProgressBar` 类）是用于显示数值的组件，特别适用于显示百分比进度。
2. 各组件类的主要属性和接口函数
   - <img style="width: 1100px;height:340px" src="image\QAbstractSlider.png">
     - `QAbstractSlider` 的接口函数主要是这些属性的读写函数，还有一个常用的函数`setRange()`
   - <img style="width: 1100px;height:170px" src="image\Abslid信号.png">
     - `actionTriggered(int action)`信号在滑动条触发一些动作时被发射，`action` 表示动作的类型，用枚举类型`QAbstractSlider::SliderAction` 的值表示
       - 如`SliderToMinimum` 表示滑动到最小值。
     - `value` 属性值改变时，组件会发射`valueChanged()`信号，可以通过拖动滑块改变`value` 属性的值，也可以在程序中运行函数`setValue()`改变`value` 属性的值。
     - 用鼠标拖动滑块移动时，组件会发射`sliderMoved(int value)`信号，参数`value` 是组件的当前值。
       - 如果`tracking` 属性设置为`true`，在拖动滑块==**时**==组件还会发射`valueChanged()`信号；
       - 如果`tracking` 属性设置为`false`，则只有在拖动==**结束**==并释放鼠标时组件才发射`valueChanged()`信号。
   - `QSlider` 类
     - `QSlider` 一般用作滑动输入数值数据的组件，`QSlider` 类新定义的属性有两个。
       - `tickPosition`：标尺**刻度**的==**显示位置**==，属性值是枚举类型`QSlider::TickPosition`
       - `tickInterval`：标尺刻度的间隔值，若设置为0，会在`singleStep` 和`pageStep` 之间自动选择
   - `QScrollBar`类
     - `QScrollBar` 没有定义新的属性。`QScrollBar` 一般与文本编辑器或容器组件组合使用，以便在一个大的显示范围内移动，例如`QPlainTextEdit` 组件显示的文本超过编辑框的大小后，就会自动出现水平卷滚条或垂直卷滚条。
   - `QDial`类
     - `QDial` 表示表盘式的组件，通过旋转表盘获得输入值，`QAbstractSlider` 定义的一些属性对`QDial`没有影响，例如`orientation` 属性。
       - `notchesVisible`：表盘**外围的小刻度线**是否可见
       - `notchTarget`：表盘**刻度间的间隔**像素值
       - `wrapping`：表盘上**首尾刻度是否连贯**。如果设置为`false`，表盘的最小值和最大值刻度之间有一定的空间，否则，表盘刻度是一整圈连续的。默认值是`false`。
   - `QProgressBar`类
     - `QProgressBar` 表示进度条组件，一般以百分比数据来显示进度。`QProgressBar` 的**父类是`QWidget`，它与`QAbstractSlider` 类没有继承关系**。
     - `textDirection`：文字的方向，这表示垂直进度条的文字的阅读方向，包括从上往下和从下往上两种选项。这个属性对于水平进度条无意义。
     - `format`：显示文字的格式，“%p%”显示百分比，“%v”显示当前值，“%m”显示总步数。默认为“%p%”

#### 日期时间数据

1. `Qt` 定义了3 个类用于表示和处理日期时间数据

   - `QTime`：表示时间数据的类，时间数据如12:04:35。
   - `QDate`：表示日期数据的类，日期数据如2021-9-15。
   - `QDateTime`：表示日期时间数据的类，日期时间数据如2021-09-16 17:22:43。
   - 这 3 个类==**都没有父类**==，它们只用于存储日期时间数据，并定义接口函数用于数据处理。
   - 在**界面上==输入和显示==日期时间数据**，`Qt` 定义了几个**用于日期时间数据处理的界面组件类**
     - `QTimeEdit`：编辑和显示时间的组件类。
     - `QDateEdit`：编辑和显示日期的组件类。
     - `QDateTimeEdit`：编辑和显示日期时间的组件类。
     - `QCalendarWidget`：一个用日历形式显示和选择日期的组件类。

2. `QTime`类
   - `QTime `是用于存储和操作时间数据的类，时间数据包含小时、分钟、秒、毫秒。`QTime` 总是用24 小时制，不区分AM/PM。
     - `QTime::QTime(int h, int m, int s = 0, int ms = 0)`
     - **静态函数** `QTime::currentTime()`创建一个`QTime` 对象，并且将其初始化为系统当前时间。
     - <img style="width: 1100px;height:340px" src="image\QTime.png">
   - `QDate`类
     - 可以在定义`QDate`变量时初始化日期数据，也可以使用静态函数`QDate::currentDate()`获取系统的当前日期创建一个`QDate` 变量。
     - ==**静态函数**==`isLeapYear()`可以判断某年是否为闰年
       - `bool QDate::isLeapYear(int year)`
     - <img style="width: 1100px;height:340px" src="image\QDate.png">
   - `QDateTime`类
     - `QDateTime` 是表示日期时间数据的类，包含日期数据和时间数据。`QDateTime` **综合了日期和时间的操作**，**很多函数与`QDate` 和`QTime` 的相似**。
     - <img style="width: 1100px;height:340px" src="image\QDateTime.png">
     - <img style="width: 1100px;height:100px" src="image\QDateTime静态函数.png">
   - 日期时间数据与字符串的转换（日期类都有的静态函数）
     - `QString QDateTime::toString(const QString &format, QCalendar cal = QCalendar())`
       - `format` 是格式化字符串，`cal` 是日历类型，使用默认值就可以
     - **静态函数**`fromString()`
       - `QTime`、`QDate` 和`QDateTime`将字符串转换为相应类的对象。
       - <img style="width: 1100px;height:540px" src="image\dateformat.png">

3. 日期时间数据的界面组件

   - `QDateTimeEdit` 是`QTimeEdit` 和`QDateEdit` 的==**父类**==，而`QDateTimeEdit` 的==**父类**==是 `QAbstractSpinBox`。

     - 日期时间编辑框的特性与`QSpinBox` 的有些相似，只是日期时间编辑框里提供了多个输入段，例如，`QTimeEdit` 有小时、分钟、秒3 个输入段，当光标落在某个段时，点击编辑框右端的上下调节按钮，就可以调节这个段的数值。

     - 属性编辑器中显示的==`QDateTimeEdit` ==的属性

       - `currentSection`：光标所在的日期时间输入段，是枚举类型`QDateTimeEdit::Section`。
       - `currentSectionIndex`：用序号表示的光标所在的段。
       - `calendarPopup`：是否允许弹出一个==**日历**==选择框。当设置为`true` 时，**编辑框右端**的**上下调节**按钮变成**一个下拉**按钮，点击按钮时会出现一个日历选择框，用于在日历上选择日期。
       - `displayFormat`：日期时间数据的显示格式，格式字符的含义如表4-16 所示。

     - `QDateTimeEdit` 有如下3 个信号

       - ```c++
         void dateChanged(QDate date) //日期发生变化时
         void timeChanged(QTime time) //时间发生变化时
         void dateTimeChanged(const QDateTime &datetime) //日期或时间发生变化时
         ```

   - `QCalendarWidget` 类

     - 用于选择日期的日历组件

     - 常用接口函数

       - ```c++
         void showToday() 				 //显示系统当前日期的月历
         void showSelectedDate() 		 //显示所选日期的月历
         QDate selectedDate() 			 //返回选择的日期
         void setSelectedDate(QDate date) //设置选择的日期
             
         //QCalendarWidget 定义了4 个信号
         void activated(QDate date) 				//在日历组件上按Enter键，或双击一个日期时
         void clicked(QDate date) 				//在日历组件上点击一个有效日期时
         void currentPageChanged(int year, int month) //当前显示的月历变化时
         void selectionChanged() 				//当前选择的日期变化时选择
         ```

     - `LineEdit`（`Qt Designer`)

       - `QLineEdit` 的 **`inputMask` (输入掩码)** 强制用户输入特定格式的数据（如时间、IP地址、MAC地址、序列号等）。
       - **`00:00:00` (掩码规则)**:
         - `0`表示该位置**必须**输入一个数字 (0-9)。
         - `:` 表示这是一个分隔符，用户不需要输入，它会自动显示并在光标经过时跳过。
       - `;` 分隔符
         - 分号用于将“掩码规则”与“占位符字符”隔开
       - `_` 占位符字符
         - 分号后面的字符定义了**“当该位置为空时显示什么”**。
         - 正是这里的 `_` 让输入框在没字的时候显示为 `_:_:_`。

#### QTimer和QElapsedTimer

1. `QTimer` 是软件定时器，其父类是`QObject`。`QTimer` 的主要功能是设置以==**毫秒**==为单位的定时==**周期**==，然后进行连续定时或单次定时。启动定时器后，定时**溢出时**`QTimer` 会**发射`timeout()`信号**，为`timeout()`信号关联槽函数就可以进行定时处理。
   - `QElapsedTimer `用于快速==**计算两个事件的间隔时间**==，是软件计时器。`QElapsedTimer` 没有父类，其计时精度可以达到纳
     秒级。`QElapsedTimer` 的主要用途是比较精确地确定一段程序运行的时长。
2. `QTimer`
   - 主要属性和接口函数
     - <img style="width: 1100px;height:240px" src="image\QTimer属性.png">
       - `void QTimer::setTimerType(Qt::TimerType atype)`
         - `Qt::PreciseTimer`：精确定时器，精度尽量保持在毫秒级。
         - `Qt::CoarseTimer`：粗糙定时器，定时误差尽量在定时周期值的5%以内。
         - `Qt::VeryCoarseTimer`：非常粗糙的定时器，精度保持在秒级。
     - 槽函数
       - <img style="width: 1100px;height:140px" src="image\QTime槽函数.png">
     - `QTimer` 只有一个`timeout()`信号
       - 函数`start()`启动定时器后，定时溢出时发射`timeout()`信号。连续定时，周期性地定时溢出和周期性地发射timeout()信号；单次定时，只会发生一次定时溢出和发射一次`timeout()`信号。
     - 静态函数`singleShot()`
       - 用于创建和启动单次定时器并且将定时器的`timeout()`信号与指定的槽函数关联。这个函数有多种参数形式。
         - `void QTimer::singleShot(int msec, Qt::TimerType timerType,
           const QObject *receiver, const char *member)`
3. `QElapsedTimer` 类
   - **它没有父类，不支持Qt 的元对象系统**。
     - `elapsed()`的返回值是自上次运行`start()`之后计时器的运行时间，单位是毫秒。
     - `nsecsElapsed()`的返回值也是自上次运行`start()`之后计时器的运行时间，单位是纳秒。
     - `restart()`返回从上次启动计时器到现在的时间，单位是毫秒，然后重启计时器。相当于先后运行了`elapsed()`和`start()`。
   - `QLCDNumber`的关键属性是`digitCount` 和`smallDecimalPoint`
     - `digitCount `表示显示的数字位数
     - `smallDecimalPoint` 表示是否显示小数点
     - `digitCount` 设置为2，`smallDecimalPoint` 设置为`false`，就只显示
       两位整数

#### QComboBox

1. 它可以提供**下拉列表**供用户**选择输入**，也可以提供**编辑框用于输入文字**。下拉列表框的下拉列表的每个项（`item`，或称为列表项）可以存储一个或多个`QVariant` 类型的用户数据，用户数据并不显示在界面上。

2. `QComboBox` 类的属性和接口函数

   - <img style="width: 1100px;height:400px" src="image\QComBox.png">
     - `QComboBox` 使用**模型/视图**结构存储和显示下拉列表的数据，下拉列表的数据实际上存储在`QStandardItemModel` 模型里，下拉列表是用`QListView` 的子类组件显示的。`modelColumn` 属性表示下拉列表显示的数据在模型中的列编号，默认值为0。关于模型/视图结构的详细原理见第5 章。

3. `QComboBox`的信号

   - 函数中的参数index 是项的序号，text 是项的文字。

   - <img style="width: 1100px;height:140px" src="image\QCombo信号.png">

     - **选择**下拉列表的一个项时，**即使选择的项没有发生变化**，组件也会发射 `activated()`信号
     - 当 `currentIndex` **属性**变化时，不管是用户在界面操作还是程序导致`currentIndex` 变化，组件都会发射`currentIndexChanged()`信号。
     - 当 `currentText` **属性**变化时，不管是用户在界面操作还是程序导致`currentText` 变化，组件都会发射`currentTextChanged()`信号。
     - 在编辑框中**修改文字**时，组件会发射`editTextChanged()`信号
     - 移动鼠标使下拉列表中的**某一项被高亮显示**但还**没有完成选择时**，组件会发射`highlighted()`信号。
     - 在下拉列表中**选择某一项时**，即使**选择的项没有发生变化**，组件也会发射`textActivated()`信号。
     - 当下拉列表中的某一项被高亮显示但还没有完成选择时，组件会发射`textHighlighted()`信号

   - 对列表的操作

     - `addItem()`用于向列表添加一个项，它有两种参数形式

       - `void addItem(const QString &text, const QVariant &userData = QVariant())`

       - `void addItem(const QIcon &icon, const QString &text, const QVariant &userData = QVariant())`

       - 使用函数`addItem()`添加项时，除了可以设置文字，还可以设置图标，或设置`QVariant` 类型数据作为项的用户数据。

       - ```c++
         combo->addItem(QIcon(":/icons/beijing.png"),"北京",1001);
         //userData：程序使用（隐藏）
         if (combo->currentText() == "北京") { ... }//文本可能改，多语言会炸，逻辑和 UI 耦合
         //正确做法
         switch (combo->currentData().toInt()) {
         case 1: ...
         case 2: ...
         }
         ```

     - 函数`addItems()`可以一次性向列表添加多个项

       - `void addItems(const QStringList &texts)`

       - ```c++
         ui->comboBox->clear();
         QStringList strList;
         strList<<"北京"<<"上海"<<"天津"<<"河北省"<<"山东省"<<"山西省";
         ui->comboBox->addItems(strList);
         ```

       - 用函数`addItems()`添加的列表项**只有文字，没有图标和用户数据**。

     - 插入项

       - 函数`insertItem()`可以向列表插入一个项，`insertItems()`可以一次插入多个项

       - ```c++
         void insertItem(int index, const QString &text, const QVariant &userData = QVariant())
         void insertItem(int index, const QIcon &icon, const QString &text,const QVariant &userData = QVariant())
         void insertItems(int index, const QStringList &list)
         ```

       - 这几个函数中的参数与`addItem()`和`addItems()`中同名参数的意义相同，只是多了一个参数`index`，表示插入项的位置序号。如果`index` 大于列表的总项数，就插入列表末尾。

     - 移除项和清除列表

       - ```c++
         void removeItem(int index) //移除序号为index 的项
         void clear() 			   //清除整个列表
         ```

     - 访问列表项

       - ```c++
         int count() 									//返回列表中项的总数
         int currentIndex() 								//返回当前项的序号
         QString currentText() 							//返回当前项的文字
             
         QVariant currentData(int role = Qt::UserRole) 	//返回当前项的用户数据
             
         QString itemText(int index) 					//返回序号为index 项的文字
         QIcon itemIcon(int index) 						//返回序号为index 项的图标
             
         QVariant itemData(int index, int role = Qt::UserRole) //返回序号为index 项的用户数据
             
         void setItemText(int index, const QString &text) 	  //设置序号为index 项的文字
         void setItemIcon(int index, const QIcon &icon) 		  //设置序号为index 项的图标
         void setItemData(int index, const QVariant &value, int role = Qt::UserRole)
         ```

       - `currentData()`或`itemData()`访问用户数据时有一个角色参数`role`，默认值是`Qt::UserRole`，表示用户数据。在使用函数`addItem()`添加项时，若传递了用户数据，用户数据的`role` 值就是`Qt::UserRole`

       - 实际上，**一个项可以设置不止一个用户数据**，用函数 `setItemData()`可以为一个项设置更多的用户数据，例如设置第二个用户数据时，传递`role` 的值为`1+Qt::UserRole` 即可

#### QMainWindow和QAction

1. `QMainWindow` 是主窗口类，具有菜单栏、工具栏、状态栏等主窗口常见的界面元素。要设计主窗口上的菜单栏、工具栏、按钮的下拉菜单、组件的快捷菜单等，需要用到`QAction`类。`QAction` 对象就是实现某个功能的“动作”，我们称其为`Action`。在`UI` 可视化设计时，我们可以设计很多`Action`，然后用`Action` 创建菜单项和工具按钮。

2. 设计`Action`

   - `iconText`：这是用`Action` 创建**工具按钮时**按钮上**显示的文字**。在图4-41 所示对话框中设置了`Text` 属性后，`iconText` 就自动等于`Text`。如果`Text` 设置的文字有...`iconText` 的文字会自动去除...。
     - <img style="width: 1100px;height:400px" src="image\Act编辑器.png">
   - ==`statusTip`==：这是**鼠标移动到菜单项或工具按钮上时**，在主窗口下方状态栏的临时消息区显示的文字，**显示两秒后自动消失**。`statusTip` 一般是对`Action` 比较详细的描述，默认为空。
   - `shortcutContext`：这是`Action` 的**快捷键的有效响应范围**，默认值为`WindowShortcut`，**表示`Action` 关联的组件是当前窗口的子组件时快捷键有效**；如果值为`ApplicationShortcut`，表示只要应用程序有窗口显示，快捷键就有效。
   - `autoRepeat`：表示当**快捷键被==一直按下时==**，`Action` 是否自动重复执行。
   - `menuRole`：==**这个属性在`macOS` 上才有意义**==，表示`Action` 创建的菜单项的作用。
   - `iconVisibleInMenu`：表示在菜单项上是否显示`Action` 的图标。
   - `shortcutVisibleInContextMenu`：表示在使用`Action` 创建右键快捷菜单时，是否显示快捷键。
   - `priority`：表示`Action` 在`UI` 上的优先级，默认值为`NormalPriority`。如果设置为`LowPriority`，当工具栏的`toolButtonStyle` 属性设置为`Qt::ToolButtonTextBesideIcon` 时，按钮上将不显示`Action` 的文字。
   - <img style="width: 1100px;height:400px" src="image\QAction.png">

3. 设计菜单栏和工具栏

   - 菜单栏`QMenuBar`，工具栏`QToolBar`，状态栏`QStatusBar`它们都是直接从`QWidget` 继承而来的。

     - 一个主窗口上最多有一个菜单栏和一个状态栏，可以有多个工具栏。
     - <img style="width: 1100px;height:500px" src="image\qact界面.png">
       - 要设计菜单栏，双击菜单栏上的“Type Here”，会出现一个编辑框，在编辑框里输入所要设计菜单的分组名称，如“**文件(&F)**”，然后按Enter 键，这样就可创建一个“文件(F)”菜单分组。在程序运行时通过快捷键Alt+F 可以便捷地打开“文件”菜单。
     - <img style="width: 800px;height:400px" src="image\菜单栏设计.png">

   - ==**QToolBar类的主要属性**==

     - <img style="width: 1000px;height:200px" src="image\QToolBar类.png">
       - `Qt::ToolButtonIconOnly`：只显示图标
       - `Qt::ToolButtonTextOnly`：只显示文字
       - `Qt::ToolButtonTextBesideIcon`：文字显示在图标旁边
       - `Qt::ToolButtonTextUnderIcon`：文字显示在图标下面
         - 里面的组件显示文字和图片
       - `Qt::ToolButtonFollowStyle`：由`QStyle` 样式定义

   - `QAction` 类

     - `QAction` 类的大部分接口函数是用于**属性读写的函数**，这些接口函数就不具体介绍了，查看`Qt` 帮助文档即可

     - `QAction` 的信号

       - ```c++
         void changed() 							//Action 的text、toolTip、font 等属性值变化时
         void checkableChanged(bool checkable) 	//checkable 属性值变化时
         void enabledChanged(bool enabled) 		//enabled 属性值变化时
         void hovered() 							//鼠标移动到用此Action 创建的菜单项或工具按钮上时
         void toggled(bool checked) 				//checked 属性值变化时
         void triggered(bool checked = false) 	//点击用此Action创建的菜单项或工具按钮时
         void visibleChanged() 					//visible 属性值变化时
         ```

         - 点击由`Action` 创建的菜单项/工具按钮或按下`Action` 的快捷键时，`QAction` 对象发射`triggered()`信号
         - 如果`Action` 的`checkable` 属性值为`true`，还会发射`triggered(bool)`信号，`bool` 类型参数表示当前复选状态
         - `triggered()`==**信号是较常用的**==，一般会为`triggered()`或`triggered(bool)`信号编写槽函数，点击菜单项或工具按钮时，就会运行相关`Action` 的`triggered()`或`triggered(bool)`信号关联的槽函数。
         - 当 `Action` 的`checked` **属性值变化时**，`Action` 会发射`toggled(bool)`信号。点击菜单项或工具按钮可以使`checked` 属性值发生变化，在程序中运行`QAction::setChecked()`函数也可以使`checked` 属性值发生变化。

     - `QAction` 的公有槽

       - ```c++
         void hover() 			//触发hovered()信号
         void trigger() 			//触发triggered()信号
         void resetEnabled() 	//复位enabled 属性为默认值
         void setChecked(bool) 	//设置checked 属性的值
         void setDisabled(bool b) //设置enabled 属性的值，若b=true，设置enabled=false
         void setEnabled(bool) //设置enabled 属性的值
         void setVisible(bool) //设置visible 属性的值
         void toggle() 			//反转checked 属性的值
         ```

       - `hover()`和`trigger()`用于触发相应的信号，其他槽函数用于设置`Action` 的一些属性

       - `QPlainTextEdit` 提供编辑操作的公有槽，如`cut()`、`copy()`、`paste()`、`undo()`等

   - `QToolBar` 类

     - 在`UI` 可视化设计时，可以用`Action` 可视化地创建工具栏上的按钮，但是==**不能可视化地在工具栏上放置其他组件**==（如QProgressBar)。`QToolBar` 提供了接口函数，可以通过代码在工具栏上添加组件，从而灵活地设计工具栏。

       - ```c++
         void addAction(QAction *action) 			//添加一个Action，并根据Action 的设置自动创建工具按钮
         QAction *addWidget(QWidget *widget) 		//添加一个界面组件
         QAction *insertWidget(QAction *before, QWidget *widget) //插入一个界面组件
         QAction *addSeparator() 					//添加一个分隔条
         QAction *insertSeparator(QAction *before) 	//插入一个分隔条
         ```

         - `QToolBar` 定义了一些信号，这些信号基本都是某个属性值变化时发射的信号

   - `QStatusBar` 类

     - 添加组件

       - ==**在UI 可视化设计时，不能在状态栏上放置任何组件**==，而只能通过其接口函数向状态栏添加组件。

         - ```c++
           void addWidget(QWidget *widget, int stretch = 0) //添加正常组件
           void addPermanentWidget(QWidget *widget, int stretch = 0) //添加永久组件
           ```

           - `widget` 可以是从`QWidget` 继承来的任何组件，一般是适合放置在状态栏上的组件，如`QLabel`、`QSpinBox`、`QProgressBar` 等。参数`stretch` 是延展因子
           - 函数 `addWidget()`添加的组件按添加的**先后顺序**，从状态栏左端开始从左到右排列，也就是**左对齐**。函数`addPermanentWidget()`添加的组件按添加的先后顺序从左到右排列，但是为**右对齐**，也就是最后添加的组件在状态栏右端。
           - 使用 `addWidget()`或`addPermanentWidget()`添加组件后，就可以在组件上显示信息了，例如添加的是一个`QLabel` 组件，就在这个`QLabel` 组件上显示信息即可。

       - 显示临时消息

         - ```c++
           void showMessage(const QString &message, int timeout = 0) //显示临时消息
           void clearMessage() //清除临时消息
           ```

         - 函数`showMessage()`用于在**状态栏上==左端首位==置显示字符串信息**，显示**持续时间**是`timeout`，单位是**毫秒**。如果`timeout` 设置为`0`，就是一直显示，直到被`clearMessage()`清除，或显示下一条临时消息。

         - 使用`showMessage()`显示临时消息时，状态栏上用`addWidget()`添加的组件会被临时隐藏，而用`addPermanentWidget()`函数添加的组件会保持不变。

       - 自动显示`Action` 的`statusTip`

         - 如果一个`Action` 的`statusTip` **属性不为空**，当鼠标移动到如果一个`Action` 的`statusTip` 属性不为空，当鼠标移动到由这个`Action` 创建的菜单项或工具按钮上时，状态栏上就会自动显示这个`Action` 的`statusTip` 属性的内容；当鼠标移出时，状态栏上的临时消息就会被自动清除。使用这个功能无须编写任何代码，只需要设置`Action` 的`statusTip` 属性。

4. 混合式UI 设计

   - 一般情况下，尽量用可视化方式设计界面。如果一部分界面无法用可视化方式设计完成，就需要编写部分代码，在窗口类的构造函数里用代码创建这部分界面，我们称这种设计方式为混合式UI 设计。
     - 将两个`Action` 添加到所创建的`actionGroup` 里，才可以实现两个`Action` 互斥选择的功能。
     - `QPlainTextEdit` 的信号
       - <img style="width: 1000px;height:250px" src="image\QPlainTextEdit信号.png">


#### QToolButton 和QListWidget

1. `Qt` 中用于**处理项数据**（item data）的组件有两类

   - 一类是`Item Views` 组件，包括`QListView`、`QTreeView`、`QTableView `等；
   - 另一类是`Item Widgets` 组件，包括`QListWidget`、`QTreeWidget`、
     `QTableWidget` 等
   - `Item Widgets` 组件使用起来稍微复杂一点。它们直接将数据存储在每一个项里，例如，`QListWidget` 的每一行是一个项，`QTreeWidget` 的每个节点是一个项，`QTableWidget` 的每一个单元格是一个项。一个项存储了文字、文字的格式定义、图标、用户数据等内容。
   - `QToolButton` 有一个**`setDefaultAction()`函数**，可以使==**按钮与`Action` 关联**==，按钮的文字、图标、`toolTip` 等属性都将自动从关联的`Action` 复制而来。点击一个工具按钮时就会运行关联`Action` 的`triggered()`信号的槽函数。
     - 在 `Qt Designer` 里并**不能**直接为一个==**工具**==按钮设定一个`Action`，而需要在窗口类的构造函数里编写代码，为界面上的各个工具按钮设置关联的`Action`。

2. `QToolBox` 组件

   - `QToolBox` 是工具箱组件类，工具箱是一种**垂直分页**的**多页容器组件**。
   - 在`UI` 可视化设计时，在工具箱组件上点击鼠标右键调出快捷菜单，可以分别使用`Insert Page` 和`Delete Page` 菜单项添加和删除页面。
   - 工具箱的**每个页面就是一个 `QWidget` 组件**在页面的工作区可以放置任何其他界面组件
   - 在切换当前页面时组件发射此信号，参数`index` 是当前页面序号
     - `void QToolBox::currentChanged(int index)`
   - `QToolBox` 类提供了用于页面控制、属性访问的各种接口函数，查阅`Qt` 帮助文档
   - <img style="width: 1000px;height:250px" src="image\QAction设计.png">

3. QListWidget 组件

   - `QListWidget` 是列表组件，每**一行是一个**`QListWidgetItem` **类型的对象**，称为**项或列表项**。
   - `QListWidgetItem`有一个**标志变量**`flags`，用于**设置列表项的特性**，`flags` 是枚举类型`Qt::ItemFlag` 的枚举值的组合。
     - `Selectable` ： 列表项可被选择， 对应枚举值`Qt::ItemIsSelectable`。
     - `Editable`：列表项可被编辑，对应枚举值`Qt::ItemIsEditable`。
     - `DragEnabled`：列表项可以被拖动，对应枚举值`Qt::ItemIsDragEnabled`。
     - `DropEnabled`：列表项可以接收拖放的项
     - `UserCheckable`：列表项可以被复选，若为`true`，列表项前面会出现一个复选框
     - `Enabled`：列表项可用，
     - `Tristate`：**自动改变列表项的复选状态**，对应枚举值`Qt::ItemIsAutoTristate`。该==**特性对`QTreeWidget` 的节点有效，对`QListWidget` 的列表项无效**==。

4. `QToolButton` 与界面补充创建

   - `QToolButton` 的属性
     - **一个工具按钮关联一个 `Action` 后，按钮的文字、图标、`toolTip` 等属性都将自动从关联的`Action`复制而来**。但是在`UI` 可视化设计时，我们无法为工具按钮设置关联的`Action`。
     - `popupMode` 属性。当按钮==**有下拉菜单**==时，这个属性决定了弹出菜单的模式
       - `QToolButton::DelayedPopup`：按钮上没有任何附加的显示内容。如果按钮有下拉菜单，按下按钮并延时一会儿后，才显示下拉菜单。
       - `QToolButton::MenuButtonPopup`：会在按钮右侧**显示一个带箭头图标**的**下拉按钮**。==**点击下拉按钮**==才显示下拉菜单
         - **点击工具按钮**会执行按钮关联的Action，而不会显示下拉菜单。
       - `QToolButton::InstantPopup`：会在按钮的**右下角显示一个很小的下拉箭头图标**，==**点击按钮就会立刻显示下拉菜单，即使工具按钮关联了一个`Action`，也不会执行这个`Action`**==
     - `toolButtonStyle` 属性。属性值是枚举类型`Qt::ToolButtonStyle`，表示工具按钮上文字与图标的显示方式
     - `autoRaise` 属性。如果设置为`true`，按钮就没有边框，鼠标移动到按钮上时才显示按钮边框。
     - `arrowType` 属性。属性值是枚举类型`Qt::ArrowType`
       - 可以在按钮上显示表示方向的箭头图标
   - `QToolButton` 的其他接口函数
     - `setDefaultAction()`函数。这个函数用于为工具按钮设置关联的`Action`。设置关联的`Action`后，工具按钮的文字、图标、`toolTip` 等属性都与`Action` 的一样，工具按钮的`triggered()`信号自动关联`Action` 的`triggered()`信号。
     - `setMenu()`函数。这个函数用于为工具按钮设置下拉菜单
       - `void QToolButton::setMenu(QMenu *menu)`
       - `QMenu` 是菜单类，它直接从`QWidget` 继承而来。要为工具按钮设计下拉菜单，需要通过代码动态创建`QMenu` 对象，然后通过函数`setMenu()`将其设置为工具按钮的下拉菜单。

5. 代码补充创建界面

   - `QMenu` 是管理菜单的类，它的父类是`QWidget`，菜单实际上是一种窗口

     - ```c++
       void QWidget::addAction(QAction *action) 	//添加Action，创建菜单项
       QAction *QMenu::addMenu(QMenu *menu) 		//添加菜单，创建子菜单
       QAction *QMenu::addSeparator() 				//添加一个分隔条
       ```

     - `QWidget::addAction()`是`QMenu` 的父类`QWidget` 中定义的函数，它会添加`Action`，并自动创建菜单项。`QMenu` 中还定义了多种参数形式的`addAction()`函数，通过已设计好的`Action` 创建菜单项是较简单的。

     - **显示菜单**可以使用函数 `exec()`

       - `QAction *QMenu::exec(const QPoint &p, QAction *action = nullptr)`
       - 参数p 表示菜单的左上角坐标。在点击鼠标右键显示快捷菜单时，**一般使用鼠标光标的当前==位置`QCursor::pos()`作==为参数`p` 的值**

6. `QListWidget` 的操作

   - <img style="width: 1000px;height:250px" src="image\listwidget.png">

     - `QListWidget` 组件的列表项是`QListWidgetItem` 对象。`QListWidgetItem` 类没有父类。

     - `QListWidget` 的主要接口函数

       - <img style="width: 1000px;height:450px" src="image\listwidget接口.png">
       - `QListWidgetItem` 的函数`setFlags()`用于设置项的一些特性，如是否可选、是否可编辑、是否有复选框等，
         - `setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable)`
         - `takeItem()`函数的功能==**只是从列表中移除一个项，并不会删除**==这个
           `QListWidgetItem` 对象，如果要彻底删除这个项，需要使用`delete` 显式地删除它。
         - `sortingEnabled`，表示列表是否**==动态自动==**排序，默认值为`false`
           - 新添加的项进行动态的排序。

       - `QListWidget` 的信号

         - ```c++
           void currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
           void currentRowChanged(int currentRow) 				//当前项发生了切换
           void currentTextChanged(const QString &currentText) //当前项发生了切换
           void itemSelectionChanged() 						//表示选择的项发生了变化
           void itemChanged(QListWidgetItem *item) 			//项的属性发生了变化，如文字、复选状态等
           void itemActivated(QListWidgetItem *item) //光标停留在某个项上，按Enter 键时发射此信号
           void itemEntered(QListWidgetItem *item)   //鼠标跟踪时
           void itemPressed(QListWidgetItem *item)   //鼠标左键或右键按下
           void itemClicked(QListWidgetItem *item)   //点击
           void itemDoubleClicked(QListWidgetItem *item) //双击
           ```

7. 创建右键快捷菜单

   - 每个继承自`QWidget` 的类都有`customContextMenuRequested()`信号，在==**一个组件上**==点击鼠标右键时，组件发射这个信号，用于请求创建快捷菜单。如果为此信号编写槽函数，就可以创建和运行快捷菜单
   - 要使 `QWidget` 组件在点击鼠标右键时发射`customContextMenuRequested()`信号，还需要设置其`contextMenuPolicy` 属性
     - `Qt::NoContextMenu`：组件没有快捷菜单，由其父容器组件处理快捷菜单
     - `Qt::PreventContextMenu`：阻止快捷菜单，并且点击鼠标右键事件也不会交给父容器组件处理
     - `Qt::DefaultContextMenu`：默认的快捷菜单，组件的`QWidget::contextMenuEvent()`事件被自动处理。
       - 某些组件有自己的默认快捷菜单，例如`QPlainTextEdit` 的`contextMenuPolicy` 属性默认设置为这个值，在无须任何编程的情况下，运行时点击鼠标右键就会出现一个标准的编辑操作快捷菜单，只是菜单文字是英文的。
     - `Qt::ActionsContextMenu`：自动根据`QWidget::actions()`返回的`Action` 列表创建并显示快捷菜单
     - `Qt::CustomContextMenu`：组件发射`customContextMenuRequested()`信号，由用户编程实现



#### QTreeWidget

1. 简介

   - `QTreeWidget` 是一种`Item Widget` 组件。`QTreeWidget` 组件被称为树形组件，它的**项**（`item`）被称为**节点**，一个树形组件内
     的所有**节点组成的结构称为目录树**。树形组件适合显示具有层级结构的数据。

2. `QDockWidget`

   - 属性
     - `floating` 属性，停靠区组件是否处于浮动状态。通过函数`isFloating()`可以返回此属性值，通过函数`setFloating(bool)`可以设置此属性值。
     - `features` 属性，停靠区组件的特性。函数`setFeatures()`用于设置此属性值
     - `allowedAreas `属性：允许停靠区域
     - `windowTitle` 属性：==**停靠区窗口的标题**==
     - 最后两个属性并不是`QDockWidget` 类中定义的属性
       - `docked` 属性为`true`，可以使`dockWidget` 处于停靠状态；设置其为`false`，则可以使`dockWidget` 处于浮动状态
     - <img style="width: 1000px;height:400px" src="image\DockWidget.png">

3. `QTreeWidget` 组件的可视化设计

   - 双击窗体上的`QTreeWidget` 组件可以打开组件的编辑器，编辑器有**两个页面**，可分别==**对`Columns` 和`Items`** ==进行设计。
     - `Columns`页面用于设计树形组件的==**列**==。在编辑器里可以添加、删除、移动列，以及设置每一列的标题文字、字体、前景色、背景色、文字对齐方式、图标等。
       - 在UI 可视化设计时，我们设置了两个列，标题分别为“节点”和“节点类型”，且两个列的标题文字对齐方式不同，如图4-58 所示
     - `Items` 页面用于==**设计树形组件的节点**==。如图4-59
   - 树形组件中的==**一行是一个节点**==，==**一个节点可以有多列**==，每一列可以==**单独设置**==文字、图标、复选状态等属性。图4-59 中右侧的属性分为两组，`Per column properties` 组是节点的每一列单独设置的属性，包括文字、图标、字体、背景色、复选状态等；`Common properties` 组是节点各列共有的属性，只有一个`flags` 属性，用于设置节点的标志，可以设置节点是否可选、是否可编辑、是否有复选框等。
     - <img style="width: 1000px;height:400px" src="image\item页面.png">

4. `QTreeWidget` 类

   - 表头

     - 树形组件有表头，**表头可以只是简单的文字**，**也可以==设置为`QTreeWidgetItem` 对象==**。当使用`QTreeWidgetItem` 对象作为**表头**时，不仅可以设置表头每一列的文字，还可以设置字体、对齐方式、背景色、图标等显示特性。
       - 如果==**只是简单地设置表头文字**==，可以使用函数`setHeaderLabels()`将字符串列表的内容作为表头==**各列**==的标题
         - `void QTreeWidget::setHeaderLabels(const QStringList &labels)`

     - 如果创建了`QTreeWidgetItem` 对象作为表头，就可以使用函数`setHeaderItem()`设置表头，还可以用函数`headerItem()`返回表头的`QTreeWidgetItem` 对象指针

   - ```c++
         void QTreeWidget::setHeaderItem(QTreeWidgetItem *item)  //设置表头节点
         QTreeWidgetItem *QTreeWidget::headerItem() 				//返回表头节点
     ```

   - 顶层节点

     - 目录树里一行就是一个节点，节点是`QTreeWidgetItem` 对象

     - 目录树里最上层的节点称为顶层节点，顶层节点没有父节点。

     - `QTreeWidget `类中有如下一些**用于==顶层节点==操作的接口函数**

     - ```c++
       int topLevelItemCount() 							//返回顶层节点的个数
       void addTopLevelItem(QTreeWidgetItem *item) 		//添加一个顶层节点
       void insertTopLevelItem(int index, QTreeWidgetItem *item) //插入一个顶层节点
       int indexOfTopLevelItem(QTreeWidgetItem *item) 		//返回一个顶层节点的索引号
       QTreeWidgetItem *topLevelItem(int index) 			//根据索引号获取一个顶层节点
       QTreeWidgetItem *takeTopLevelItem(int index) 		//移除一个顶层节点，但是并不删除这个节点对象
       ```

       - 获取一个顶层节点对象后，就可以访问它的所有子节点。

   - 次级节点

     - 所有次级节点都直接或间接挂靠在某个顶层节点下面
     - 一个节点可以访问它的所有直接子节点，可以通过递归的方法遍历其所有直接和间接子节点。所以，从顶层节点开始，就可以遍历整个目录树。

   - ==**隐藏的根节点**==

     - 目录树中还有一个**隐藏的根节点**，其**可以看作所有==顶层节点==的父节点**。函数`invisibleRootItem()`可以返回这个隐藏的根节点
     - `QTreeWidgetItem *QTreeWidget::invisibleRootItem()`
       - 使用这个隐藏的根节点，就可以通过`QTreeWidgetItem` 类的接口函数访问所有顶层节点，这样在实现一些对顶层节点和次级节点进行操作的函数时，可以使用相同的程序。

   - `QTreeWidget` 的其他接口函数

     - ```c++
       int columnCount() 				//返回表头列数
       void setColumnCount(int columns) //设置表头列数
       void sortItems(int column, Qt::SortOrder order) //将目录树按照某一列排序
       int sortColumn() 								//返回用于排序的列的序号
       QTreeWidgetItem *currentItem() 					//返回当前节点
       QList<QTreeWidgetItem*> selectedItems() 		//返回选择的节点的列表
       ```

     - 目录树上有一个当前节点，也就是**通过点击鼠标或按键移动选择**的节点。函数`currentItem()`会返回当前节点，如果返回值为`nullptr`，就表示没有当前节点。

     - 如果**树形组件允许多选**，函数`selectedItems()`会返回选择的节点的列表。通过`QTreeWidget` 的**上层父类**`QAbstractItemView` 的`selectionMode` 属性能够**设置选择模式**，可以设置为多选。

   - `QTreeWidget` 的公有槽

     - ```c++
       void clear() 									//清除整个目录树，但是不清除表头
       void collapseItem(const QTreeWidgetItem *item) 	//折叠节点
       void expandItem(const QTreeWidgetItem *item) 	//展开节点
       void scrollToItem(const QTreeWidgetItem *item, QAbstractItemView::ScrollHint hint = EnsureVisible)
       ```

     - 函数`scrollToItem()`用于确保节点`item` 可见，必要时自动移动树形组件的卷滚条。

   - `QTreeWidget` 的信号

     - ```c++
       void currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
       void itemActivated(QTreeWidgetItem *item, int column) 			//点击或双击节点时
       void itemChanged(QTreeWidgetItem *item, int column)
       void itemClicked(QTreeWidgetItem *item, int column)
       void itemCollapsed(QTreeWidgetItem *item) 						//节点折叠时
       void itemDoubleClicked(QTreeWidgetItem *item, int column)
       void itemEntered(QTreeWidgetItem *item, int column) 			//鼠标光标移动到节点上时
       void itemExpanded(QTreeWidgetItem *item) 						//节点展开时
       void itemPressed(QTreeWidgetItem *item, int column)
       void itemSelectionChanged()
       ```

       - `currentItemChanged()`信号在当前节点发生变化时被发射，`current` 是当前节点，`previous` 是之前节点，==**这两个参数的值有可能为`nullptr`**==。注意，即使当前点击的**行没有变化**，但是被点击节点的**列发生了变化**，组件也会发射此信号。
       - `itemChanged()`信号在节点的某一列的属性发生变化时被发射，例如文字变化、复选状态变化
       - `itemClicked()`信号在点击节点时被发射，不管当前节点的行和列有没有变化都会触发此信号。用户在目录树上按下鼠标左键或右键时，组件会发射`itemPressed()`信号。
       - `itemSelectionChanged()`信号在用户选择的节点发生变化时被发射，在当前节点切换或多选节点变化时都会触发此信号。
       - ==**不希望`qDebug()`输出信息的.pro 文件里增加`DEFINES += QT_NO_DEBUG_OUTPUT`**==

5. `QTreeWidgetItem` 类

   - `QTreeWidget` **组件的表头和目录树节点**都是`QTreeWidgetItem` 类对象，对**目录树节点的操作主要通过**`QTreeWidgetItem` **类的接口函数实现**。`QTreeWidgetItem` 类**没有父类**，它只用来存储节点的数据和各种属性，绘制目录树由`QTreeWidget` 实现。

   - 创建`QTreeWidgetItem` 对象

     - `QTreeWidgetItem` 类有多种参数形式的构造函数，较简单的一种定义如下`QTreeWidgetItem(int type = Type)`
       - 可以传递一个整数表示节点的类型，这个类型参数是一个自定义的数据。通过**成员函数`type()`可以返回这个类型**，如何使用这个类型数据由用户程序决定。
       - 使用这个构造函数创建节点后，**还需要调用` QTreeWidgetItem` 类的各种接口函数设置节点各列的文字、图标、复选状态等属性。**然后，可以通过`QTreeWidget::addTopLevelItem()`函数将创建的节点添加**成目录树的顶层节点**，或通过`QTreeWidgetItem::addChild()`函数将其添加成**一个节点的子节点**。
     - 在创建节点时，还可以传递==**字符串列表**==作为节点**各列**的文字，这种构造函数定义如下：`QTreeWidgetItem(const QStringList &strings, int type = Type)`
     - 可以直接在==**某个节点下创建子节点**==，这种构造函数定义如下：`QTreeWidgetItem(QTreeWidgetItem *parent, int type = Type)`
     - 还可以==**直接在树形组件里创建顶层节点**==，这种构造函数定义如下：`QTreeWidgetItem(QTreeWidget *parent, int type = Type)`

   - 访问节点各列数据的接口函数

     - ```c++
       //创建一个节点后，可以设置节点每一列的文字、字体、对齐方式、复选状态等数据
       //按列设置数据的接口函数主要有以下几个，函数中的参数column 是列的编号，0 表示第一列
       void setBackground(int column, const QBrush &brush) 	//设置背景色
       void setForeground(int column, const QBrush &brush) 	//设置前景色
       void setText(int column, const QString &text) 			//设置文字
       void setTextAlignment(int column, int alignment) 		//设置文字对齐方式
       void setToolTip(int column, const QString &toolTip) 	//设置toolTip 文字
       void setStatusTip(int column, const QString &statusTip) //设置statusTip 文字
       void setIcon(int column, const QIcon &icon) 			//设置图标
       void setCheckState(int column, Qt::CheckState state) 	//设置复选状态
       void setFont(int column, const QFont &font) 			//设置字体
       ```

     - `QTreeWidgetItem` 还有一个函数`setData()`可以为节点的某一列设置用户数据，这个数据是不显示在界面上的。

       - `void setData(int column, int role, const QVariant &value)`
       - `QVariant data(int column, int role)`

   - 对节点==**整体特性**==进行操作的接口函数

     - ```c++
       //QTreeWidgetItem 的一些接口函数用于设置或读取节点的整体特性
       int type() 						//返回在创建节点时设置的type 参数
       void setExpanded(bool expand) //使节点展开或折叠
       bool isExpanded()
       void setDisabled(bool disabled) //设置是否禁用此节点
       bool isDisabled()
       void setHidden(bool hide) //设置是否隐藏此节点
       bool isHidden()
       void setSelected(bool select) //设置此节点是否被选中
       bool isSelected()
       ```

       - 注意，函数`type()`返回的是创建节点时传递的`type` 参数，节点创建后就不能更改节点类型了。还有一个函数 `setFlags()`用于设置节点的一些特性，

     - ```c++
       void setFlags(Qt::ItemFlags flags) //设置节点的标志
       Qt::ItemFlags flags() //读取节点的标志
       
       Qt::NoItemFlags 		//没有任何标志
       Qt::ItemIsSelectable 	//节点可以被选中
       Qt::ItemIsEditable 		//节点可以被编辑
       Qt::ItemIsDragEnabled 	//节点可以被拖动
       Qt::ItemIsDropEnabled 	//节点可以接受拖来的对象
       Qt::ItemIsUserCheckable //可以被复选，节点前面会出现一个复选框
       Qt::ItemIsEnabled 		//节点可用
       Qt::ItemIsAutoTristate 	//自动决定3 种复选状态
       Qt::ItemNeverHasChildren //不允许有子节点
       Qt::ItemIsUserTristate //用户决定3 种复选状态    
       ```

   - 操作子节点的接口函数

     - ```c++
       void addChild(QTreeWidgetItem *child) 	//添加一个子节点
       QTreeWidgetItem *child(int index) 		//根据序号返回一个子节点
       int childCount() 						//返回子节点的个数
       int indexOfChild(QTreeWidgetItem *child) //返回一个子节点的索引号
       void insertChild(int index, QTreeWidgetItem *child) //插入一个子节点
       void removeChild(QTreeWidgetItem *child) 			//移除一个子节点
       QTreeWidgetItem *takeChild(int index) 				//移除一个子节点，并返回这个节点的指针
       ```

     - `removeChild()`和`takeChild()`都是从目录树上移除一个子节点，但是这个节点对象==**并不会被自动从内存中删除**==。

   - 父节点

     - 在目录树中，除了顶层节点，其他节点都有一个父节点，用**函数`parent()`可以返回父节点的指针**。`QTreeWidgetItem *parent()`如**果`parent()`函数返回的是`nullptr`，就表示没有父节点**。
     - 虽然顶层节点没有直观的父节点，但是 `QTreeWidget` 类有一个函数`invisibleRootItem()`可以返回目录树的隐藏根节点，这个隐藏根节点可以看作顶层节点的父节点，可以通过`QTreeWidgetItem`的接口函数操作所有顶层节点。
     - `QPixmap` 类存储图片数据
     
       - `scaledToHeight(int height)`：返回一个缩放后的图片副本，图片缩放到高度`height`
       - `scaledToWidth(int width)`：返回一个缩放后的图片副本，图片缩放到宽度`width`
       - `scaled(int width, int height)`：返回一个缩放后的图片副本，图片缩放到宽度`width` 和高度
         `height`，默认是不保持比例
       - 使用`QLabel` 的`setPixmap()`函数即可显示图片，其函数原型定义如下：`void QLabel::setPixmap(const QPixmap &)`
     - QDockWidget 类有如下几个信号，信号发射的时机见注释。
     
       - ```c++
         void allowedAreasChanged(Qt::DockWidgetAreas allowedAreas) //allowedAreas属性值变化时
         void dockLocationChanged(Qt::DockWidgetArea area) //移动到其他停靠区时
         void featuresChanged(QDockWidget::DockWidgetFeatures features) //features 属性值变化时
         void topLevelChanged(bool topLevel) //floating 属性值变化时
         void visibilityChanged(bool visible) //visible 属性值变化时
         ```

#### QTableWidget

1. 简介
   - <img style="width: 600px;height:400px" src="image\tablewidget.png">
   - 以表格形式显示和管理数据。
   - 表格的第一行称为水平表头用于设置每一列的标题
   - 第一列称为垂直表头也可以设置其标题，但**一般使用默认的标题**，**也就是行号**
   - 表头和垂直表头一般是不可编辑的。除水平表头和垂直表头之外的表格区域是数据区，数据区呈规则的网格状，
   - 一个网格称为单元格（`cell`）。==**每个单元格关联一个`QTableWidgetItem` 对象**==，可以设置每个单元格的文字内容、字体、前景色、背景色、图标等，单元格还可以有复选框或设置为其他`widget` 组件。每个单元格还可以存储用户数据。

2. `QTableWidget` 类

   - 表格行和列

     - `QTableWidget` 是`QTableView` 的便利类。`QTableWidget` **的属性和接口函数==主要是父类中定义的==**
     - `QTableWidget` 新增了两个**属性**，`rowCount` 表示**数据区**行数`columnCount` 表示**数据区**列数。

     - ```c++
       void insertColumn(int column) //在列号为column 的位置插入一个空列
       void removeColumn(int column) //移除列号为column 的一列
       void insertRow(int row) //在行号为row 的位置插入一个空行
       void removeRow(int row) //移除行号为row 的一行
       ```

   - 单元格关联的`QTableWidgetItem` 对象

     - 要为表格的一个**单元格设置项**，一般是先创建一个`QTableWidgetItem` 对象`item`，设置其各种属性，然后用函数`setItem()`将`item` 设置为某个单元格的项。

       - `void setItem(int row, int column, QTableWidgetItem *item)`
         - `row` 和`column` 分别是单元格的行号和列号
       - `QTableWidgetItem *takeItem(int row, int column)`
       - 函数`takeItem()`会移除单元格关联的项，并返回这个项的对象指针，但并不删除这个对象。若要释放对象占用的内存，需要用`delete` 删除对象。

     - ```c++
       //QTableWidget 定义了两个公有槽，可以用来清除整个表格或数据区的全部单元格的项。
       void clear() 		//清除表头和数据区的所有项
       void clearContents() //清除数据区的所有项
       ```

   - **当前单元格和当前项**

     - `QTableWidget` 表格数据区有一个当前单元格，也就是获得输入焦点的单元格。可以返回当前单元格的行号和列号，也可以通过行号和列号设置当前单元格。

     - ```c++
       int currentRow() 			//返回当前单元格的行号
       int currentColumn() 		//返回当前单元格的列号
       void setCurrentCell(int row, int column) //通过行号和列号设置当前单元格
       ```

     - 当前单元格关联的`QTableWidgetItem` 对象就是当前项，可以返回当前项的对象指针。也可以设置某个`QTableWidgetItem` 对象为当前项，以改变当前单元格的位置。

     - ```c++
       QTableWidgetItem *currentItem() 			//返回当前单元格的项
       void setCurrentItem(QTableWidgetItem *item) //设置当前项，改变当前单元格的位置
       ```

   - 单元格的索引

     - 为表格的每个单元格关联一个项之后，可以在表格内通过行号和列号获取每个单元格的项，项也有自己的行号和列号。

     - ```c++
       QTableWidgetItem *item(int row, int column) //通过行号和列号返回项
       int row(const QTableWidgetItem *item) 		//返回一个项的行号
       int column(const QTableWidgetItem *item) 	//返回一个项的列号
       ```

   - **水平表头**

     - 水平表头的每个单元格可以设置一个项

     - ```c++
       void setHorizontalHeaderItem(int column, QTableWidgetItem *item) //为某列设置项
       QTableWidgetItem *horizontalHeaderItem(int column) //返回column 列的表头项
       QTableWidgetItem *takeHorizontalHeaderItem(int column) //移除column 列的表头项
           
       void setHorizontalHeaderLabels(const QStringList &labels)
       //这个函数使用一个字符串列表的每一行作为水平表头每一列的标题，使用默认的格式。
       ```

     - 通过为水平表头的每个单元格设置项就可以定义表头的具体格式，例如使用不同的背景色

     - 如果只是设置表头文字而不需要设置任何特殊的格式，可以使用一个简化的函数来实现

   - **垂直表头**

     - ==**默认情况下**==，**垂直表头会自动显示行号**，不需要专门操作。垂直表头的每个单元格可以设置一个项或直接设置标题文字。

     - ```c++
       void setVerticalHeaderItem(int row, QTableWidgetItem *item) //设置row 行的表头项
       QTableWidgetItem *verticalHeaderItem(int row) 				//返回row 行的表头项
       QTableWidgetItem *takeVerticalHeaderItem(int row) 			//移除row 行的表头项
       void setVerticalHeaderLabels(const QStringList &labels) 	//用一个字符串列表设置表头标题
       ```

   - `QTableWidget` 的==**信号**==

   - ```c++
     void cellActivated(int row, int column) 		//单元格被激活时
     void cellChanged(int row, int column) 			//单元格的数据内容改变时
     void cellClicked(int row, int column) 			//在单元格上点击鼠标时
     void cellDoubleClicked(int row, int column) 	//在单元格上双击鼠标时
     void cellEntered(int row, int column) 			//鼠标移动到一个单元格上时
     void cellPressed(int row, int column) 			//在单元格上按下鼠标左键或右键时
     void currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn) //当前单元格发生切换时
     void itemActivated(QTableWidgetItem *item)
     void itemChanged(QTableWidgetItem *item)
     void itemClicked(QTableWidgetItem *item)
     void itemDoubleClicked(QTableWidgetItem *item)
     void itemEntered(QTableWidgetItem *item)
     void itemPressed(QTableWidgetItem *item)
     void currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
     void itemSelectionChanged() 					//选择的项发生变化时
     ```

     - 这些**信号**主要分为**两大类**，一类以单元格的行号和列号作为参数，另一类以`QTableWidgetItem` 对象作为参数。
     - 例如，当前单元格发生切换时，会同时发射`currentCellChanged()`信号和`currentItemChanged()`信号`currentCellChanged()`信号传递4 个参数，即当前单元格的行号和列号以及之前单元格的行号和列号；`currentItemChanged()`信号传递两个参数，即当前项和之前的项。用户编写处理程序时，根据处理需要选择其中一个信号进行处理即可。
     - `itemSelectionChanged()`信号在选择的项发生变化时被发射，==**如果表格允许多选单元格，当用户按住Ctrl 键选择的单元格发生变化时，组件就会发射此信号**。==

3. `QTableWidgetItem` 类

   - `QTableWidgetItem`类**没有父类**，**它存储了单元格的文字及其格式定义**，`QTableWidget` 就是根据每个单元格的项定义的各种属性绘制表格的。

   - 创建`QTableWidgetItem` 对象

     - ```c++
       QTableWidgetItem(const QIcon &icon, const QString &text, int type = Type)
       QTableWidgetItem(const QString &text, int type = Type)
       QTableWidgetItem(int type = Type)
       ```

     - 不管哪个构造函数，都需要传递一个参数`type` 表示项的类型，类型由用户定义和使用。项被创建后，其类型就不能再改变，通过`QTableWidgetItem::type()`函数可以返回项的类型。

     - `QTableWidget::setItem()`函数可以将其设置为某个单元格的项。

   - 项的设置

     - ```c++
       void setText(const QString &text) 		//设置单元格显示的文字
       void setTextAlignment(int alignment) 	//设置文字对齐方式
       void setBackground(const QBrush &brush) //设置背景色
       void setForeground(const QBrush &brush) //设置前景色，即文字的颜色
       void setFont(const QFont &font) 		//设置字体
       void setIcon(const QIcon &icon) 		//设置图标
       void setCheckState(Qt::CheckState state) 	//设置复选状态
       void setToolTip(const QString &toolTip) 	//设置toolTip
       void setStatusTip(const QString &statusTip) //设置statusTip
       ```

     - **项被设置为可复选的，在单元格里会出现一个复选框**，函数`setCheckState()`可设置项的复选状态。每个设置函数都有对应的读取函数，

     - `void setFlags(Qt::ItemFlags flags)`

       - `Qt::ItemFlag`的各枚举值表示项的特性，包括项是否可选、是否可编辑、是否可复选等。

       - ```c++
         void setData(int role, const QVariant &value)
         QVariant data(int role)
         ```

       - 参数role 是用户数据角色，可以使用常量`Qt::UserRole` 定义第一个用户数据，使`1+Qt::UserRole` 定义第二个用户数据。

   - 与表格相关的接口函数

     - ```c++
       int row() 		//返回项所在单元格的行号
       int column() 	//返回项所在单元格的列号
       void setSelected(bool select) 	//设置项的选中状态
       bool isSelected() 				//项是否被选中，也就是单元格是否被选中
       QTableWidget *tableWidget() 	//返回项所在的QTableWidget 对象指针
       ```

4. 自动调整行高和列宽

   - ```c++
     //这几个函数是 QTableWidget 的父类QTableView 中定义的函数，
     void resizeColumnToContents(int column) //自动调整列号为column 的列的宽度
     void resizeColumnsToContents() //自动调整所有列的宽度，以适应其内容
     void resizeRowToContents(int row) //自动调整行号为row 的行的高度
     void resizeRowsToContents() //自动调整所有行的高度，以适应其内容
     ```

5. 其他属性控制

   - **是否显示水平表头和垂直表头**函数`horizontalHeader()`返回水平表头对象，`verticalHeader()`返回垂直表头对象。表头对象是`QHeaderView` 类，通过`QHeaderView` 类的接口函数可以设置表头的各种属性。
   - **间隔行底色**。函数`setAlternatingRowColors()`用于设置表格的行是否用交替底色显示，若设置为true，则会使用一种默认颜色错行设置为行的底色。
   - **选择方式**。函数`setSelectionBehavior()`用于设置选择方式，有单元格选择、行选择等方式。
     - `QAbstractItemView::SelectItems`单元格选择

### 模型/视图结构

1. 模型/视图结构概述

   - 模型/视图结构是一种将**数据存储**和**界面展示分离**的编程方法。**模型存储数据**，**视图组件显示模型中的数据**，在视图组件里修改的数据会被自动保存到模型里。
   - 模型的数据来源可以是内存中的字符串列表或二维表格型数据，也可以是数据库中的数据表，一种模型可以用不同的视图组件来显示数据。
     - <img style="width: 600px;height:200px" src="image\模型视图.png">
     - 源数据（data）
       - 是原始数据如数据库的一个数据表或SQL查询结果、内存中的一个字符串列表或磁盘文件系统结构等
     - 视图（view）也称为视图组件
       - 是界面组件，视图从模型获得数据然后将其显示在界面上
       - `Qt` 提供一些常用的视图组件，如`QListView`、`QTreeView` 和`QTableView`
     - 模型（model）也称为数据模型
       - 与源数据通信，并为视图组件提供数据接口。它从源数据提取需要的数据，用于视图组件进行显示和编辑。
       - `QStringListModel` 是字符串列表的模型类，`QSqlTableModel` 是数据库中数据表的模型类。
     - 代理（delegate）
       - 在视图与模型之间交互操作时提供的临时编辑器。模型向视图提供数据是单向的，一般仅用于显示。当需要在视图上编辑数据时，代理会为编辑数据提供一个编辑器，这个编辑器获取模型的数据、接受用户编辑的数据后又将其提交给模型。
       - 例如在`QTableView` 组件上双击一个单元格来编辑数据时，在单元格里就会出现一个`QLineEdit` 组件，这个编辑框就是代理提供的临时编辑器。

2. 模型

   - 所有**基于项**（item）的**模型类**都是基于`QAbstractItemModel` 类的，这个类定义了视图组件和代理存取数据的接口。
     - 模型只是在内存中临时存储数据，模型的数据来源可以是其他类、文件、数据库或任何数据源
   - `Qt` 中几个主要的模型类的继承关系如图5-2 所示。`QAbstractItemModel` 的父类是`QObject`，所以模型类支持`Qt` 的元对象系统。
     - <img style="width: 1100px;height:400px" src="image\模型类的继承关系.png">
     - 抽象模型类 `QAbstractItemModel` 不能直接用于创建实例对象
   - 常用的模型类
     - `QFileSystemModel` 	用于表示计算机上文件系统的模型类
     - `QStringListModel`         用于表示字符串列表数据的模型类
     - `QStandardItemModel`     标准的基于项的模型类，每个项是一个`QStandardItem` 对象
     - `QSqlQueryModel`             用于表示数据库`SQL` 查询结果的模型类
     - `QSqlTableModel`             用于表示数据库的一个数据表的模型类

3. 视图

   - 

   

   

   

   





