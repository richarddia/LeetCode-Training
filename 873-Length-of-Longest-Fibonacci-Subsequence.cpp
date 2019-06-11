class Solution {
public:
    int lenLongestFibSubseq(vector<int>& A) {
        unordered_set<int> st( A.begin(), A.end() );
        int res = 0;
        for ( int i = 0; i < A.size(); ++i ) {
            for ( int j = i + 1; j < A.size(); ++j ) {
                if ( A[j] - A[i] < A[i] && st.find( A[j] - A[i] ) != st.end() ) continue;
                int ans = 2;
                int a = A[i]; int b = A[j];
                while ( a + b <= A.back() && st.find( a + b ) != st.end() ) {
                    int c = a + b;
                    a = b;
                    b = c;
                    ++ans;
                }
                res = max( res, ans );
            }
        }
        if ( res >= 3 ) return res;
        return 0;
    }
};