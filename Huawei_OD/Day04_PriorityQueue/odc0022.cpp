#include <bits/stdc++.h>
#define FAST_IO                  \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
using namespace std;

/*
题目：单核CPU任务调度 (odc0022)
考点：模拟、优先队列
分值：200分
在线OJ链接：https://hydro.ac/d/coder_gather/p/odc0022

题目描述：
有一个单核CPU需要处理一系列任务。每个任务有到达时间、执行时间和优先级。
CPU调度规则：
1. 当CPU空闲时，选择当前已到达的任务中优先级最高的执行
2. 如果优先级相同，选择到达时间最早的任务
3. 如果到达时间也相同，选择任务ID最小的任务
4. 任务执行不可抢占（一旦开始执行，必须完成才能执行下一个任务）
5. 如果有新任务在某个任务执行期间到达，需要等当前任务执行完后重新调度

需要计算每个任务的完成时间。

输入格式：
第一行一个整数N，表示任务数量
接下来N行，每行4个整数：任务ID、到达时间、执行时间、优先级
任务ID唯一，按输入顺序从1开始编号

输出格式：
输出N行，每行一个整数，表示对应任务的完成时间（按任务ID顺序输出）

示例输入：
4
1 0 5 3
2 1 3 2
3 2 4 1
4 3 2 4

示例输出：
5
8
12
14

解释：
时间0：任务1到达，开始执行（优先级3）
时间5：任务1完成，此时已到达任务：任务2(优先级2)、任务3(优先级1)、任务4(优先级4)
       选择优先级最高的任务4执行
时间7：任务4完成，此时已到达任务：任务2(优先级2)、任务3(优先级1)
       选择优先级较高的任务2执行
时间10：任务2完成，执行任务3
时间14：任务3完成

解题思路：
1. 按到达时间排序所有任务
2. 使用优先队列维护当前可执行的任务
3. 模拟时间推进，处理任务执行和调度
4. 自定义比较器：优先级高的先执行，优先级相同则到达时间早的先执行，都相同则ID小的先执行
*/

struct Task {
    int id;
    int arrivalTime;
    int executeTime;
    int priority;
    int finishTime;
    
    // 用于按到达时间排序
    bool operator<(const Task& other) const {
        return arrivalTime < other.arrivalTime;
    }
};

// 优先队列比较器：用于选择要执行的任务
struct CompareTaskForExecution {
    bool operator()(const Task& a, const Task& b) const {
        // 优先级高的先执行（数字越大优先级越高）
        if (a.priority != b.priority) {
            return a.priority < b.priority; // 大顶堆需要反向比较
        }
        // 优先级相同，到达时间早的先执行
        if (a.arrivalTime != b.arrivalTime) {
            return a.arrivalTime > b.arrivalTime; // 大顶堆需要反向比较
        }
        // 都相同，ID小的先执行
        return a.id > b.id; // 大顶堆需要反向比较
    }
};

class CPUScheduler {
private:
    vector<Task> tasks;
    int n;
    
public:
    CPUScheduler(int num) : n(num) {
        tasks.resize(n);
    }
    
    void addTask(int index, int id, int arrival, int execute, int priority) {
        tasks[index] = {id, arrival, execute, priority, 0};
    }
    
    vector<int> schedule() {
        // 按到达时间排序
        vector<Task> sortedTasks = tasks;
        sort(sortedTasks.begin(), sortedTasks.end());
        
        // 优先队列：维护当前可执行的任务
        priority_queue<Task, vector<Task>, CompareTaskForExecution> readyQueue;
        
        // 结果数组：按任务ID顺序存储完成时间
        vector<int> result(n + 1, 0); // 索引从1开始
        
        int currentTime = 0;
        int taskIndex = 0;
        
        while (taskIndex < n || !readyQueue.empty()) {
            // 将当前时间及之前到达的任务加入就绪队列
            while (taskIndex < n && sortedTasks[taskIndex].arrivalTime <= currentTime) {
                readyQueue.push(sortedTasks[taskIndex]);
                taskIndex++;
            }
            
            if (readyQueue.empty()) {
                // 如果没有就绪任务，时间跳到下一个任务的到达时间
                if (taskIndex < n) {
                    currentTime = sortedTasks[taskIndex].arrivalTime;
                    continue;
                } else {
                    break;
                }
            }
            
            // 执行优先级最高的任务
            Task currentTask = readyQueue.top();
            readyQueue.pop();
            
            // 如果CPU空闲时间早于任务到达时间，等待到到达时间
            if (currentTime < currentTask.arrivalTime) {
                currentTime = currentTask.arrivalTime;
            }
            
            // 执行任务
            int startTime = currentTime;
            int endTime = startTime + currentTask.executeTime;
            
            // 记录完成时间
            result[currentTask.id] = endTime;
            
            // 更新时间
            currentTime = endTime;
            
            // 在执行期间可能有新任务到达，需要加入就绪队列
            while (taskIndex < n && sortedTasks[taskIndex].arrivalTime <= currentTime) {
                readyQueue.push(sortedTasks[taskIndex]);
                taskIndex++;
            }
        }
        
        return result;
    }
};

int main() {
    FAST_IO;
    
    int N;
    cin >> N;
    
    CPUScheduler scheduler(N);
    
    for (int i = 0; i < N; i++) {
        int id, arrival, execute, priority;
        cin >> id >> arrival >> execute >> priority;
        scheduler.addTask(i, id, arrival, execute, priority);
    }
    
    vector<int> finishTimes = scheduler.schedule();
    
    // 按任务ID顺序输出完成时间
    for (int i = 1; i <= N; i++) {
        cout << finishTimes[i] << "\n";
    }
    
    return 0;
}

/*
测试用例1：
输入：
4
1 0 5 3
2 1 3 2
3 2 4 1
4 3 2 4

输出：
5
8
12
14

测试用例2：
输入：
3
1 0 3 1
2 1 2 2
3 2 1 3

输出：
3
5
6

解释：
时间0：执行任务1（优先级1）
时间3：任务1完成，执行任务3（优先级3，最高）
时间4：任务3完成，执行任务2（优先级2）
时间6：任务2完成

测试用例3：
输入：
3
1 0 2 2
2 0 3 2
3 0 1 2

输出：
2
5
6

解释：
优先级相同，按到达时间（都相同），按ID顺序执行

测试用例4：
输入：
5
1 0 2 1
2 1 3 3
3 2 1 2
4 3 2 3
5 4 1 1

输出：
2
5
8
10
11

测试用例5：
输入：
1
1 10 5 1

输出：
15

测试用例6：复杂情况
输入：
6
1 0 3 2
2 1 2 3
3 2 4 1
4 3 1 4
5 4 2 2
6 5 3 3

输出：
3
5
15
6
13
10
*/