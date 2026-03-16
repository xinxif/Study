### Boost库

#### Asio网络库

1. `boost::asio::io_context`

   - 用于对I/O对象（如套接字）执行**同步**和**异步**操作，程序至少需要包含**一个输入/输出执行上下文**。

     - 如：`boost::asio::io_context io_context`

   - 要执行输入/输出操作，程序需要需要**一个输入/输出对象**，例如一个TCP套接字

     - 同步操作

       <img style="width: 1000px;height:700px" src="others_img\asio同步.png">

       - 程序通过调用I/O对象==**`socket.connect(server_endpoint)`**==来启动连接操作

       - I/O 对象将请求转发给I/O执行上下文

       - I/O 执行上下文调用操作系统执行连接操作

       - 操作系统将操作的结果返回给I/O执行上下文

       - I/O 执行上下文将操作过程中产生的**任何错误**转换为类型为 `boost::system::error_code` 的对象。

         - `error_code` 可与特定值进行比较，或作为布尔值进行测试（==**其中 `false` 结果表示未发生错误**==）。随后，结果被传递回I/O对象。

       - 输入/输出对象在**操作失败**时抛出类型为 `boost::system::system_error` 的**异常**。

         - ```c++
           //如果初始化操作的代码改写为如下，error_code 变量 ec 将被设置为该运算的结果，且不会抛出异常。
            boost::system::error_code ec;    
           socket.connect(server_endpoint, ec);
           ```

     - 异步操作

       - <img style="width: 1000px;height:700px" src="others_img\asio异步.png">

       - 程序通过调用I/O对象：==**`socket.async_connect(server_endpoint, your_completion_handler)`**==来启动连接操作。

         - 其中 `your_completion_handler` 是一个函数或函数对象

         - ```c++
           void your_completion_handler(const boost::system::error_code& ec);
           ```

       - I/O对象将请求转发给I/O执行上下文

       - I/O 执行上下文向操作系统发出信号，指示其启动异步连接。

       - 操作系统通过将连接操作的结果放入队列中，表示连接操作已完成，并准备由 I/O 执行上下文进行处理。

       - 当使用 `io_context` 作为 I/O 执行上下文时，程序必须调用 `io_context::run()` （或类似的 `io_context` 成员函数）才能获取结果。调用 `io_context::run()` 会在存在未完成的异步操作时阻塞，因此通常应在启动第一个异步操作后立即调用它。

       - 在调用 `io_context::run()` 时，I/O 执行上下文会从队列中取出操作的结果，将其转换为 `error_code` ，然后传递给你的完成处理程序

   - ```c++
     #include <iostream>
     #include <boost/asio.hpp>
     
     void print(const boost::system::error_code& /*e*/)
     {
       std::cout << "Hello, world!" << std::endl;
     }
     
     int main()
     {
       boost::asio::io_context io;
     
       boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));
       t.async_wait(&print);
     
       io.run();
     
       return 0;
     }
     /*
     程序启动
        ↓
     创建 io_context （无事件）
        ↓
     构造 steady_timer，设置 5 秒后到期 （状态：等待中）
        ↓
     t.async_wait(&print) 注册回调 （状态：等待中）
        ↓
     io.run() 阻塞并进入事件循环
        ↓
     （0 ~ 5 秒内，io.run() 阻塞在底层 epoll_wait，定时器等待到期）
        ↓
     约 5 秒后，底层定时器到期 → epoll 通知 → Asio 完成队列插入 “定时器就绪” 事件
        ↓
     io.run() 从队列取出事件，调用 print 回调
        ↓
     print 打印 “Hello, world!”
        ↓
     回调结束，io.run() 检查没有剩余异步操作，返回
        ↓
     main 返回，进程退出
     */
     ```

   - **让线程池**调用 `boost::asio::io_context::run()` 。不过，由于这种方法允许处理程序并发执行，当处理程序**访问共享的、线程不安全**的资源时，**需要一种同步方法**。需要用到`boost::asio::strand` 类型的对象

     > strand **类模板**是一个执行器适配器，可以保证==**通过它分派的处理程序**==在==**下一个处理程序启动之前**==，**允许一个正在执行的处理程序完成**。无论调用 `boost::asio::io_context::run()` 的线程数量有多少，都能保证这一点。
     >
     > 当然，处理程序仍可能与其他处理程序同时执行，这些处理程序不是通过 strand 调度的，就是通过不同的 strand 对象调度的。strand 类模板是一个执行器适配器，可以保证通过它分派的处理程序在下一个处理程序启动之前，允许一个正在执行的处理程序完成。
     >
     > 无论调用 `boost::asio::io_context::run()` 的线程数量有多少，都能保证这一点。当然，处理程序仍可能与其他处理程序同时执行，这些处理程序不是通过 strand 调度的，就是通过不同的 strand 对象调度的。

   - ```c++
     #include <functional>
     #include <iostream>
     #include <thread>
     #include <boost/asio.hpp>
     class printer
     {
     public:
         printer(boost::asio::io_context& io)
             : strand_(boost::asio::make_strand(io)),
             timer1_(io, boost::asio::chrono::seconds(1)),
             timer2_(io, boost::asio::chrono::seconds(1)),
             count_(0)
         {
             timer1_.async_wait(boost::asio::bind_executor(strand_,
                 std::bind(&printer::print1, this)));
     
             timer2_.async_wait(boost::asio::bind_executor(strand_,
                 std::bind(&printer::print2, this)));
         }
         ~printer()
         {
             std::cout << "Final count is " << count_ << std::endl;
         }
     
         void print1()
         {
             if (count_ < 10)
             {
                 std::cout << "Timer 1: " << count_ << std::endl;
                 ++count_;
     
                 timer1_.expires_at(timer1_.expiry() + boost::asio::chrono::seconds(1));
     
                 timer1_.async_wait(boost::asio::bind_executor(strand_,
                     std::bind(&printer::print1, this)));
             }
         }
     	//std::bind 会自动忽略多余参数。所以const boost::system::error_code& ec可以没有
         void print2()
         {
             if (count_ < 10)
             {
                 std::cout << "Timer 2: " << count_ << std::endl;
                 ++count_;
     
                 timer2_.expires_at(timer2_.expiry() + boost::asio::chrono::seconds(1));
     
                 timer2_.async_wait(boost::asio::bind_executor(strand_,
                     std::bind(&printer::print2, this)));
             }
         }
     
     private:
         boost::asio::strand<boost::asio::io_context::executor_type> strand_;
         boost::asio::steady_timer timer1_;
         boost::asio::steady_timer timer2_;
         int count_;
     };
     
     int main()
     {
         boost::asio::io_context io;
         printer p(io);
         std::thread t([&] { io.run(); });//因为 Lambda 捕获了 io 的引用，io.run() 真正调用的是主线程中那一份 io_context 对象。
         io.run();
         t.join();
     
         return 0;
     }
     ```

