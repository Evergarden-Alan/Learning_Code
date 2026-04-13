#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
using namespace std;



class Solution{
private:
public:
    int getresult(vector<vector<int>>& services,int k){
        vector<int> service = services[k-1];

        int result=0;
        for(int i=0;i<service.size();i++){
            if(service[i]==1){
                result += getresult(services,i+1);
            }
        }
        result += services[k-1][k-1];

        return result;
    }
};


int main(){
    FAST_IO;

    int n,k;
    cin>>n;
    cin.ignore();

    vector<vector<int>> services;

    string raw_service;
    while(services.size()<n){
        getline(cin,raw_service);
        stringstream ss(raw_service);
        string c;
        vector<int> use_time;
        while(getline(ss,c,' ')){
            use_time.push_back(stoi(c));
        }
        services.push_back(use_time);
    }

    cin>>k;
    cin.ignore();

    Solution solu = Solution();
    cout<<solu.getresult(services,k);

    return 0;
}