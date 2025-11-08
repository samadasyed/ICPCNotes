//Warning: The contents of this file are AI Generated
#include <bits/stdc++.h>
using namespace std;

/*
    PALINDROME CHEATSHEET
    ---------------------
    Common patterns & functions you can reuse in ICPC problems.
    Each section is self-contained; copy what you need into your solution.
*/

/**************************************
 * 1. BASIC STRING PALINDROME CHECK
 **************************************/

bool isPalindromeString(const string &s) {
    int i = 0, j = (int)s.size() - 1;
    while (i < j) {
        if (s[i] != s[j]) return false;
        i++;
        j--;
    }
    return true;
}

/**************************************
 * 2. BASIC NUMBER PALINDROME CHECK
 *    (without converting to string)
 **************************************/

bool isPalindromeNumber(long long x) {
    if (x < 0) return false; // usually negative numbers are not palindromes
    long long orig = x, rev = 0;
    while (x > 0) {
        int d = x % 10;
        x /= 10;
        // watch for overflow if you care; usually constraints are safe
        rev = rev * 10 + d;
    }
    return rev == orig;
}

/******************************************
 * 3. EXPAND-AROUND-CENTER (CORE TRICK)
 *
 * Handles both:
 *  - odd length palindromes (center at one char)
 *  - even length palindromes (center between two chars)
 ******************************************/

// expand from center [L, R] while s[L] == s[R]
int expandFromCenter(const string &s, int L, int R) {
    int n = (int)s.size();
    while (L >= 0 && R < n && s[L] == s[R]) {
        L--;
        R++;
    }
    // when while breaks, [L+1, R-1] is the last valid palindrome
    return R - L - 1; // length
}

/******************************************
 * 4. LONGEST PALINDROMIC SUBSTRING
 *    O(n^2), easy & safe for many ICPC tasks
 *    Uses expand-around-center for odd+even.
 ******************************************/

string longestPalindromicSubstring(const string &s) {
    int n = (int)s.size();
    if (n == 0) return "";
    int bestLen = 1;
    int bestStart = 0;

    for (int center = 0; center < n; center++) {
        // Odd length: center at (center, center)
        int len1 = expandFromCenter(s, center, center);
        // Even length: center between (center, center+1)
        int len2 = expandFromCenter(s, center, center + 1);

        int len = max(len1, len2);
        if (len > bestLen) {
            bestLen = len;
            // recover start index
            int start = center - (len - 1) / 2;
            bestStart = start;
        }
    }
    return s.substr(bestStart, bestLen);
}

/******************************************
 * 5. COUNT PALINDROMIC SUBSTRINGS
 *    "How many palindromes are in this string?"
 *    Another classic.
 ******************************************/

long long countPalindromicSubstrings(const string &s) {
    int n = (int)s.size();
    long long count = 0;
    for (int center = 0; center < n; center++) {
        // odd length palindromes
        int L = center, R = center;
        while (L >= 0 && R < n && s[L] == s[R]) {
            count++;
            L--;
            R++;
        }
        // even length palindromes
        L = center; R = center + 1;
        while (L >= 0 && R < n && s[L] == s[R]) {
            count++;
            L--;
            R++;
        }
    }
    return count;
}

/******************************************
 * 6. LONGEST PALINDROMIC SUBSEQUENCE (LPS)
 *
 * Subsequence ≠ Substring.
 * You can skip characters.
 * DP: LPS(s) = LCS(s, reverse(s)) idea or direct 2D DP.
 * Complexity: O(n^2).
 ******************************************/

int longestPalindromicSubsequence(const string &s) {
    int n = (int)s.size();
    string t = s;
    reverse(t.begin(), t.end());

    // classic LCS DP between s and reverse(s)
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[i - 1] == t[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][n];
}

/******************************************
 * 7. 2D GRID PALINDROMES (ROW/COL)
 *
 * Pattern for problems like:
 * - Find palindromes in rows & columns
 * - Kattis / ICPC style grid word palindromes.
 *
 * This shows how to:
 *  - scan rows and columns,
 *  - use expand-around-center on each.
 ******************************************/

// Check if substring s[l..r] is palindrome
bool isPal(const string &s, int l, int r) {
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++; r--;
    }
    return true;
}

// Example: max palindrome length in all rows + columns of a char grid
int maxPalindromeInGrid(const vector<string> &g) {
    int n = (int)g.size();
    if (n == 0) return 0;
    int m = (int)g[0].size();
    int best = 1;

    // 1) Rows
    for (int i = 0; i < n; i++) {
        const string &row = g[i];
        // expand-around-center over this row
        for (int center = 0; center < m; center++) {
            // odd
            int L = center, R = center;
            while (L >= 0 && R < m && row[L] == row[R]) {
                best = max(best, R - L + 1);
                L--; R++;
            }
            // even
            L = center; R = center + 1;
            while (L >= 0 && R < m && row[L] == row[R]) {
                best = max(best, R - L + 1);
                L--; R++;
            }
        }
    }

    // 2) Columns
    for (int j = 0; j < m; j++) {
        // build column string
        string col;
        col.reserve(n);
        for (int i = 0; i < n; i++) {
            col.push_back(g[i][j]);
        }
        // expand-around-center on this column
        for (int center = 0; center < n; center++) {
            // odd
            int L = center, R = center;
            while (L >= 0 && R < n && col[L] == col[R]) {
                best = max(best, R - L + 1);
                L--; R++;
            }
            // even
            L = center; R = center + 1;
            while (L >= 0 && R < n && col[L] == col[R]) {
                best = max(best, R - L + 1);
                L--; R++;
            }
        }
    }

    return best;
}

/******************************************
 * 8. EXAMPLE MAIN
 *
 * This is a demo / sandbox, not a fixed judge format.
 * In contest: COPY the functions you need into your solution
 * and adapt input/output to the problem statement.
 ******************************************/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Demo block 1: basic string palindrome
    {
        string s = "racecar";
        cout << "Is \"" << s << "\" a palindrome string? "
             << (isPalindromeString(s) ? "YES" : "NO") << "\n";
    }

    // Demo block 2: longest palindromic substring
    {
        string s = "babad";
        cout << "Longest palindromic substring of \"" << s << "\" is: "
             << longestPalindromicSubstring(s) << "\n";
    }

    // Demo block 3: count palindromic substrings
    {
        string s = "aaa"; // palindromes: "a","a","a","aa","aa","aaa" => 6
        cout << "Count palindromic substrings in \"" << s << "\": "
             << countPalindromicSubstrings(s) << "\n";
    }

    // Demo block 4: longest palindromic subsequence
    {
        string s = "bbbab";
        cout << "Longest palindromic subsequence length in \"" << s << "\": "
             << longestPalindromicSubsequence(s) << "\n";
    }

    // Demo block 5: grid example
    {
        vector<string> g = {
            "APPLE",
            "BOBBY",
            "KAYAK",
            "REBEL"
        };
        cout << "Max palindrome length in grid rows/cols: "
             << maxPalindromeInGrid(g) << "\n";
    }

    // In a real ICPC problem, delete the demo and:
    // - read input according to the statement
    // - call the appropriate functions above
    // - print the required answer.

    return 0;
}
