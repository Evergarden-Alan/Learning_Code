#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
using namespace std;

class Solution {
private:

public:
    Solution() {
        
    }
};


int main() {
    FAST_IO;
    //1. command error ->fail
    //2. add id exists -> fail
    //3. modify id not exists && index==old -> fail
    //4. delete id not exists -> fail
    //out fail num

    string row_command;
    unordered_map<string,string> commands;
    int count_fail=0;
    while (getline(cin,row_command))
    {
        if(row_command=="") break;

        stringstream cstream(row_command);
        vector<string> command;
        string keyword;
        while (getline(cstream,keyword,' '))
        {
            command.push_back(keyword);
        }
        
        if(command[0]=="add_rule"){
            if (command.size()<3){
                count_fail++;
                continue;
            } 
            auto pos_id = command[1].find('=');
            auto pos_index = command[2].find('=');
            if(commands.count(command[1].substr(pos_id+1))!=0){
                count_fail++;
                continue;
            }
            if(stoi(command[2].substr(pos_index+1))>=10000){
                count_fail++;
                continue;
            }
            commands[command[1].substr(pos_id+1)] = command[2].substr(pos_index+1);
            continue;
        }

        if(command[0]=="mod_rule"){
            if (command.size()<3){
                count_fail++;
                continue;
            }
            auto pos_id = command[1].find('=');
            auto pos_index = command[2].find('=');
            if(commands.count(command[1].substr(pos_id+1))==0){
                count_fail++;
                continue;
            }
            if(stoi(command[2].substr(pos_index+1))==stoi(commands[command[1].substr(pos_id+1)])){
                count_fail++;
                continue;
            }
            commands[command[1].substr(pos_id+1)] = command[2].substr(pos_index+1);
            continue;
        }
        
        if(command[0]=="del_rule"){
            auto pos_id = command[1].find('=');
            if (command.size()<2){
                count_fail++;
                continue;
            }
            if(commands.count(command[1].substr(pos_id+1))==0){
                count_fail++;
                continue;
            }

            commands.erase(command[1].substr(pos_id+1));
        }
    }
        
        
    cout<<count_fail;

    return 0;
}