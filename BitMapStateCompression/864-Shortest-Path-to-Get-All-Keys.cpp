// 写这道题时候踩了好多的坑
// 一个判断条件 0 == ( s & ( 1 << ( grid[nx][ny] - 'A' ) ) ) 少了一对括号写成 0 ==  s & ( 1 << ( grid[nx][ny] - 'A' ) ) 被系统误判
// 位运算和等号的优先级要注意，反正记不住，多加一层括号总没错
// if 判断里=和==又弄错了，以后还是把常量写在前面把 '@' == grid[i][j]
// 847也是一道这种bit来进行状态压缩的题目

const int dir[] = { 1, 0, -1, 0, 1 };
struct Node {
    int x, y, s;
    Node( int x, int y, int s ) : x{x}, y{y}, s{s} {}
};

class Solution {
public:
    int shortestPathAllKeys(vector<string>& grid) {
        int n = grid.size(), m = grid[0].size();
        int starti, startj;
        int keyCnt = 0;
        for ( int i = 0; i < n; ++i ) {
            for ( int j = 0; j < m; ++j ) {
                if ( grid[i][j] == '@' ) {
                    starti = i;
                    startj = j;
                } else if ( islower(grid[i][j]) != 0 ) {
                    keyCnt++;
                } 
            }
        }
        int K = 1 << keyCnt;
        bool state[n][m][K];
        memset(state, 0, sizeof(state));
        queue<Node> q;
        q.push( Node( starti, startj, 0) );
        state[starti][startj][0] = true;
        int res = 0;
        
        while ( !q.empty() ) {
            int sz = q.size();
            for ( int i = 0; i < sz; ++i ) {
                int x = q.front().x;
                int y = q.front().y;
                int s = q.front().s;
                q.pop();
                if ( s == K - 1 ) {
                    return res;
                }

                for ( int i = 0; i < 4; ++i ) {
                    int nx = x + dir[i], ny = y + dir[i+1];
                    if ( nx < 0 || nx >= n || ny < 0 || ny >= m || grid[nx][ny] == '#' ) continue;
                    if ( isupper(grid[nx][ny]) ) { // ran into a door, but no key to open it
                        if ( 0 == ( s & ( 1 << ( grid[nx][ny] - 'A' ) ) ) ) continue;    
                    }
                    int ns = s;
                    if ( islower(grid[nx][ny]) ) {
                        ns = s | ( 1 << ( grid[nx][ny] - 'a' ) );    
                    } 
                    if ( !state[nx][ny][ns] ) {
                        q.push(Node(nx, ny, ns));
                        state[nx][ny][ns] = true;
                    }
                }
            }
            ++res;
        }
        return -1;
    }
};