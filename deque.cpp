#include <bits/stdc++.h>
using namespace std;

/*
    DEQUE in C++ — ICPC CHEATSHEET
    ------------------------------
    Why deque?
      - O(1) amortized push_front / push_back, pop_front / pop_back
      - Random access: O(1) a[i] (unlike queue)
      - Great for two-ended algorithms (0–1 BFS, monotonic window, etc.)

    Gotchas:
      - Erasing in the middle is O(n); avoid inside tight loops.
      - Iterators can be invalidated by insert/erase (ends usually fine).
*/

/*********************************
 * 1) Basics: operations & idioms
 *********************************/
void deque_basics_demo() {
    deque<int> dq;

    // Push / Pop at both ends
    dq.push_back(2);
    dq.push_front(1);
    dq.emplace_back(3);
    dq.emplace_front(0);

    // Access
    int x = dq.front();  // 0
    int y = dq.back();   // 3
    int z = dq[2];       // random access (here: 2)
    (void)x; (void)y; (void)z;

    // Remove
    dq.pop_front();  // remove 0
    dq.pop_back();   // remove 3

    // Iterate
    for (int v : dq) {
        // process v
    }

    // Clear quickly
    dq = deque<int>(); // or: deque<int>().swap(dq);
}

/********************************************
 * 2) Sliding Window Maximum (O(n)) with deque
 *    (min version = flip comparison)
 ********************************************/
vector<int> sliding_window_max(const vector<int>& a, int k) {
    deque<int> dq; // stores indices
    vector<int> ans;
    for (int i = 0; i < (int)a.size(); i++) {
        while (!dq.empty() && dq.front() <= i - k) dq.pop_front();    // out of window
        while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();    // keep decreasing
        dq.push_back(i);
        if (i + 1 >= k) ans.push_back(a[dq.front()]);
    }
    return ans;
}

vector<int> sliding_window_min(const vector<int>& a, int k) {
    deque<int> dq;
    vector<int> ans;
    for (int i = 0; i < (int)a.size(); i++) {
        while (!dq.empty() && dq.front() <= i - k) dq.pop_front();
        while (!dq.empty() && a[dq.back()] >= a[i]) dq.pop_back();
        dq.push_back(i);
        if (i + 1 >= k) ans.push_back(a[dq.front()]);
    }
    return ans;
}

/**************************************
 * 3) 0–1 BFS (shortest path with 0/1 edges)
 *    Complexity: O(N + M)
 **************************************/
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
            int nd = dist[u] + w; // w in {0,1}
            if (nd < dist[v]) {
                dist[v] = nd;
                if (w == 0) dq.push_front(v);
                else        dq.push_back(v);
            }
        }
    }
    return dist;
}

/********************************************************
 * 4) Two-ended BFS toy (bidirectional flavor scaffold)
 ********************************************************/
bool meet_in_middle_grid(const vector<string>& g, pair<int,int> A, pair<int,int> B) {
    int n = (int)g.size(), m = (int)g[0].size();
    auto inside = [&](int r, int c){ return r>=0 && r<n && c>=0 && c<m && g[r][c] != '#'; };
    vector<vector<int>> va(n, vector<int>(m, -1)), vb(n, vector<int>(m, -1));
    deque<pair<int,int>> qa, qb;
    qa.push_back(A); va[A.first][A.second] = 0;
    qb.push_back(B); vb[B.first][B.second] = 0;
    int dr[4] = {-1,1,0,0}, dc[4] = {0,0,-1,1};

    while (!qa.empty() || !qb.empty()) {
        if (!qa.empty()) {
            auto [r,c] = qa.front(); qa.pop_front();
            if (vb[r][c] != -1) return true; // met
            for (int k=0;k<4;k++){
                int nr=r+dr[k], nc=c+dc[k];
                if (inside(nr,nc) && va[nr][nc]==-1){
                    va[nr][nc]=va[r][c]+1;
                    qa.push_back({nr,nc});
                }
            }
        }
        if (!qb.empty()) {
            auto [r,c] = qb.front(); qb.pop_front();
            if (va[r][c] != -1) return true; // met
            for (int k=0;k<4;k++){
                int nr=r+dr[k], nc=c+dc[k];
                if (inside(nr,nc) && vb[nr][nc]==-1){
                    vb[nr][nc]=vb[r][c]+1;
                    qb.push_back({nr,nc});
                }
            }
        }
    }
    return false;
}

/*****************************************
 * 5) Rolling window sum with push/pop
 *****************************************/
vector<long long> window_sum(const vector<int>& a, int k) {
    deque<int> dq; // store values directly here
    long long cur = 0;
    vector<long long> ans;
    for (int i = 0; i < (int)a.size(); i++) {
        dq.push_back(a[i]);
        cur += a[i];
        if ((int)dq.size() > k) { cur -= dq.front(); dq.pop_front(); }
        if ((int)dq.size() == k) ans.push_back(cur);
    }
    return ans;
}

/*********
 * main()
 *********/
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Uncomment to quick-test locally.

    // // 1) Basics
    // deque_basics_demo();

    // // 2) Sliding window max/min
    // vector<int> v = {1,3,-1,-3,5,3,6,7};
    // auto mx = sliding_window_max(v, 3); // {3,3,5,5,6,7}
    // auto mn = sliding_window_min(v, 3); // {-1,-3,-3,3,3}
    // for (int x : mx) cout << x << ' '; cout << "\n";
    // for (int x : mn) cout << x << ' '; cout << "\n";

    // // 3) 0–1 BFS
    // int n = 5;
    // vector<vector<pair<int,int>>> adj01(n);
    // adj01[0].push_back({1,0});
    // adj01[0].push_back({2,1});
    // auto d01 = zero_one_bfs(n, adj01, 0);

    // // 4) Meet-in-middle toy
    // vector<string> g = {"...",".#.","..."};
    // cout << (meet_in_middle_grid(g, {0,0},{2,2}) ? "MEET\n" : "NO\n");

    // // 5) Rolling sum
    // auto ws = window_sum(v, 3); // {3, -1, 1, 5, 14, 16}
    // for (auto s : ws) cout << s << ' '; cout << "\n";

    return 0;
}
