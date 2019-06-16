vector<int> arr1;
vector<int> arr2;
struct mycomparison {
    bool operator() (const pair<int, int>& lhs, const pair<int, int>& rhs) {
        // c++ pq默认是max heap，这里我们要用min heap，比较关系变成大于，奇葩！
        return arr1[lhs.first] + arr2[lhs.second] > arr1[rhs.first] + arr2[rhs.second];    
    }
};

class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        //这个题以前做过但是总是忘记，要用heap，忘记怎么移动指针了
        //nums1和nums2是排序好了的，所以最小的组合一定是[nums1[0], nums2[0]]，然后指针该怎么移动呢
        //字迹在纸上画了一下[1 7 11] [2 4 6]的情况，感觉要用两对指针而不是两个指针
        //两个指针摆弄了一下发现也不行，那就n个指针算了
        arr1 = nums1;
        arr2 = nums2;
        int n = nums1.size();
        vector<vector<int>> res;
        if ( nums1.empty() || nums2.empty() ) return res;
        priority_queue<pair<int, int>, vector<pair<int, int>>,  mycomparison> queue;      
        vector<int> ptrs ( n, 0 );
        for ( int i = 0; i < n; ++ i ) queue.push( make_pair( i, 0 ) );
        while ( k > 0 && !queue.empty() ) {
            pair<int, int> cur = queue.top();
            queue.pop();
            res.push_back( vector<int> { nums1[cur.first], nums2[cur.second] } );
            --k;
            if ( ++cur.second < nums2.size() ) {
                queue.push( cur );
            }
        }
        return res;
    }
};


//第二版代码
class Solution {
private:
    struct Tuple {
        int pt1;
        int pt2;
        int sum;
        Tuple( int pt1, int pt2, int sum ) : pt1{pt1}, pt2{pt2}, sum{sum} {
            
        };
    };
    
    struct myComp {
        bool operator() ( const Tuple& lhs, const Tuple& rhs ) {
            return lhs.sum > rhs.sum;
        }
    };
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        //上一版代码写的有够奇葩，还动用的全局变量
        //看了别人代码，做一些修改和完善，顺便练习一下c++里使用内部类
        int n = nums1.size();
        vector<vector<int>> res;
        if ( nums1.empty() || nums2.empty() ) return res;
        priority_queue<Tuple, vector<Tuple>,  myComp> queue;      
        vector<int> ptrs ( n, 0 );
        for ( int i = 0; i < n; ++ i ) queue.push( Tuple( i, 0, nums1[i] + nums2[0] ) );
        while ( k > 0 && !queue.empty() ) {
            Tuple cur = queue.top();
            queue.pop();
            res.push_back( vector<int> { nums1[cur.pt1], nums2[cur.pt2] } );
            --k;
            if ( ++cur.pt2 < nums2.size() ) {
                cur.sum = nums1[cur.pt1] + nums2[cur.pt2];
                queue.push( cur );
            }
        }
        return res;
    }
};

