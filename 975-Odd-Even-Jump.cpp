class Solution {
public:
    int oddEvenJumps(vector<int>& A) {
        // 通过这道题学习一下map怎么找小于等于key的第一个和小于key的第一个
        int n = A.size();
        bool evenReach[n] = {0};
        bool oddReach[n] = {0};
        evenReach[n-1] = true; oddReach[n-1] = true;
        int res = 1;
        map<int, int> mp;
        mp[A[n-1]] = n-1;
        for ( int i = n-2; i >= 0; --i ) {
            auto hi = mp.upper_bound(A[i]);
            auto lo = mp.lower_bound(A[i]);
            if ( lo != mp.end() ) {
                oddReach[i] = evenReach[lo->second];
                res += oddReach[i];
            }
            if ( hi != mp.begin() ) evenReach[i] = oddReach[(--hi)->second];
            mp[A[i]] = i;
        }
        return res;
    }
};

// 试着用单调栈写了一下，直接用单调栈是不行的，还是要先排序
class Solution {
public:
    int oddEvenJumps(vector<int>& A) {
        int n = A.size();
        int index[n];
        int oddNext[n];
        int evenNext[n];
        stack<int> st;
        for ( int i = 0; i < n; ++i ) {
            index[i] = i;
        }
        sort( index, index + n, [&A](int a, int b) {
            return A[a] == A[b] ? a < b : A[a] < A[b];
        });
         for ( int i = n - 1; i >= 0; --i ) {
            int idx = index[i];
            while ( !st.empty() && st.top() < idx ) st.pop();
            oddNext[idx] = st.empty() ? -1 : st.top();
            st.push( idx );
        }
        while ( !st.empty() ) st.pop();
        sort( index, index + n, [&A](int a, int b) {
            return A[a] == A[b] ? a < b : A[a] > A[b];
        });
        for ( int i = n - 1; i >= 0; --i ) {
            int idx = index[i];
            while ( !st.empty() && st.top() < idx ) st.pop();
            evenNext[idx] = st.empty() ? -1 : st.top();
            st.push( idx );
        }
        bool odd[n];
        bool even[n];
        odd[n - 1] = true;
        even[n - 1] = true;
        int res = 1;
        for ( int i = n - 2; i >= 0; --i ) {
            if ( oddNext[i] == -1 ) odd[i] = false;
            else odd[i] = even[oddNext[i]];
            
            if ( evenNext[i] == -1 ) even[i] = false;
            else even[i] = odd[evenNext[i]];
            res += odd[i];
        }
        return res;
    }
};