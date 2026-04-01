#include <bits/stdc++.h>
#define FAST_IO                  \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
using namespace std;

/*
题目：热点网站统计 (ode0034)
考点：优先队列
分值：100分
在线OJ链接：https://hydro.ac/d/coder_gather/p/ode0034

题目描述：
统计一段时间内访问次数最多的网站（热点网站）。
输入包含多行，每行是一个网站的URL。
输出访问次数最多的前K个网站，按访问次数降序排列，如果访问次数相同，按字典序升序排列。

输入格式：
第一行包含一个整数K，表示需要输出的热点网站数量。
接下来多行，每行一个URL字符串，表示一次网站访问记录。
输入以EOF结束。

输出格式：
输出K行，每行格式：URL 访问次数
按访问次数降序排列，如果访问次数相同，按URL字典序升序排列。

示例输入：
3
www.example.com
www.test.com
www.example.com
www.demo.com
www.test.com
www.example.com
www.demo.com

示例输出：
www.example.com 3
www.demo.com 2
www.test.com 2

解题思路：
1. 使用哈希表统计每个URL的访问次数
2. 使用优先队列（小顶堆）维护前K个热点网站
3. 自定义比较器：先按访问次数降序，次数相同按URL字典序升序
4. 遍历哈希表，维护大小为K的优先队列
*/

struct Website {
    string url;
    int count;
    
    // 自定义比较器：用于优先队列（小顶堆）
    // 注意：优先队列默认是大顶堆，我们需要小顶堆来维护前K个最大元素
    bool operator<(const Website& other) const {
        // 如果访问次数不同，按次数升序（小顶堆）
        if (count != other.count) {
            return count > other.count; // 注意：小顶堆需要反向比较
        }
        // 访问次数相同，按URL字典序降序（小顶堆）
        return url < other.url; // 注意：小顶堆需要反向比较
    }
};

class HotWebsiteStats {
private:
    unordered_map<string, int> urlCount;
    int K;
    
public:
    HotWebsiteStats(int k) : K(k) {}
    
    void addVisit(const string& url) {
        urlCount[url]++;
    }
    
    vector<Website> getTopK() {
        // 使用小顶堆维护前K个最大元素
        priority_queue<Website> pq; // 使用默认的大顶堆，但我们的比较器已经调整为小顶堆逻辑
        
        for (const auto& [url, count] : urlCount) {
            Website website{url, count};
            
            if (pq.size() < K) {
                pq.push(website);
            } else if (website < pq.top()) {
                // 如果当前网站比堆顶"更好"（在比较器中更小），则替换堆顶
                // 注意：我们的比较器定义的是小顶堆逻辑
                pq.pop();
                pq.push(website);
            }
        }
        
        // 将优先队列中的元素提取到vector中并排序（降序）
        vector<Website> result;
        while (!pq.empty()) {
            result.push_back(pq.top());
            pq.pop();
        }
        
        // 因为是小顶堆，需要反转顺序得到降序排列
        reverse(result.begin(), result.end());
        
        return result;
    }
};

int main() {
    FAST_IO;
    
    int K;
    cin >> K;
    cin.ignore(); // 忽略换行符
    
    HotWebsiteStats stats(K);
    string url;
    
    // 读取URL直到EOF
    while (getline(cin, url)) {
        if (!url.empty()) {
            stats.addVisit(url);
        }
    }
    
    vector<Website> topK = stats.getTopK();
    
    for (const auto& website : topK) {
        cout << website.url << " " << website.count << "\n";
    }
    
    return 0;
}

/*
测试用例1：
输入：
3
www.example.com
www.test.com
www.example.com
www.demo.com
www.test.com
www.example.com
www.demo.com

输出：
www.example.com 3
www.demo.com 2
www.test.com 2

测试用例2：
输入：
2
a.com
b.com
c.com
a.com
b.com
a.com

输出：
a.com 3
b.com 2

测试用例3：
输入：
1
site1.com
site2.com
site1.com
site3.com

输出：
site1.com 2

测试用例4：
输入：
5
only-one.com

输出：
only-one.com 1

测试用例5：
输入：
3
z.com
a.com
b.com
a.com
c.com
b.com
a.com
z.com

输出：
a.com 3
b.com 2
z.com 2
*/