# Memory Pool A
本项目实现了一个基于 C++ 11 `高性能内存池`的可`动态内存分配`的链表队列，队列支持`多线程`下 30 Hz 到 50 Hz 的数据输入和 10 Hz 的数据输出，项目内含自实现的 内存池 分配器，可以在一定程度上`提升内存分配性能`，减少内存碎片的产生和内存分配失败引起的程序崩溃。

# 项目背景
项目最初，要求是设计一个可以`同时缓存多种数据类型的容器`，容器需要保证`先入先出`的存取规则，因此笔者理所当然的选择了对 STL 中的 deque 队列进行封装，并自行设计了数据结构满足多种数据的存取，插入数据可以通过重载实现，这也是第一版。

但是在测试过程中，由于`数据输入频率很高`，但是`取出速率较慢`，因此`数据很容易在队列中积压`，栈区`内存开销`会很大，而栈区内存只有在进程结束后才被回收，因此会导致整个`进程内存占用较大`，为了解决这个问题，笔者选择将类中成员类型修改为`指针`类型，这也就是第二版。

修改为指针后，当数据进入队列时分配堆区内存，当数据被取走后便可以即刻释放内存，从而一定程度上减少内存开销。虽然解决了内存开销问题，但是随着数据输入频率越来越高，渐渐产生了新的问题，即每次存入数据都需要在堆区申请内存，取出数据需要释放内存，`频繁的内存申请与释放存在一定的安全隐患`，而且最关键的是，程序效率也会有所下降，笔者查阅后发现，是因为每次 new delete 都需要和操作系统进行对接，这里存在一定的开销，会影响程序效率，而且可能会出现内存不足的情况，为了解决这个问题，笔者查阅一些资料后决定选择`内存池化技术`进行解决。


# 项目架构

## 内存池设计
指针，是 C/C++ 独特的一点，在程序设计中，不可避免的需要操作内存，但是直接操作内存的便捷性也会给程序设计带来许多隐患，可能会遇到内存不足、分配失败等特殊情况，而且每次内存分配都需要向操作系统申请，都存在时空开销，效率并不高。
为了更好地管理和优化程序内存，可以通过内存池化技术，在一定程度上降低操作内存的成本，提升程序效率，因此，在本项目中将实现一个性能不错的内存池用于解决笔者在工作过程中遇到的一些项目需求。

## 链表栈
为了验证内存池设计的性能，还需要设计一个可以进行动态内存分配的数据结构作为载体，分别使用默认分配器和内存池作为内存分配工具，进行相同的数据输入输出，观察两者的分配效率。常用的测试工具为链表栈结构，因此，笔者将首先实现一个链表栈，作为测试分配其性能的工具。

## 数据缓存池
数据池可以`存储多种格式数据`，并保证数据的`先入先出`存取，通过内存池提升数据存取效率。
出于一些原因，在这里笔者并未给出通过内存池实现的数据缓存队列，相信感兴趣的读者可以通过给出的内存池实现和队列设计可以自行实现。

# Memory Pool A
This project has realized a dynamic memory allocation list queue based on C++ 11 'high performance memory pool'. The queue supports 30 Hz to 50 Hz data input and 10 Hz data output under 'multithreading'. The project includes a self-implemented memory pool allocator. Can 'improve memory allocation performance' to some extent, reduce the generation of memory fragmentation and memory allocation failure caused by the program crash.

# Project background
At the beginning of the project, the Leader's requirement is to design a container that can simultaneously cache multiple data types. The container needs to ensure the first-in, first-out access rule. Therefore, the author chose to encapsulate the deque queue in STL and designed the data structure to meet the requirements of multiple data access. Inserting data can be done by overloading, which is also the first version.

However, in the test process, because the data input frequency is very high, but the fetch rate is slow, so the data is easy to backlog in the queue, the stack area memory overhead will be very large, and the stack area memory is only reclaimed after the process ends, so it will lead to the whole process memory consumption is large, in order to solve this problem, I chose to change the class member type to 'pointer' type, which is the second version.

After changing to a pointer, the heap area memory can be allocated when the data enters the queue, and the memory can be released immediately after the data is removed, thus reducing the memory overhead to some extent. Although solved the memory cost problem, but with the data input frequency is higher and higher, gradually produced a new problem, that is, every time the data stored in the heap area to apply for memory, take out the data need to release memory, 'frequent memory application and release there are certain security risks', and the most critical is that the efficiency of the program will be reduced, the author found that, Because each new delete needs to be connected with the operating system, there is a certain amount of overhead, will affect the efficiency of the program, and there may be insufficient memory, in order to solve this problem, the author looked up some information after deciding to choose the 'memory pooling technology' to solve.

# Project architecture

## Memory pool design
Pointer, is a unique point of C/C++, in the program design, it is inevitable to operate the memory, but the convenience of direct operation of memory will also bring many hidden dangers to the program design, may encounter insufficient memory, allocation failure and other special cases, and each memory allocation needs to apply to the operating system, there is time and space overhead, efficiency is not high.
In order to better manage and optimize program memory, memory pooling technology can be used to reduce the cost of operating memory to a certain extent and improve program efficiency. Therefore, in this project, a memory pool with good performance will be realized to solve some project requirements encountered in the process of work.

## Linked list stack
In order to verify the performance of the memory pool design, it is also necessary to design a data structure that can be used for dynamic memory allocation as the carrier. The default allocator and memory pool are used as memory allocation tools respectively to carry out the same data input and output, and observe the allocation efficiency of both. The common test tool is the linked list stack structure, so the author will first implement a linked list stack, as a test to assign its performance tool.

## Data cache pool
Data pool can 'store multiple formats of data', and ensure data 'first-in, first-out' access, through the memory pool to improve the efficiency of data access.
For some reason, the data cache queue implemented by the memory pool is not presented here. I believe that interested readers can implement the memory pool implementation and queue design by themselves.

