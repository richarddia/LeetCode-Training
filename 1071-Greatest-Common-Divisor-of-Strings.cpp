class Solution {
public:
    string gcdOfStrings(string str1, string str2) {
        // 比赛的时候把这个题想复杂了，而且实现起来也特别笨
        // 自己当时是通过掐出字符串一节一节比，效率低
        // 看了大神答案，可以有高效的方法来判断一个字符串是不是由另一个字符串重复拼接构成
        // 这个值得一学
        
        int n1 = str1.length();
        int n2 = str2.length();
        int g = gcd(n1, n2);
        for ( int i = g; i >= 1; --i ) {
            if( g % i == 0 ) {
                bool flag = true;
                for ( int j = 0; j < n1 && flag; ++j ) {
                    if ( str1[j] != str1[j % g] ) { // 重点:如何判断一个字符串是由一个小串重复出现构成的，这里写的精妙
                        flag = false;
                    }
                }
                for ( int j = 0; j < n2 && flag; ++j ) {
                    if ( str2[j] != str1[j % g] ) {
                        flag = false;
                    }
                }
                if ( flag ) return str1.substr(0, g);
            }
        }
        return "";
    }
    
    int gcd( int x, int y ) {
        return y == 0 ? x : gcd( y, x % y );
    }
};

    
    
    
