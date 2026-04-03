#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
using namespace std;

struct Site
{
    string domain;
    int count;
};

struct CompareCount
{
    bool operator()(Site const& a,Site const& b){
        if(a.count!=b.count){
            return a.count<b.count;
        }
        return a.domain>b.domain;
    }
};



class Solution{
private:
    unordered_map<string,int> countSite;
    priority_queue<Site,vector<Site>,CompareCount> pq;

public:
    Solution(){
    }
    void add(string domain){
        countSite[domain]++;
        pq.push({domain,countSite[domain]});
    }

    vector<Site> getTop(int K){
        vector<Site> result;
        if(K<=0) return result;

        // vector<Site> temp;
        while (!pq.empty()&&K)
        {
            Site top = pq.top();
            // temp.push_back(top);
            pq.pop();

            if(top.count!=countSite[top.domain]) continue;
            result.push_back(top);
            // pq.push(top);  
            K--;
        }

        for(auto const& entry:result){
            pq.push(entry);
        }

        return result;      
    }
};


int main(){
    FAST_IO;

    string line;
    Solution solu = Solution();
    vector<Site> result;
    while(getline(cin,line))
    {
        if(line.empty()) break; 
        bool isNum = true;
        for (char c:line)
        {
            if(!isdigit(c)){
                isNum=false;
                break;
            }
        }
        
        if(isNum){
            int K = stoi(line);
            result = solu.getTop(K);       
            for(size_t i=0;i< result.size();i++){
                cout<<result[i].domain;
                if(i<result.size()-1) cout<<",";
            }
            cout<<"\n";
        }else{
            solu.add(line);
        }

        
    }
    
        
    

    return 0;
}