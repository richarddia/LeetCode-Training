class Solution {
public:
    vector<int> splitIntoFibonacci(string S) {
        // 这个题写起来超级恶心
        int n = S.length();
        long a = 0; long b = 0;
        for ( int i = 0; i < n - 2; ++i ) {
            if ( i > 0 && S[0] == '0' ) break;
            a = a * 10 + S[i] - '0';
            if ( a > INT_MAX ) break;
            b = 0;
            for ( int j = i + 1; j < n - 1; ++j ) {
                if ( j > i + 1 && S[i+1] == '0' ) break;
                b = b * 10 + S[j] - '0';
                if ( b > INT_MAX ) break;
                int pt = j + 1;
                vector<int> res{ a, b };
                // 一开始这里也用了a 和 b,导致循环变量混乱
                long a1 = a; long b1 = b;
                while ( pt < n ) {
                    long c = a1 + b1;
                    if ( c > INT_MAX ) break;
                    string cStr = to_string( c );
                    if ( cStr != S.substr( pt, cStr.length() ) ) break;
                    res.push_back( (int)c );
                    pt += cStr.length();
                    a1 = b1;
                    b1 = c;
                }
                if ( pt == n ) return res;
            }
        }
        return vector<int>();
    }
};