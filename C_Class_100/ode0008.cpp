#include <bits/stdc++.h>
using namespace std;

class Solve
{
private:
    vector<int> preSum;

public:
    Solve(const vector<int> &percentage)
    {
        preSum.resize(percentage.size() + 1);
        preSum[0] = 0;
        for (int i = 1; i < preSum.size(); i++)
        {
            preSum[i] = preSum[i - 1] + percentage[i - 1];
        }
    }

    vector<int> maxRange(int minAverageLost)
    {
        vector<int> result(2, 0);
        for (int i = 1, j = 0; i < preSum.size();)
        {
            double calAverageLost = (double)(preSum[i + 1] - preSum[j]) / (i - j + 1);
            if (calAverageLost < minAverageLost)
            {
                if ((i - j + 1) > (result[1] - result[0]))
                {
                    result[1] = i + 1;
                    result[0] = j;
                }
                i++;
            }
            else
            {
                j++;
            }
        }

        return result;
    }
};

int main()
{
    int minAverageLost = 0;
    vector<int> percentage(100);

    cin >> minAverageLost;
    cin.ignore();
    string line;
    getline(cin, line);
    istringstream iss(line);

    int temp;
    while (iss >> temp)
    {
        percentage.push_back(temp);
    }

    Solve sol = Solve(percentage);
    vector<int> result = sol.maxRange(minAverageLost);

    cout << result[0] << "-" << result[1];

    return 0;
}
