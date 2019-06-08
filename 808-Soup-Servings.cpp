// 这个题最初是用py写的，用了py中tuple可以hash的性质，有点作弊的嫌疑，一直在想c++里面没有hash tuple的时候该怎么办，在经过magic number处理过后，N就变小了，只需要考虑5000以内就可以。这个时候再用最小度量25一做除法，N就更小了，5000/25 = 200，也就是说如果写一个dp表来存是不会MLE的，也就201*201那么大，于是就用cpp写出了第一版

//还有一处值得学习的地方是手动求上取整除法
//m/m(上取整) = m/n + (m%n != 0);

class Solution {
public:
    double soupServings(int N) {
        if ( N > 5000 ) return 1.0;
        N = N / 25 + ( N % 25 != 0 );
        vector<vector<double>> dp(N+1, vector<double>(N+1, -1));
        return helper(dp, N, N);
    }
    
    double helper(vector<vector<double>>& dp, int A, int B) {
        if ( A <= 0 && B > 0 ) return 1.0;
        if ( A <= 0 && B <= 0 ) return 0.5;
        if ( A >= 0 && B <= 0 ) return 0;
        if ( dp[A][B] >= 0 ) return dp[A][B];
        dp[A][B] = 0.25*(helper(dp, A-4, B) + helper(dp, A-3, B-1) + 
                         helper(dp, A-2, B-2) + helper(dp, A-1, B-3));
        return dp[A][B];
    }
};

//后面又看了一个答案，把二维数组通过行列关系转换成一维也是可以实现的，只需要知道最大列数即可。dp[i][j]就转换成了dp[i*colNum+j]

class Solution {
public:
    double soupServings(int N) {
        if ( N > 5000 ) return 1.0;
        N = N / 25 + ( N % 25 != 0 );
        unordered_map<int, double> dp;
        return helper(dp, N, N);
    }
    
    double helper(unordered_map<int, double>& dp, int A, int B) {
        if ( A <= 0 && B > 0 ) return 1.0;
        if ( A <= 0 && B <= 0 ) return 0.5;
        if ( A >= 0 && B <= 0 ) return 0;
        int key = A*201 + B;
        if (dp.find(key) == dp.end()) {
            dp[key] = 0.25*(helper(dp, A-4, B) + helper(dp, A-3, B-1) + 
                         helper(dp, A-2, B-2) + helper(dp, A-1, B-3));
        }
        return dp[key];
    }
};