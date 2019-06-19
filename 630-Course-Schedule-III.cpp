// 贪婪算法，不容易想到，难点在用要用priority_queue来筛选。
// 错了4次，终于试出来一个对的答案
class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        sort( courses.begin(), courses.end(), []( vector<int>& lhs, vector<int>& rhs ) {
            return lhs[1] < rhs[1];
        });
        priority_queue<int> pq;
        int time = 0;
        int res = 0;
        for ( auto& c : courses ) {
            if ( c[0] + time <= c[1] ) {
                time += c[0];
                pq.push( c[0] );
                ++res;
            } else {
                if ( !pq.empty() && c[0] <= pq.top() ) {
                    time += c[0] - pq.top();
                    pq.pop();
                    pq.push( c[0] );
                }
            }
        }
        return res;
    }
};

// 改进了一下代码，比上一版本好一点，改进的片段里也借助了一点贪婪算法
class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        sort( courses.begin(), courses.end(), []( vector<int>& lhs, vector<int>& rhs ) {
            return lhs[1] < rhs[1];
        });
        priority_queue<int> pq;
        int time = 0;
        int res = 0;
        for ( auto& c : courses ) {
            pq.push( c[0] );
            time += c[0];
            ++res;
            if ( time > c[1] ) {
                time -= pq.top();
                pq.pop();
                --res;
            }
        }
        return res;
    }
};