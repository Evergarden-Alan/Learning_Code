#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
using namespace std;



class Solution{
private:
    unordered_map<char,int> count;
    unordered_map<char,int> excess;
    string optss;
    int N;

public:
    Solution(string opts,int n){
        N = n;
        optss = opts;
        for (int i = 0; i < opts.length(); i++)
        {
           count[opts[i]]++;
           excess[opts[i]] = max(0,count[opts[i]]-N/4); 
        }
        
        
    }
    int min_continue_len(){
        int result=N+1;
        int need = 0;
        for(auto [key,value]:excess){
            if(value>0) need ++;
        }
        if(need==0) return 0;
        unordered_map<char,int> win;
       
        for (int right = 0,left=0; right < N; right++)
        {
            char c = optss[right];

            win[c]++;
            if(win[c]==excess[c]) need--;
           
            while (need==0)
            {
                result = min(result,right-left+1);
                if(win[optss[left]]==excess[optss[left]]) need++;
                win[optss[left]]--;
                left++;
            }
           
           
        }

        // result = (result==N+1 ? 0:result);
        return result; 

    }

};


int main(){
    FAST_IO;
    string opts;
    getline(cin,opts);

   Solution solu = Solution(opts,opts.length()); 

   cout<<solu.min_continue_len();
    
    return 0;
}