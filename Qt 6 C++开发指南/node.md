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

   - `*.ui`文件经过UIC 编译后生成`*.h`这个文件里定义了一个类，类的名称是`Ui_*`，用`C++`语言描述`UI` 文件中界面组件的属性设置、布局以及信号与槽的关联等内容

     - 窗口界面定义文件，是一个XML 文件。用`Qt Designer` 打开`UI` 文件进行窗口界面可视化设计，保存修改后会重新生成`UI` 文件。
     - `retranslateUi()`，其功能是设置界面上各组件的文字属性，如标签的文字、按钮的文字、窗口的标题等。界面上所有与文字设置相关的功能都集中在函数`retranslateUi()`里，在设计多语言界面时会用到这个函数。

3. 窗口界面可视化设计

   - 界面组件的属性设置，需要注意以下几点

     - 界面上的每个组件需要有一个唯一的对象名称，程序里访问界面组件时都是通过其对象名称进行的，自动生成的槽函数名称里也有对象名称。所以，组件的对象名称设置好之后一般不要改动。若需要修改对象名称，涉及的代码需要相应改动。
     - 窗体的对象名称会影响窗口`UI` 类的名称。`dialog.ui` 被`UIC` 编译后生成文件`ui_dialog.h`，窗体的对象名称与文件`ui_dialog.h`中定义的窗口`UI` 类有关。一般不在`Qt Designer` 里修改窗体的对象名称，除非是要重命名一个窗口，那么需要对窗口相关的`4` 个文件都重命名。
     - 设置**窗体**的`font `属性后，**界面上其他组件**的默认字体就是窗体的字体，无须再单独设置，除非要为某个组件设置单独的字体，例如组件`plainTextEdit` 的字体大小被单独设置为`20`。
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
       - `Qt` 提供了元对象编译器（MOC）。在构建项目时，项目中的头文件会先被`MOC` 预编译。例如，以`Release` 模式构建项目`samp2_2` 后，文件夹`release` 里的文件。其中，`moc_dialog.cpp`是`MOC` 读取文件`dialog.h` 的内容后生成的一个元对象代码文件，文件`moc_predefs.h` 里是一些宏定义。结合`moc_dialog.cpp` 和`moc_predefs.h`，`dialog.cpp` 和`ui_dialog.h` 就可以被标准`C++`编译器编译。
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

     - 可以生成VS项目解决方案，需要使用MSVC编译套件，系统环境变量也存在Qt的MSVC编译套件，要在MinGw之前。

5. `Qt Creator`使用技巧

   - <img style="width: 1100px;height:400px" src="image\Qt快捷键.png">

