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