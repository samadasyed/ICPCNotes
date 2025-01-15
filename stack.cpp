#include <bits/stdc++.h>
using namespace std;

/*
    STACK in C++ — ICPC CHEATSHEET
    ------------------------------
    std::stack<T> (container adapter over deque<T> by default)
      - s.push(x), s.emplace(args...), s.pop(), s.top(), s.size(), s.empty()
      - LIFO (last-in, first-out)
      - No iterators; to clear: s = stack<T>();

    Tip: For monotonic-stack patterns you usually use a raw vector<int> as an index stack.
*/

/***********************
 * 0) Fast I/O template
 ***********************/
static inline void fastio() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

/*********************************
 * 1) Basics: operations & idioms
 *********************************/
void stack_basics_demo() {
    stack<int> st;
    st.push(10);
    st.emplace(20);
    st.push(30);
    // top -> 30
    while (!st.empty()) {
        int x = st.top();
        // process x ...
        st.pop();
    }
    // clear:
    st = stack<int>();
}

/***********************************************
 * 2) Parentheses / Brackets validation (O(n))
 ***********************************************/
bool valid_brackets(const string& s) {
    stack<char> st;
    auto match = [](char a, char b){
        return (a=='('&&b==')')||(a=='['&&b==']')||(a=='{'&&b=='}');
    };
    for (char c : s) {
        if (c=='('||c=='['||c=='{') st.push(c);
        else if (c==')'||c==']'||c=='}') {
            if (st.empty() || !match(st.top(), c)) return false;
            st.pop();
        }
    }
    return st.empty();
}

/***********************************
 * 3) Evaluate Reverse Polish Notation
 *    tokens like: ["2","1","+","3","*"] -> 9
 ***********************************/
int evalRPN(const vector<string>& tokens) {
    stack<long long> st;
    for (auto &t : tokens) {
        if (t=="+"||t=="-"||t=="*"||t=="/") {
            long long b = st.top(); st.pop();
            long long a = st.top(); st.pop();
            if (t=="+") st.push(a+b);
            else if (t=="-") st.push(a-b);
            else if (t=="*") st.push(a*b);
            else st.push(a/b); // trunc toward 0 like LeetCode
        } else {
            st.push(stoll(t));
        }
    }
    return (int)st.top();
}

/***********************************
 * 4) Iterative DFS using stack
 ***********************************/
vector<int> dfs_iter(int n, const vector<vector<int>>& adj, int src) {
    vector<int> order;
    vector<char> vis(n, 0);
    stack<int> st;
    st.push(src);
    while (!st.empty()) {
        int u = st.top(); st.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        order.push_back(u);
        // push neighbors (optionally reverse to mimic recursive order)
        for (int v : adj[u]) if (!vis[v]) st.push(v);
    }
    return order;
}

/*********************************************************
 * 5) Monotonic Stack: Next Greater Element to the right
 *    return idx of next greater for each i, or -1 if none
 *********************************************************/
vector<int> next_greater_right(const vector<int>& a) {
    int n = (int)a.size();
    vector<int> res(n, -1);
    vector<int> st; // stack of indices with decreasing values
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.back()] < a[i]) {
            res[st.back()] = i;
            st.pop_back();
        }
        st.push_back(i);
    }
    return res;
}

/*********************************************************
 * 6) Monotonic Stack: Next Smaller Element to the left
 *********************************************************/
vector<int> next_smaller_left(const vector<int>& a) {
    int n = (int)a.size();
    vector<int> res(n, -1);
    vector<int> st; // increasing stack of indices
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.back()] > a[i]) st.pop_back();
        res[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }
    return res;
}

/***********************************************
 * 7) Stock Span: days with consecutive <= current
 *    res[i] = length of span ending at i
 ***********************************************/
vector<int> stock_span(const vector<int>& price) {
    int n = (int)price.size();
    vector<int> span(n);
    vector<int> st; // stack of indices with strictly greater prices
    for (int i = 0; i < n; i++) {
        while (!st.empty() && price[st.back()] <= price[i]) st.pop_back();
        span[i] = st.empty() ? i + 1 : i - st.back();
        st.push_back(i);
    }
    return span;
}

/*************************************************************
 * 8) Largest Rectangle in Histogram (classic, O(n))
 *************************************************************/
long long largest_rectangle_histogram(const vector<int>& h) {
    int n = (int)h.size();
    vector<int> st; // increasing heights stack (indices)
    long long best = 0;
    for (int i = 0; i <= n; i++) {
        int cur = (i == n ? 0 : h[i]);
        while (!st.empty() && h[st.back()] > cur) {
            int height = h[st.back()]; st.pop_back();
            int left = st.empty() ? 0 : st.back() + 1;
            int right = i - 1;
            long long area = 1LL * height * (right - left + 1);
            best = max(best, area);
        }
        st.push_back(i);
    }
    return best;
}

/******************************************************
 * 9) Min-Stack (track current minimum in O(1))
 ******************************************************/
struct MinStack {
    stack<long long> st, mn;
    void push(long long x) {
        st.push(x);
        if (mn.empty()) mn.push(x);
        else mn.push(std::min(x, mn.top()));
    }
    void pop() { st.pop(); mn.pop(); }
    long long top() const { return st.top(); }
    long long getMin() const { return mn.top(); }
    bool empty() const { return st.empty(); }
    int size() const { return (int)st.size(); }
};

/*********
 * main()
 *********/
int main() {
    fastio();

    // Uncomment to quick-test locally.

    // // 2) Brackets
    // cout << (valid_brackets("([]){}") ? "OK\n" : "BAD\n");

    // // 3) RPN
    // vector<string> tok = {"2","1","+","3","*"}; // -> 9
    // cout << evalRPN(tok) << "\n";

    // // 4) DFS iter
    // int n = 5;
    // vector<vector<int>> adj(n);
    // adj[0]={1,2}; adj[1]={0,3}; adj[2]={0,3}; adj[3]={1,2,4}; adj[4]={3};
    // auto ord = dfs_iter(n, adj, 0);
    // for (int v: ord) cout << v << ' '; cout << "\n";

    // // 5) Next Greater Right
    // vector<int> a = {2,1,2,4,3};
    // auto ngr = next_greater_right(a); // -> {3,2,3,-1,-1} (indices)
    // for (int i=0;i<(int)ngr.size();i++) cout << ngr[i] << ' '; cout << "\n";

    // // 7) Stock span
    // vector<int> p = {100,80,60,70,60,75,85};
    // auto sp = stock_span(p); // -> {1,1,1,2,1,4,6}
    // for (int x: sp) cout << x << ' '; cout << "\n";

    // // 8) Largest rectangle
    // vector<int> h = {2,1,5,6,2,3}; // -> 10
    // cout << largest_rectangle_histogram(h) << "\n";

    // // 9) MinStack
    // MinStack ms; ms.push(3); ms.push(5); ms.push(2); ms.push(2); ms.push(4);
    // cout << ms.getMin() << "\n"; // 2
    // ms.pop(); ms.pop();
    // cout << ms.getMin() << "\n"; // 2

    return 0;
}
