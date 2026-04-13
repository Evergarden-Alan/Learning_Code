#include <bits/stdc++.h>
#define FAST_IO                  \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
using namespace std;

class Printer
{
private:
    int max_len = -1;
    vector<int> preSum;

public:
    Printer(const vector<int> &nums)
    {
        preSum.push_back(0);

        for (size_t i = 0; i < nums.size(); i++)
        {
            preSum.push_back(preSum[i] + nums[i]);
        }
    }

    int getMax(int target)
    {
        for (int i = 0; i < (int)preSum.size(); i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (preSum[i] - preSum[j] < target)
                {
                    break;
                }
                else if (preSum[i] - preSum[j] == target)
                {
                    max_len = max(max_len, i - j);
                }
            }
        }
        return max_len;
    }

    int getMax_slideWindow(int target, const vector<int> &nums)
    {
        int currentSum = 0;
        for (int right = 0, left = 0; right < (int)nums.size(); right++)
        {
            currentSum += nums[right];
            while (currentSum > target)
            {
                currentSum -= nums[left];
                left++;
            }
            if (currentSum == target)
            {
                max_len = max(max_len, right - left + 1);
            }
        }
        return max_len;
    }
};

int main()
{
    string line;

    if (!getline(cin, line))
    {
        return 0;
    }

    vector<int> nums;
    stringstream ss(line);
    string temp;

    while (getline(ss, temp, ','))
    {
        if (!temp.empty())
        {
            nums.push_back(stoi(temp));
        }
    }

    int sum;
    cin >> sum;

    Printer solu = Printer(nums);

    cout << solu.getMax_slideWindow(sum, nums);

    return 0;
}