#include <bits/stdc++.h>
using namespace std;

/*
    QUEUES IN C++ — ICPC CHEATSHEET
    -------------------------------
    Sections:
      1) std::queue basics (FIFO)
      2) BFS on unweighted graphs
      3) Multi-source BFS
      4) 0–1 BFS (deque) for edge weights in {0,1}
      5) Monotonic queue (sliding window maximum)
      6) priority_queue (max-heap, min-heap, custom compare)
*/

/****************************
 * 1) std::queue — operations
 ****************************/
// Notes:
//   - FIFO: push() at back, pop() removes front
//   - Access: front(), back(), size(), empty()
//   - No iterators; to clear: q = queue<T>();
//   - Prefer emplace(args...) to avoid extra copy
void queue_basics_demo() {
    queue<int> q;
    q.push(10);
    q.emplace(20);
    q.push(30);

    // front -> 10, back -> 30
    while (!q.empty()) {
        int x = q.front();
        // process x ...
        q.pop();
    }
    // Clear explicitly:
    q = queue<int>(); // swap-trick: queue<int>().swap(q);
}

/**************************************
 * 2) BFS (single-source) — O(N + M)
 **************************************/
// Unweighted graph shortest distances (edges weight 1)
vector<int> bfs_single_source(int n, const vector<vector<int>>& adj, int s) {
    const int INF = 1e9;
    vector<int> dist(n, INF);
    queue<int> q;
    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == INF) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

/********************************************
 * 3) Multi-source BFS — push many starts
 ********************************************/
// Example: distance to nearest special node
vector<int> bfs_multi_source(int n, const vector<vector<int>>& adj,
                             const vector<int>& starts) {
    const int INF = 1e9;
    vector<int> dist(n, INF);
    queue<int> q;
    for (int s : starts) {
        dist[s] = 0;
        q.push(s);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == INF) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

/**************************************
 * 3b) BFS path reconstruction (optional)
 **************************************/
vector<int> bfs_path(int n, const vector<vector<int>>& adj, int s, int t) {
    const int INF = 1e9;
    vector<int> dist(n, INF), par(n, -1);
    queue<int> q;
    dist[s] = 0; q.push(s);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == t) break;
        for (int v : adj[u]) if (dist[v] == INF) {
            dist[v] = dist[u] + 1;
            par[v] = u;
            q.push(v);
        }
    }
    vector<int> path;
    if (dist[t] == INF) return path; // empty => unreachable
    for (int v = t; v != -1; v = par[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

/**************************************
 * 4) 0–1 BFS using deque — O(N + M)
 **************************************/
// Graph with edge weights 0 or 1; finds shortest distances
// For each edge u->v with cost c in {0,1}:
//   if c == 0: push_front(v)
//   if c == 1: push_back(v)
vector<int> zero_one_bfs(int n,
                         const vector<vector<pair<int,int>>>& adj, // (to, cost 0/1)
                         int s) {
    const int INF = 1e9;
    vector<int> dist(n, INF);
    deque<int> dq;
    dist[s] = 0;
    dq.push_front(s);

    while (!dq.empty()) {
        int u = dq.front(); dq.pop_front();
        for (auto [v, w] : adj[u]) {
            int nd = dist[u] + w;
            if (nd < dist[v]) {
                dist[v] = nd;
                if (w == 0) dq.push_front(v);
                else        dq.push_back(v);
            }
        }
    }
    return dist;
}

/*****************************************************
 * 5) Monotonic queue — Sliding Window Maximum (O(n))
 *****************************************************/
// Keep indices in decreasing values; front = max in window
vector<int> sliding_window_max(const vector<int>& a, int k) {
    deque<int> dq; // store indices
    vector<int> ans;
    for (int i = 0; i < (int)a.size(); i++) {
        // Pop out-of-window from front
        while (!dq.empty() && dq.front() <= i - k) dq.pop_front();
        // Maintain decreasing deque (values)
        while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
        dq.push_back(i);
        if (i + 1 >= k) ans.push_back(a[dq.front()]);
    }
    return ans;
}

/**************************************************************
 * 6) priority_queue — max-heap (default), min-heap, custom
 **************************************************************/
// Default: max-heap
void pq_max_demo() {
    priority_queue<int> pq;
    pq.push(5); pq.push(1); pq.emplace(10);
    // top: 10
    while (!pq.empty()) {
        int x = pq.top(); pq.pop();
        // process x
    }
}

// Min-heap for ints
void pq_min_demo() {
    priority_queue<int, vector<int>, greater<int>> pq;
    pq.push(5); pq.push(1); pq.emplace(10);
    // top: 1
}

// Custom compare (e.g., pair<dist,node> for Dijkstra-like usage)
struct Node {
    int dist, id;
};
struct Cmp {
    bool operator()(const Node& a, const Node& b) const {
        return a.dist > b.dist; // min-heap by dist
    }
};
void pq_custom_demo() {
    priority_queue<Node, vector<Node>, Cmp> pq;
    pq.push({5, 2});
    pq.push({1, 0});
    pq.emplace(Node{3, 7});
    // top has smallest dist
}

/*********
 * main()
 *********/
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // Use these helpers in real problems; below are simple smoke checks.
    // (Comment out in contest if unnecessary.)

    // 1) queue basics
    // queue_basics_demo();

    // 2) BFS example (build simple graph)
    // int n = 5;
    // vector<vector<int>> adj(n);
    // adj[0] = {1,2}; adj[1] = {0,3}; adj[2] = {0,3}; adj[3] = {1,2,4}; adj[4] = {3};
    // auto d = bfs_single_source(n, adj, 0); // distances from 0

    // 3) Multi-source BFS
    // vector<int> starts = {1,4};
    // auto d2 = bfs_multi_source(n, adj, starts);

    // 4) 0–1 BFS
    // vector<vector<pair<int,int>>> adj01(n);
    // adj01[0].push_back({1,0});
    // adj01[0].push_back({2,1});
    // auto d01 = zero_one_bfs(n, adj01, 0);

    // 5) Sliding window max
    // vector<int> a = {1,3,-1,-3,5,3,6,7};
    // auto win = sliding_window_max(a, 3); // -> {3,3,5,5,6,7}

    // 6) priority_queue demos
    // pq_max_demo();
    // pq_min_demo();
    // pq_custom_demo();

    return 0;
}
