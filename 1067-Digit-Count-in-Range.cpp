// 终于还是把这道题改成了自己的套路

class Solution {
public:
    int digitsCount(int d, int low, int high) {
        vector<int> digits;
        int dp[10] = { 0 };
        // dp[1] = 1; dp[2] = 2 * 10; dp[3] = 3*100;
        for ( int i = 1; i <= 9; ++i ) {
            dp[i] = i * (int)pow(10, i - 1);
        }
        return count(d, high, dp) - (low == 1 ? 0 : count(d, low - 1, dp));
    }
    
    int count(int d, int num, int* dp) {
        int n = num;
        vector<int> digits;
        while ( num > 0 ) {
            digits.push_back( num % 10 );
            num /= 10;
        }
        int base = (int)pow(10, digits.size() - 1 );
        int res = 0;
        int n1 = 1;
        int j = 0;
        while ( n1 < base ) {
            res += 9 * dp[j]; // {1-9}XXXX, 其中XXXX中的d出现了9次
            if ( d != 0 ) res += n1;
            n1 *= 10;
            ++j;
        }
        int pre = 0;
        for ( int i = digits.size() - 1; i >= 0; --i ) {
            int k = 0;
            if ( i == digits.size() - 1 ) ++k; //最高位不能以0开头
            while ( k < digits[i] ) {
                res += dp[i];
                res += pre * (int)pow( 10, i );
                if ( k == d ) res += (int)pow( 10, i );
                ++k;
            }
            if ( digits[i] == d ) { 
                pre++;
                res++;
            }
        }
        return res;
    }
};