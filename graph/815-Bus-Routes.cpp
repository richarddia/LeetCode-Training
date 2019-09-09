// 这个题其实就是一个bfs，只不过一次加的是整个bus路线上的所有点
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
        if ( S == T ) return 0;
        int n = routes.size();
        
        // key: stop   val: bus line
        unordered_map<int, vector<int>> stopMap;
        for ( int i = 0; i < routes.size(); ++i ) {
            for ( auto r : routes[i] ) {
                stopMap[r].push_back(i);
            }
        }
        int ans = 0;
        queue<int> q;
        vector<bool> visited(n, false);
        unordered_set<int> stopVisited = {S};
        q.push(S);
        while ( !q.empty() ) {
            int sz = q.size();
            for ( int i = 0; i < sz; ++i ) {
                int cur = q.front();
                q.pop();
                if ( cur == T ) return ans;
                for ( auto line : stopMap[cur] ) {
                    if ( !visited[line] ) {
                        visited[line] = true;
                        for ( auto x : routes[line] ) {
                            if ( stopVisited.find(x) == stopVisited.end() ) {
                                q.push(x);    
                                stopVisited.insert(x);
                            }
                        }
                    }
                }
            }
            ++ans;
        }
        return -1;
        
    }
};