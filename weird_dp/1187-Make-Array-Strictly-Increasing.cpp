const int mx = 1 << 30;
class Solution {
public:
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        int m = arr1.size();
        set<int> st;
        for ( auto x : arr2 ) st.insert(x);
        int n = st.size();
        // dp[i][j]表示0到j(左闭右闭) 被换过i个数字以后，j那个位置(尾巴上)最小能是多少
        int dp[m][n+1];
        for ( int j = 0; j <= n; ++j ) dp[0][j] = mx;
        dp[0][0] = arr1[0];
        if ( n > 1 ) dp[0][1] = *st.begin(); 
//                            dp[i][j]候选值         
//         dp[i][j] =         arr1[i] if arr1[i] > dp[i-1][j]  如果之前都换过j次了，arr1的当前值只有比之前的尾巴大才能有资格当个候选值
//                            st中第一个大于dp[i-1][j-1]的值 if dp[i-1][j-1] != 1 << 30; 如果之前换了j-1次了，当前又必须得换，那就在set里找个比之前尾巴大一号的数换上去吧
        
        for ( int i = 1; i < m; ++i ) {
            for ( int j = 0; j <= n; ++j ) {
                dp[i][j] = mx;
                if ( arr1[i] > dp[i-1][j] ) dp[i][j] = min(dp[i][j], arr1[i]);
                
                if ( j >= 1 && dp[i-1][j-1] != mx ) {
                    auto it = st.upper_bound(dp[i-1][j-1]);
                    if ( it != st.end() ) dp[i][j] = min(dp[i][j], *it);
                }
            }
        }
        
        
        for ( int j = 0; j <= n; ++j ) {
            if ( dp[m-1][j] != mx ) return j;
        }
        return -1;
    }
};