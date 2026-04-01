#include <bits/stdc++.h>
#define FAST_IO                  \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
using namespace std;

/*
题目：根据IP查找城市 (odb0042)
考点：优先队列
分值：200分
在线OJ链接：https://hydro.ac/d/coder_gather/p/odb0042

题目描述：
给定一批IP地址和对应的城市信息，以及一批查询IP。
对于每个查询IP，需要找到包含该IP的IP段对应的城市。
如果有多个IP段包含该查询IP，选择范围最小的IP段（即子网掩码最长的）。
如果仍有多个，选择城市编号最小的。

IP地址格式：点分十进制，如192.168.1.1
IP段格式：起始IP-结束IP，如192.168.1.0-192.168.1.255

输入格式：
第一行两个整数N和M，N表示IP段数量，M表示查询IP数量
接下来N行，每行格式：起始IP 结束IP 城市编号
接下来M行，每行一个查询IP

输出格式：
对于每个查询IP，输出对应的城市编号。
如果没有匹配的IP段，输出-1。

示例输入：
3 4
192.168.1.0 192.168.1.255 1
192.168.0.0 192.168.255.255 2
10.0.0.0 10.255.255.255 3
192.168.1.100
192.168.2.1
10.1.1.1
172.16.1.1

示例输出：
1
2
3
-1

解释：
192.168.1.100 匹配第一个IP段（最精确）
192.168.2.1 匹配第二个IP段
10.1.1.1 匹配第三个IP段
172.16.1.1 没有匹配

解题思路：
1. 将IP地址转换为32位整数便于比较
2. 对于每个查询IP，需要找到包含该IP的所有IP段
3. 使用优先队列维护匹配的IP段，按以下顺序排序：
   a) 范围小的优先（结束IP-起始IP小的优先）
   b) 范围相同，城市编号小的优先
4. 对于每个查询，遍历所有IP段，将匹配的加入优先队列，取队首

优化思路：
由于N和M可能较大，需要优化查询效率。
可以将IP段按起始IP排序，使用二分查找快速定位可能匹配的IP段。
*/

// 将点分十进制IP转换为32位整数
unsigned int ipToInt(const string& ip) {
    unsigned int result = 0;
    stringstream ss(ip);
    string segment;
    
    for (int i = 3; i >= 0; i--) {
        getline(ss, segment, '.');
        unsigned int num = stoi(segment);
        result |= (num << (i * 8));
    }
    
    return result;
}

// 将32位整数转换为点分十进制IP（用于调试）
string intToIp(unsigned int ip) {
    stringstream ss;
    ss << ((ip >> 24) & 0xFF) << "."
       << ((ip >> 16) & 0xFF) << "."
       << ((ip >> 8) & 0xFF) << "."
       << (ip & 0xFF);
    return ss.str();
}

struct IPRange {
    unsigned int startIp;
    unsigned int endIp;
    int cityId;
    unsigned int rangeSize; // 预计算范围大小，避免重复计算
    
    IPRange(unsigned int start, unsigned int end, int city) 
        : startIp(start), endIp(end), cityId(city) {
        rangeSize = endIp - startIp;
    }
    
    // 检查IP是否在范围内
    bool contains(unsigned int ip) const {
        return ip >= startIp && ip <= endIp;
    }
};

// 优先队列比较器：用于选择最佳匹配
struct CompareIPRange {
    bool operator()(const IPRange& a, const IPRange& b) const {
        // 范围小的优先
        if (a.rangeSize != b.rangeSize) {
            return a.rangeSize > b.rangeSize; // 小顶堆需要反向比较
        }
        // 范围相同，城市编号小的优先
        return a.cityId > b.cityId; // 小顶堆需要反向比较
    }
};

class IPCityFinder {
private:
    vector<IPRange> ipRanges;
    int n;
    
public:
    IPCityFinder(int num) : n(num) {}
    
    void addRange(const string& startIpStr, const string& endIpStr, int cityId) {
        unsigned int startIp = ipToInt(startIpStr);
        unsigned int endIp = ipToInt(endIpStr);
        ipRanges.emplace_back(startIp, endIp, cityId);
    }
    
