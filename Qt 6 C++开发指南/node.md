### 第一章

1. `Profile` 是介于`Debug` 和`Release` 之间的性能平衡版本，可用于调试。
2. `Shadow Build` 是 `Qt Creator` 提供的一种构建方式，它将编译过程中生成的中间文件和可执行文件输出到独立于源码目录的构建目录中，从而保持源码目录的整洁，便于同时管理多种构建配置和开发环境。

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

   - `*.ui`文件经过*UIC* 编译后生成`*.h`这个文件里定义了一个类，类的名称是`Ui_*`，用`C++`语言描述`UI` 文件中界面组件的属性设置、布局以及信号与槽的关联等内容

     - 窗口界面定义文件，是一个XML 文件。用`Qt Designer` 打开`UI` 文件进行窗口界面可视化设计，保存修改后会重新生成`UI` 文件。
     - `retranslateUi()`，其功能是设置界面上各组件的文字属性，如标签的文字、按钮的文字、窗口的标题等。界面上所有与文字设置相关的功能都集中在函数`retranslateUi()`里，在设计多语言界面时会用到这个函数。

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

     - `connect()`是`QObject` 类的一个静态函数，而`QObject` 是大部分`Qt` 类的基类，在实际调用时可以忽略前面的限定符部分。

     - `sender` 是发射信号的对象的名称

     - `signal()`是信号，信号可以看作特殊的函数，需要带有括号，有参数时还需要指明各参数类型；

     - `receiver` 是接收信号的对象的名称

     - `slot()`是槽函数，需要带有括号，有参数时还需要指明各**参数类型**。

     - 当一个信号与多个槽函数关联时，槽函数按照建立连接时的顺序依次运行。

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
       - `QSizePolicy::Preferred`：首选尺寸，使用`sizeHint()`函数的返回值作为最优尺寸，组件仍然可以缩放，但是放大时不会超过`sizeHint()`函数返回的尺寸。
       - `QSizePolicy::Expanding`：可扩展尺寸，`sizeHint()`函数的返回值是可变大小的尺寸，组件可扩展。
       - `QSizePolicy::MinimumExpanding`：最小可扩展尺寸，`sizeHint()`函数的返回值是最小尺寸，组件可扩展。
       - `QSizePolicy::Ignored`：忽略尺寸，`sizeHint()`函数的返回值被忽略，组件占据尽可能大的空间。
       - 在使用尺寸策略时，`QWidget` 的`sizeHint()`函数会起到很大作用，在组件的父组件尺寸变化时，`sizeHint()`返回组件的建议尺寸。
       - `QSizePolicy` 还有`Horizontal Stretch`（水平延展）属性和`Vertical Stretch`（垂直延
         展）属性，分别表示水平延展因子和垂直延展因子，它们都是整数值，取值范围是0～255。默认
         值是0，表示组件保持默认的宽度或高度。
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
