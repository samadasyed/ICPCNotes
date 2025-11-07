#include <bits/stdc++.h> 
using namespace std; 

typedef long long ll; 


int main () {
    cin.tie(0) -> sync_with_stdio(0); //cin.tie(0) unties cin from cout. 
    //sync_with_stdio decouples C++ iostreams from C stdio and can make I/O faster.
    cin.exceptions(cin.failbit); // throw on format/read failure
    return 0; 


    //Basic input patterns 
    //////////////////////////////////////////////////////////////////
    int a; 
    ll x; 
    double d; 
    string s; 

    cin >> a >> x >> d >> s; //reads a word, stops at whitespace 

    
    //Until EOF
    //Useful when number of test cases isn’t given
    //////////////////////////////////////////////////////////////////
    int x;
    while (cin >> x) {
    // process x
}

    //Read full line (including spaces)
    //////////////////////////////////////////////////////////////////
    string line; 
    getline(cin, line); 
}