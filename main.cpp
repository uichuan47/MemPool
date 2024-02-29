/***********************************
 * @author uichuan
 * @since  2023.9.24
 * @brief  本文件对实现的内存分配器进行性能测试
 * @date   2023.10.2
 ***********************************/

#include <iostream> // std::cout, std::endl
#include <cassert>  // assert()
#include <ctime>    // clock()
#include <vector>   // std::vector

#include "MemoryPool.hpp" // MemoryPool<T>
#include "StackAlloc.hpp" // StackAlloc<T, Alloc>

// 待插入元素个数
#define ELEMS 10000
// 重复插入次数
#define REPS 100

int main()
{
    // 计时变量
    clock_t start;

    // 在 STL 默认分配器下进行内存分配操作
    StackAlloc<int, std::allocator<int>> stackDefault;

    // allocator 提供分配 原始的、未构造 的内存，(new 直接对内存调用构造函数)

    // 开始计时
    start = clock();

    // 重复 REPS 次
    for (int j = 0; j < REPS; j++)
    {
        // 检查容器是否为空
        assert(stackDefault.empty());

        // 插入指定元素个数
        for (int i = 0; i < ELEMS; i++)
        {
            stackDefault.push(i);
        }

        // 将元素全部弹出
        for (int i = 0; i < ELEMS; i++)
        {
            stackDefault.pop();
        }
    }

    // 输出内存分配的时间
    std::cout << "Default Allocator Time: ";
    std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";

    // 在 内存池 下进行内存分配操作
    StackAlloc<int, MemoryPool<int>> stackPool;

    // 开始计时
    start = clock();

    // 重复 REPS 次
    for (int j = 0; j < REPS; j++)
    {
        assert(stackPool.empty());

        // 插入指定元素个数
        for (int i = 0; i < ELEMS; i++)
        {
            stackPool.push(i);
        }

        // 将元素全部弹出
        for (int i = 0; i < ELEMS; i++)
        {
            stackPool.pop();
        }
    }

    // 输出内存分配时间
    std::cout << "MemoryPool Allocator Time: ";
    std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";

    return 0;
}