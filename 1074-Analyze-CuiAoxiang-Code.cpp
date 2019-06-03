const int N = 300 + 10;
int sum[N][N];
const int M = 600000 + 10;
const int OFFSET = M / 2;
int cnt[M]; //cache
int visit[M]; // cache的时间戳
unordered_map<int, int> cnt2;

class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& a, int target) {
        int n = a.size(), m = a[0].size();  
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                sum[i + 1][j + 1] = sum[i + 1][j] + sum[i][j + 1] - sum[i][j]
                    + a[i][j];
            }
        }
        // sum[i][j]表示前i行前j列圈出来部分的总和
        memset(::visit, 0, sizeof(::visit));
        int step = 1;
        int ret = 0;
        for (int i = 0; i < n; ++i) {
            for (int u = i + 1; u <= n; ++u) {
                cnt2.clear();
                for (int j = m - 1; j >= 0; --j) {
                    int x = sum[u][j + 1] - sum[i][j + 1] + OFFSET;
                    if (x >= 0 && x < M) {
                        if (::visit[x] == step) {
                            cnt[x]++;
                        } else {
                            cnt[x] = 1;
                            ::visit[x] = step;
                        }
                    } else {
                        cnt2[x]++;
                    }
                    x = target + sum[u][j] - sum[i][j] + OFFSET;
                    if (x >= 0 && x < M) {
                        if (::visit[x] == step) ret += cnt[x];
                    } else {
                        ret += cnt2[x];
                    }
                }
                ++step;
            }
        }
        return ret;
    }
};