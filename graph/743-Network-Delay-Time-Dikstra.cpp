class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        //Dijkstra
        using P = pair<int, int>;
        int n = times.size();
        vector<int> path(N+1, 1 << 30);
        priority_queue<P, vector<P>, greater<P>> pq;
        path[K] = 0;
        pq.push({0, K});
        vector<P> graph[N + 1];
        
        for ( auto& time : times ) {
            graph[time[0]].push_back({time[1], time[2]});
        }
        
        while ( !pq.empty() ) {
            auto cur = pq.top();
            pq.pop();
            int u = cur.second;
            for ( int i = 0; i < graph[u].size(); ++i ) {
                int v = graph[u][i].first;
                int w = graph[u][i].second;
                if ( path[v] > path[u] + w ) {
                    path[v] = path[u] + w;
                    pq.push({path[v], v});
                }
            }
        }
        
        int res = 0;
        for ( int i = 1; i <= N; ++i ) {
            if ( path[i] == 1 << 30 ) return -1;
            res = max(res, path[i]);
        }
        return res;
    }
};