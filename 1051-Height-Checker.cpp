class Solution {
public:
    int heightChecker(vector<int>& heights) {
        //这题没什么意思，以后基本上都不用再看了
        int res = 0;
        vector<int> arr(heights);
        sort(arr.begin(), arr.end());
        for ( int i = 0; i < heights.size(); ++i ) {
            res += (arr[i] != heights[i]);
        }
        return res;
    }
};