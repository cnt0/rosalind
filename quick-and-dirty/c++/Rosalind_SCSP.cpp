#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string LCS(string s1, string s2)
{
    int n = s1.length() + 1;
    int m = s2.length() + 1;
    vector<vector<int>> len(n, vector<int>(m, 0)),
           p(n, vector<int>(m, 0));
    for (int i = 1; i < n; ++i)
        for (int j = 1; j < m; ++j)
            if (s1[i - 1] == s2[j - 1])
                len[i][j] = len[i - 1][j - 1] + 1;
            else if (len[i - 1][j] > len[i][j - 1])
            {
                len[i][j] = len[i - 1][j];
                p[i][j] = 1;
            }
            else
            {
                len[i][j] = len[i][j - 1];
                p[i][j] = 2;
            }
    vector<char> ans;
    int i = n - 1, j = m - 1;
    while (i > 0 && j > 0)
        switch (p[i][j])
        {
        case 0: if (s1[i - 1] == s2[j - 1])
            { ans.push_back(s1[i - 1]); --i; --j; break; }
            else
            {
                reverse(ans.begin(), ans.end());
                return string(ans.begin(), ans.end());
            }
        case 1: --i; break;
        default: --j; break;
        }
    reverse(ans.begin(), ans.end());
    return string(ans.begin(), ans.end());
}

string SCS(string s1, string s2)
{
    string lcs = LCS(s1, s2);
    vector<char> ans;
    int cur1 = 0, cur2 = 0;
    for (int cur = 0; cur < lcs.length(); ++cur)
    {
        while ((cur1 < s1.length()) && (s1[cur1] != lcs[cur])) ans.push_back(s1[cur1++]);
        while ((cur2 < s2.length()) && (s2[cur2] != lcs[cur])) ans.push_back(s2[cur2++]);
        ans.push_back(lcs[cur]);
        ++cur1; ++cur2;
    }
    while (cur1 < s1.length()) ans.push_back(s1[cur1++]);
    while (cur2 < s2.length()) ans.push_back(s2[cur2++]);
    return string(ans.begin(), ans.end());
}

int main()
{
    freopen("rosalind_scsp.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(0);
    string s1, s2;
    cin >> s1 >> s2;
    cout << SCS(s1, s2) << '\n';
    return 0;
}