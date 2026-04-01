#include <bits/stdc++.h>
#define FAST_IO                  \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
using namespace std;

/*
题目：打印机队列 (oda0004)
考点：优先队列
分值：100分
在线OJ链接：https://hydro.ac/d/coder_gather/p/oda0004

题目描述：
有5台打印机，每台打印机有一个任务队列。
支持两种操作：
1. IN P N：将编号为N的任务加入到第P台打印机的队列中，任务优先级为N
   （数字越大优先级越高，优先级相同则按任务编号小的先执行）
2. OUT P：从第P台打印机取出一个任务执行并输出任务编号
   如果队列为空，输出"NULL"

打印机编号P为1~5。

输入格式：
第一行一个整数N，表示操作数量
接下来N行，每行一个操作：
IN P N 或 OUT P

输出格式：
对于每个OUT操作，输出执行的任务编号或"NULL"

示例输入：
7
IN 1 1
IN 1 2
IN 1 3
OUT 1
OUT 1
OUT 1
OUT 1

示例输出：
3
2
1
NULL

解题思路：
1. 为每台打印机维护一个优先队列（大顶堆）
2. 自定义比较器：先按优先级降序，优先级相同按任务编号升序
3. 注意：优先队列默认是大顶堆，但我们需要自定义比较逻辑
*/

struct Task
{
    int id;
    int priority;
};

// 自定义比较器：用于优先队列
// 注意：priority_queue默认使用less<T>，即大顶堆
// 我们的比较器需要定义"小于"关系，但实际用于构建大顶堆
struct CompareTask
{
    bool operator()(const Task &a, const Task &b)
    {
        // 优先级高的先执行（大顶堆）
        if (a.priority != b.priority)
            return a.priority < b.priority; // 注意：对于大顶堆，需要反向比较
        // 优先级相同，任务编号小的先执行
        return a.id > b.id; // 注意：对于大顶堆，需要反向比较
    }
};

class Printer
{
private:
    priority_queue<Task, vector<Task>, CompareTask> pq;

public:
    Printer()
    {
    }

    void insert_STL(int id, int priority)
    {
        pq.push({id, priority});
    }

    int pop_STL()
    {
        if (pq.empty())
            return -1;
        int top = pq.top().id;
        pq.pop();
        return top;
    }
};

int main()
{
    FAST_IO;
    int N;
    cin >> N;

    // 5台打印机，编号1~5，对应数组索引0~4
    vector<Printer> printers(5);
    int taskId = 1; // 任务编号从1开始
    
    while (N--)
    {
        string operation, printerIndexStr, priorityStr;
        cin >> operation;

        if (operation == "IN")
        {
            // IN P N 操作
            cin >> printerIndexStr >> priorityStr;
            int printerIndex = stoi(printerIndexStr) - 1; // 转换为0-based索引
            int priority = stoi(priorityStr);
            
            printers[printerIndex].insert_STL(taskId++, priority);
        }
        else if (operation == "OUT")
        {
            // OUT P 操作
            cin >> printerIndexStr;
            int printerIndex = stoi(printerIndexStr) - 1; // 转换为0-based索引
            
            int taskId = printers[printerIndex].pop_STL();
            if (taskId == -1)
            {
                cout << "NULL" << "\n";
            }
            else
            {
                cout << taskId << "\n";
            }
        }
    }
    return 0;
}

/*
测试用例1：
输入：
7
IN 1 1
IN 1 2
IN 1 3
OUT 1
OUT 1
OUT 1
OUT 1

输出：
3
2
1
NULL

测试用例2：
输入：
10
IN 1 5
IN 2 3
IN 1 4
OUT 1
OUT 2
IN 2 6
OUT 2
OUT 2
OUT 1
OUT 1

输出：
5
3
6
NULL
4
NULL

解释：
时间线：
1. IN 1 5: 打印机1加入任务1(优先级5)
2. IN 2 3: 打印机2加入任务2(优先级3)
3. IN 1 4: 打印机1加入任务3(优先级4)
4. OUT 1: 打印机1执行任务1(优先级5最高)
5. OUT 2: 打印机2执行任务2(优先级3)
6. IN 2 6: 打印机2加入任务4(优先级6)
7. OUT 2: 打印机2执行任务4(优先级6)
8. OUT 2: 打印机2队列空，输出NULL
9. OUT 1: 打印机1执行任务3(优先级4)
10. OUT 1: 打印机1队列空，输出NULL

测试用例3：优先级相同的情况
输入：
6
IN 1 5
IN 1 5
IN 1 5
OUT 1
OUT 1
OUT 1

输出：
1
2
3

解释：优先级相同，按任务编号小的先执行

测试用例4：多台打印机
输入：
8
IN 1 10
IN 2 20
IN 3 30
OUT 1
OUT 2
OUT 3
IN 1 5
OUT 1

输出：
1
2
3
4

测试用例5：空队列测试
输入：
3
OUT 1
OUT 2
OUT 3

输出：
NULL
NULL
NULL

测试用例6：混合操作
输入：
12
IN 1 3
IN 1 1
IN 1 2
OUT 1
IN 2 5
OUT 1
OUT 1
OUT 2
IN 3 4
OUT 3
OUT 3
OUT 1

输出：
3
2
1
5
4
NULL
NULL
*/