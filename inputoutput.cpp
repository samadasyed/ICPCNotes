#include <bits/stdc++.h> 
using namespace std; 

typedef long long ll; 


int main () {
    cin.tie(0) -> sync_with_stdio(0); //cin.tie(0) unties cin from cout. 
    //sync_with_stdio decouples C++ iostreams from C stdio and can make I/O faster.
    cin.exceptions(cin.failbit); // throw on format/read failure
    return 0; 


    //Basic input patterns 
    int a; 
    ll x; 
    double d; 
    string s; 

    cin >> a >> x >> d >> s; //reads a word, stops at whitespace 
    //////////////////////////////////////////////////////////////////
    
    //Until EOF
    //Useful when number of test cases isn’t given
    int x;
    while (cin >> x) {
    // process x
    }
    //////////////////////////////////////////////////////////////////
    //Read full line (including spaces)

    string line; 
    getline(cin, line); 
    //////////////////////////////////////////////////////////////////

    //Warning, If you do a cin >> something before getline, there’s a leftover '\n' in the buffer.
    //The fix
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard rest of line
    string line;
    getline(cin, line);
    //////////////////////////////////////////////////////////////////

    //1D Vector
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    //////////////////////////////////////////////////////////////////
    //2D Vector (matrix)
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        cin >> grid[i][j];
        }
    }
    //////////////////////////////////////////////////////////////////
    //2d Char Grid (classic for grids/mazes)
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for (int i = 0; i < n; i++) {
    cin >> g[i];   // each row, no spaces
    }

    //Adjaceny List (Graph)
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1); // 1-based

    for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u); // remove for directed
    }
    //////////////////////////////////////////////////////////////////

    //vector<string> (list of words / names)
    int n;
    cin >> n;
    vector<string> names(n);
    for (int i = 0; i < n; i++) {
    cin >> names[i];
    }
    //////////////////////////////////////////////////////////////////

    //map / unordered_map
    //Count frequencies, etc.
    int n;
    cin >> n;
    unordered_map<int,int> freq;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        freq[x]++;
    }
    //////////////////////////////////////////////////////////////////


    //Simple output 
    cout << x << " " << y << "\n";
    //Precision for doubles
    cout << fixed << setprecision(6) << ans << "\n";
}