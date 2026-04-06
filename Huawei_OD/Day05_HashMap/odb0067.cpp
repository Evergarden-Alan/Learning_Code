#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
using namespace std;



struct Compare
{
    bool operator()(const pair<int,int>& a,const pair<int,int>& b){
        if (a.second!=b.second)
        {
            return a.second<b.second;
        }
        
        return (a.first<b.first); 
    }
};


class Solution{
private:
    unordered_map<int,priority_queue<int>>  user_map;
public:
    Solution(vector<int> id,vector<int> score){ 
        for (size_t i = 0; i < id.size(); i++)
        {
            // priority_queue<int> temp = user_map[id[i]];
            // temp.push(score[i]);
            // user_map[id[i]] = temp;
            user_map[id[i]].push(score[i]);
        }
        
    }

    vector<int> getResult(){
        priority_queue<pair<int,int>,vector<pair<int,int>>,Compare> temp;

        for(auto& [key, value] : user_map){
            if(value.size()<3) continue;
            int sum=0;
            for (size_t i = 0; i < 3; i++)
            {
                int top = value.top();
                value.pop();
                sum+=top;
            }
            temp.push({key,sum});            
            // result.push_back()
        }

        vector<int> result;
        while (!temp.empty())
        {
            int id = temp.top().first;
            result.push_back(id);
            temp.pop();
        }
        
        return result;
    }
};


int main(){
    FAST_IO;
    int N;
    cin>>N;
    cin.ignore();
    string ids;
    string scores;

    getline(cin,ids);
    getline(cin,scores);

    stringstream idss(ids);
    stringstream scoress(scores);

    vector<int> id;
    vector<int> score;

    string temp;
    while (getline(idss,temp,','))
    {
        id.push_back(stoi(temp));
    }
    while (getline(scoress,temp,','))
    {
        score.push_back(stoi(temp));
    }
    
    Solution solu = Solution(id,score);
    
    vector<int> result = solu.getResult();

    for (size_t i = 0; i < result.size(); i++)
    {
        cout<<result[i];
        if(i<result.size()-1) cout<<',';
    }
    


    return 0;
}