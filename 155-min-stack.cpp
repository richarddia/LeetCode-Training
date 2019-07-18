// 总算把这个解法看懂了
// 小心溢出，警钟长鸣

class MinStack {
    stack<long> st;
    long mn;
public:
    /** initialize your data structure here. */
    MinStack() : mn{INT_MAX}{
        
    }
    
    void push(int x) {
        st.push((long)x - mn);
        mn = min(mn, (long)x);
    }
    
    void pop() {
        if ( st.top() > 0 ) {
            // 目的是求last_min
            // 当前的min就是last_min
            st.pop();
        } else {
            // x <= last_min
            // 此时 st.top() == x - last_min
            // 而且 x == mn
            // 所以 st.top() == mn - last_min
            mn -= st.top();
            st.pop();
        }
    }
    
    int top() {
        if ( st.top() > 0 ) {
            // x - last_mn > 0 推出 x > last_min
            // 说明当前的min就是last_min
            // 此时 st.top() == x - mn
            return st.top() + mn;
        } else {
            // x <= last_min
            // 说明当前的min就是x
            return mn;
        }
    }
    
    int getMin() {
        return mn;
    }
};
