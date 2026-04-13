#include<bits/stdc++.h>
using namespace std;

class Solve{
    public:

        int maxLen(int N,int M,const vector<int>& blank,int K){
            int maxNum = -1;

            for (int i = 1,j=i+K-1; j < M+1; i++,j++)
            {
                maxNum = max(maxNum,blank[j+1]-1-blank[i-1]);
            }
            
            return maxNum;
        }

};


int main(){
    int N,M,K;
    cin>>N>>M;

    vector<int> blank(M+2);
    blank[0]=0;
    blank[M+1]=N+1;
    for (int i = 1; i < M+1; i++)
    {
        cin>>blank[i];
    }

    cin>>K;
    if(K==M){
        cout<<N;
        return 0;  
    }
    Solve sol = Solve();
    cout<<sol.maxLen(N,M,blank,K);
    return 0;
}
