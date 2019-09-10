const int mod = 1e9 + 7;
class Solution {
public:
    int longestDecomposition(string text) {
        int n = text.length();
        return helper(text, 0, n - 1);
    }
    
    int helper(const string& s, int i, int j) {
        if ( i > j ) return 0;
        if ( i == j ) return 1;
        int mid = ( j - i ) / 2 + i;
        
        int l = i, r = j;
        long h1 = 0, h2 = 0;
        long base = 1;
        
        while ( l < r ) {
            // rolling hash的核心部分
            // 如果当前到达的是最高位，那就用base
            h1 = ( h1 + base * ( s[l] - 'a' ) ) % mod;
            // 如果当前到达的是最低为，那就整体移动
            h2 = ( h2 * 26 + ( s[r] - 'a' ) ) % mod;
            
            if ( h1 == h2 && s.substr(i, l - i + 1) == s.substr(r, j - r + 1) ) {
                return 2 + helper(s, l + 1, r - 1);
            }
            base = base * 26 % mod;
            ++l;
            --r;
        }
        return 1;
    }
};