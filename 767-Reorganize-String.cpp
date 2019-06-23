class Solution {
public:
    string reorganizeString(string S) {
        // 第一遍写错了，心态崩了
        // 错误思路: 数一下每个字母出现的次数，比如出现次数最多的那个字母出现了k次，
        // 然后我居然弄了一个2*k - 1的数组存放这k个字母，两两之间空一个，然后我尝试用剩下的n-k个
        // 去填充那k-1个空缺，如果填不满，那肯定做不成，假如能填满，这会儿手上有两个string
        // 一个长为2*k - 1 另一个是n - ( 2*k - 1 )，然后我尝试去merge这两个string，失败，一开始我
        // 想当然以为2*k - 1要长一些，后面发现到底哪个长真不一定，所以就没办法merge下去了
        // 正确思路是开一个长度为n的string，按照出现的频次，从高到低，依次写入string，
        // 最后再验一遍
        
        int counter[26] = { 0 };
        int n = S.length();
        for ( int i = 0; i < n; ++i ) {
            counter[S[i]-'a']++;
        }
        sort( S.begin(), S.end(), [&]( char& a, char& b  ) {
            if ( counter[a-'a'] != counter[b-'a'] )  return counter[a-'a'] > counter[b-'a'];
            else return a < b;
        });
        string res(n, '*');
        int pt = 0;
        for ( int i = 0; i < n; i += 2 ) {
            res[i] = S[pt++];
        }
        
        for ( int i = 1; i < n; i += 2 ) {
            res[i] = S[pt++];
        }
        
        for ( int i = 1; i < n; ++i ) {
            if ( res[i] == res[i-1] ) return "";
        }
        return res;
    }
};