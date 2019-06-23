// 767 和 1045 本质上是一道题

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

// 第二种写法O(n)，对26个字母按照出现的频次排序，抄群里的答案
class Solution {
public:
    string reorganizeString(string S) {
        
        int counter[26];
        for ( int i = 0; i < 26; ++i ) counter[i] = i;
        
        int n = S.length();
        for ( int i = 0; i < n; ++i ) {
            // 这个地方写的精妙
            counter[S[i]-'a'] += 100;
        }
        sort( counter, counter + 26, [](int a, int b) {
            return a > b;
        });
        string res(n, '*');
        int pt = 0;
        for ( int i = 0; i < 26; ++i ) {
            int num = counter[i] / 100;
            char c = (char) ( 'a' + counter[i] % 100 );
            for ( int j = 0; j < num; ++j ) {
                res[pt] = c;
                pt += 2;
                if ( pt >= n ) pt = 1;
            }
        }        
        for ( int i = 1; i < n; ++i ) {
            if ( res[i] == res[i-1] ) return "";
        }
        return res;
    }
};

// 1045同样的套路
class Solution {
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        unordered_map<int, int> umap;
        int n = barcodes.size();
        for (auto& x : barcodes ) ++umap[x];
        priority_queue<pair<int, int>> pq;
        for ( auto it = umap.begin(); it != umap.end(); ++it ) {
            pq.push( make_pair( it -> second, it -> first ) );
        }
        vector<int> res(n);
        int pt = 0;
        for ( int i = 0; i < pq.size(); ) {
            pair<int, int> cur = pq.top();
            pq.pop();
            for ( int j = 0; j < cur.first; ++j ) {
                res[pt] = cur.second;
                pt += 2;
                if ( pt >= n ) pt = 1;
            }
        }
        return res;
    }
};



