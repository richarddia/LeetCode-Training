class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        // single source shortest path
        // BellmanFord
        int n = times.size();
        vector<int> path(N + 1, 1 << 30);
        path[K] = 0;
        int u, v, w;
        for ( int k = 1; k <= N; ++k ) {
            for ( int i = 0; i < n; ++i ) {
                u = times[i][0], v = times[i][1], w = times[i][2];
                path[v] = min(path[v], path[u] + w);
            }
        }
        int res = *max_element(path.begin() + 1, path.end());
        if ( res == 1 << 30 ) return -1;
        return res;
    }
};