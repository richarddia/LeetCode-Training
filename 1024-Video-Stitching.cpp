// 这个题挺有意思
// 看了题以后思维还是被局限到了是按照start排序还是按照end排序
// 本质是用最少的区间去凑一个大区间
// 思路是尽量往远走，因为我们要覆盖[0, T]整个区间，所以每个点都要照顾到
// 在照顾某个点P的同时，我们就像挑那些既能覆盖P同时还能尽量往远覆盖的video
// 复杂度nlogn

class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int T) {
        sort(clips.begin(), clips.end());
        int pt = 0;
        int cur = 0;
        int res = 0;
        while ( cur < T ) {
            int next = cur;
            while ( pt < clips.size() && clips[pt][0] <= cur ) {
                next = max(next, clips[pt][1]);
                ++pt;                    
            }
            if ( next == cur ) return -1;
            cur = next;
            ++res;
        }
        return res;
    }
};