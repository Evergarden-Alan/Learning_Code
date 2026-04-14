#include <bits/stdc++.h>
#define FAST_IO                  \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
using namespace std;

class Solution
{
private:
public:
    Solution()
    {
    }
};

bool nextStep(vector<vector<int>> &dist, vector<vector<int>> &count, int nx, int ny, int x, int y)
{
    if (dist[nx][ny] == -1)
        return false;
    if (dist[nx][ny] > dist[x][y] + 1)
    {
        dist[nx][ny] = dist[x][y] + 1;
        count[nx][ny] = count[x][y];
        return true;
    }
    if (dist[nx][ny] == dist[x][y] + 1)
    {
        count[nx][ny] = count[x][y] + 1;
        return true;
    }
}

int main()
{
    FAST_IO;

    int n;
    cin >> n;
    cin.ignore();

    string row_scout;
    getline(cin, row_scout);
    auto pos = row_scout.find(',');
    int x = stoi(row_scout.substr(pos - 1));
    int y = stoi(row_scout.substr(pos + 1));

    // init grid
    vector<vector<bool>> blocked(n, vector<bool>(n, false));
    vector<vector<int>> dist(n, vector<int>(n, -1));
    vector<vector<int>> count(n, vector<int>(n, 0));

    // sign scout square
    for (size_t i = x - 1; i <= x + 1; i++)
    {
        for (size_t j = y - 1; j <= y + 1; j++)
        {
            blocked[i][j] = true;
        }
    }

    int startX = 0, startY = n / 2;
    int endX = n - 1, endY = n / 2;

    if (blocked[startX][startY] || blocked[endX][endY])
    {
        cout << "0 0\n";
        return 0;
    }

    dist[startX][startY] = 1;
    count[startX][startY] = 1;

    queue<pair<int, int>> bfs;
    bfs.push({startX, startY});

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    //discovering
    while (!bfs.empty())
    {
        auto [X, Y] = bfs.front();
        bfs.pop();

        for (size_t i = 0; i < 4; i++)
        {
            int nx = X + dx[i];
            int ny = Y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < n && !blocked[nx][ny])
            {
                if (dist[nx][ny] == -1)
                {
                    dist[nx][ny] = dist[X][Y] + 1;
                    count[nx][ny] = count[X][Y];
                    bfs.push({nx, ny});
                }else if (dist[nx][ny] == dist[X][Y] + 1)
                {
                    count[nx][ny] += count[X][Y];
                }
            }
        }
    }


    //print result
    if (dist[endX][endY] == -1) {
        cout << "0 0\n";
    } else {
        cout << count[endX][endY] << " " << dist[endX][endY] << "\n";
    }

    return 0;
}