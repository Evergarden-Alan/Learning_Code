#include <bits/stdc++.h>
using namespace std;

class Printer
{
private:
    vector<int> preSum;
    int MAX_LEN=-1;

public:
    Printer(vector<int>& percentage){
        preSum.push_back(0);
        for (int i = 1; i <= percentage.size(); i++)
        {
            preSum.push_back(percentage[i-1] + preSum[i-1]);
        }
        
    }

    vector<vector<int>> find_max(){
        vector<vector<int>> result;
        for (int i = 0; i < preSum.size(); i++)
        {
            for (int j = 0; j < i ; j++)
            {
                if(preSum[i]-preSum[j]<=0){
                    if(i-j>MAX_LEN){
                        MAX_LEN = i-j;
                        result.clear();
                        result.push_back({j,i-1});
                    }else if( i-j==MAX_LEN){
                        result.push_back({j,i-1});
                    }
                    
                }
            }
            
        }
        return result;
    } 
    
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int minAverageLost;

    if(cin>>minAverageLost){
        string dummy;
        getline(cin,dummy);

        string line;
        getline(cin,line);
        istringstream iss(line);
        vector<int> percentage;
        int temp;
        while (iss >> temp)
        {
            percentage.push_back(temp-minAverageLost);
        }
        

        Printer solu = Printer(percentage);
        vector<vector<int>> result = solu.find_max();

        if(result.empty()){
            cout<<"NULL";
        }else{
            for (int i = 0; i < result.size(); i++)
            {
                cout<<result[i][0]<<"-"<<result[i][1]<<" ";
            }

        }
                
    }


    return 0;
}
