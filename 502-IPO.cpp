class Solution {
    struct Proj {
        int p;
        int c;
        Proj ( int p, int c ) : p{p}, c{c} {
            
        }
    };
public:
    int findMaximizedCapital(int k, int W, vector<int>& Profits, vector<int>& Capital) {
        // 题目很长，但是核心意思很简单，想法也比较直接，就是每一轮在能够完成的project里面挑出利润最大的
        int n = Profits.size();
        vector<Proj> proj;
        for ( int i = 0; i < n; ++i ) {
            proj.push_back( Proj( Profits[i], Capital[i] ) );
        }
        sort( proj.begin(), proj.end(), []( const Proj& lhs, const Proj& rhs ) {
            return lhs.c < rhs.c;
        });
        int pt = 0;
        priority_queue<int> pq;
        for ( int i = 0; i < k; ++i ) {
            // 这个题的技巧就是每次只把能做的proj放到pq里，再找出利润最大的那个
            while ( pt < n && proj[pt].c <= W ) {
                pq.push( proj[pt++].p );
            }
            if ( pq.empty() ) break;
            W += pq.top();
            pq.pop();
        }
        return W;
    }
};