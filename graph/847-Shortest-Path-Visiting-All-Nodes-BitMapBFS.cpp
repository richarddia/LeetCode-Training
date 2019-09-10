#define N 15
bool path[1 << N][N];
// 状态压缩搜索问题path[i][j]表示在i状态且最后落在node j需要几步，这里用了一个bool是因为我们只需要标记它走过了没
// 题目钟给的图权值都是1，bfs时候第一次碰到一定是最短距离

class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        memset(path, 0, sizeof(path));
        using P = pair<int, int>;
        int n = graph.size();
        if ( n == 1 ) return 0;
        queue<P> q;
        
        for ( int i = 0; i < n; ++i ) {
            q.push({1 << i, i});
            path[1<<i][i] = true;
        }
        
        int res = 0;
        while ( !q.empty() ) {
            ++res;
            int sz = q.size();
            for ( int i = 0; i < sz; ++i ) {
                P cur = q.front();
                int u = cur.first;
                q.pop();
                for ( auto nei : graph[cur.second] ) {
                    int v = cur.first | ( 1 << nei );
                    if ( v == ( 1 << n ) - 1 ) return res;
                    if ( path[v][nei] == false ) {
                        path[v][nei] = true;
                        q.push({v, nei});
                    }
                }
            }
        }
        return -1;
    }
};