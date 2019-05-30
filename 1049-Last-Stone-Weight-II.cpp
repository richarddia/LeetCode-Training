class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        // 核心思路: 每一种消消乐都可以转成 \Sigma_{i = 0}^{i = n - 1} +/-1*stones[i]
        unordered_set<int> st{0};
        for( auto& x : stones ) {
            unordered_set<int> next;
            for ( auto& y : st ) {
                next.insert(x + y);
                next.insert(abs(x - y));
            }
            st = next;
        }
        return *min_element(st.begin(), st.end());
    }
};