2. `boost::asio::ip::tcp::acceptor`

   - 绑定端口（bind），开始监听（listen），接收连接（accept）

3. `boost::asio::ip::tcp::socket`

   - ```c++
     #include <boost/asio.hpp>
     #include <iostream>
     
     int main()
     {
         boost::asio::io_context io;
     
         boost::asio::ip::tcp::acceptor acceptor(
             io,
             boost::asio::ip::tcp::endpoint(
                 boost::asio::ip::tcp::v4(), 8888));
     
         boost::asio::ip::tcp::socket socket(io);
     
         acceptor.accept(socket);
     
         auto remote = socket.remote_endpoint();
     
         std::cout << "Client connected\n";
         std::cout << "IP: " << remote.address().to_string() << "\n";
         std::cout << "Port: " << remote.port() << "\n";
     }
     ```
     
   - `socket.get_executor()` 的作用是 **获取这个 socket 所使用的执行器（executor）**。在 **Boost.Asio** 中，每一个 I/O 对象（例如 `tcp::socket`、`steady_timer` 等）都必须运行在某个执行环境里，而这个执行环境就是通过 **executor** 表示的。此时 `socket` 内部就知道自己属于哪个 `io_context`。`get_executor()` 的作用就是把这个“执行环境”取出来。这个执行环境并不直接返回 `io_context`，而是返回一个更通用的抽象类型（通常是 `any_io_executor`），它表示“在哪个事件循环里执行任务”。
   
     - 保证 **同一个事件循环** **同一个线程模型**
   

##### HTTP

1. `beast::http::async_read`

   - 第一个参数 `AsyncReadStream& stream` 表示**数据来源的流对象**。这个对象必须支持异步读取操作，例如 `async_read_some`。在实际代码中，这个参数**通常就是 TCP 连接**对象。

     - ```c++
       tcp::socket socket_;
       http::async_read(socket_, ...);
       ```

   - 第二个参数 `DynamicBuffer& buffer` 是**接收原始字节数据的缓冲区**。网络读取到的数据首先进入这个 buffer，然后 Beast 的 HTTP 解析器再从 buffer 中解析 HTTP 协议内容。

   - 第三个参数 `message<...>& msg` 是**解析后的 HTTP 消息对象**。当 `async_read` 完成时，HTTP 请求或响应就会被解析并填充到这个对象中。

   - 第四个参数 `ReadHandler&& handler` 是**异步操作完成后的回调函数**。当 HTTP 消息读取并解析完成后，Asio 会调用这个函数。回调函数通常接收两个参数：一个 `error_code` 表示是否发生错误，一个 `size_t` 表示读取的字节数。

2. 格式

   - 