    int findCityForIP(const string& ipStr) {
        unsigned int queryIp = ipToInt(ipStr);
        
        // 使用优先队列存储所有匹配的IP段
        priority_queue<IPRange, vector<IPRange>, CompareIPRange> matchingRanges;
        
        // 遍历所有IP段，找到包含查询IP的段
        for (const auto& range : ipRanges) {
            if (range.contains(queryIp)) {
                matchingRanges.push(range);
            }
        }
        
        // 如果没有匹配的IP段
        if (matchingRanges.empty()) {
            return -1;
        }
        
        // 返回最佳匹配的城市编号
        return matchingRanges.top().cityId;
    }
    
    // 优化版本：先按起始IP排序，使用二分查找减少遍历次数
    void sortRanges() {
        sort(ipRanges.begin(), ipRanges.end(), 
             [](const IPRange& a, const IPRange& b) {
                 return a.startIp < b.startIp;
             });
    }
    
    int findCityForIPOptimized(const string& ipStr) {
        unsigned int queryIp = ipToInt(ipStr);
        
        // 使用优先队列存储匹配的IP段
        priority_queue<IPRange, vector<IPRange>, CompareIPRange> matchingRanges;
        
        // 二分查找：找到第一个起始IP大于查询IP的位置
        auto it = upper_bound(ipRanges.begin(), ipRanges.end(), queryIp,
                             [](unsigned int ip, const IPRange& range) {
                                 return ip < range.startIp;
                             });
        
        // 从开始到it-1的位置都可能包含查询IP
        for (auto iter = ipRanges.begin(); iter != it; ++iter) {
            if (iter->contains(queryIp)) {
                matchingRanges.push(*iter);
            }
        }
        
        // 如果没有匹配的IP段
        if (matchingRanges.empty()) {
            return -1;
        }
        
        return matchingRanges.top().cityId;
    }
};

int main() {
    FAST_IO;
    
    int N, M;
    cin >> N >> M;
    
    IPCityFinder finder(N);
    
    // 读取IP段信息
    for (int i = 0; i < N; i++) {
        string startIp, endIp;
        int cityId;
        cin >> startIp >> endIp >> cityId;
        finder.addRange(startIp, endIp, cityId);
    }
    
    // 对IP段排序（用于优化查询）
    finder.sortRanges();
    
    // 处理查询
    for (int i = 0; i < M; i++) {
        string queryIp;
        cin >> queryIp;
        int cityId = finder.findCityForIPOptimized(queryIp);
        cout << cityId << "\n";
    }
    
    return 0;
}

/*
测试用例1：
输入：
3 4
192.168.1.0 192.168.1.255 1
192.168.0.0 192.168.255.255 2
10.0.0.0 10.255.255.255 3
192.168.1.100
192.168.2.1
10.1.1.1
172.16.1.1

输出：
1
2
3
-1

测试用例2：
输入：
2 3
0.0.0.0 255.255.255.255 0
192.168.0.0 192.168.255.255 1
192.168.1.1
10.0.0.1
192.168.255.255

输出：
1
0
1

测试用例3：
输入：
4 5
1.1.1.0 1.1.1.255 10
1.1.0.0 1.1.255.255 20
1.0.0.0 1.255.255.255 30
0.0.0.0 255.255.255.255 40
1.1.1.1
1.1.2.1
1.2.1.1
2.1.1.1
1.1.1.255

输出：
10
20
30
40
10

测试用例4：
输入：
3 3
10.0.0.0 10.0.0.255 100
10.0.0.128 10.0.0.255 200
10.0.0.192 10.0.0.223 300
10.0.0.200
10.0.0.150
10.0.0.100

输出：
300
200
100

测试用例5：
输入：
1 2
192.168.1.0 192.168.1.127 50
192.168.1.64
192.168.1.128

输出：
50
-1

测试用例6：范围相同，选择城市编号小的
输入：
3 2
1.0.0.0 1.0.0.255 30
1.0.0.0 1.0.0.255 20
1.0.0.0 1.0.0.255 10
1.0.0.100
1.0.0.200

输出：
10
10
*/