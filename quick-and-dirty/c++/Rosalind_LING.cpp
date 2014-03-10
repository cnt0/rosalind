#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

using namespace std;

#define LL long long

char alphabet[] = {'A', 'T', 'G', 'C'};
int get(char c)
{
    switch (c)
    {
        case 'A': return 0;
        case 'T': return 1;
        case 'G': return 2;
        default: return 3;
    }
}

LL C (LL n, LL k)
{
    double res = 1;
    for (LL i = 1; i <= k; ++i)
        res = res * (n - k + i) / i;
    return (LL) (res + 0.01);
}

LL maximum_number_of_substrings(LL d, LL n)
{
    LL k = (LL)(log(n) / log(d));
    return ((LL)pow(d, k + 1) - 1) / (d - 1) + C(n - k + 1, 2) - 1LL;
}


LL number_of_distinct_substrings(string s)
{
    LL n = s.size();
    s = s + ' ';
    vector< vector<LL> > a(4);
    LL ans = 0;
    for (LL i = n - 1; i >= 0; --i)
    {
        LL lev = 0;
        for (LL st = (LL)a[get(s[i])].size() - 1; st >= 0; --st)
        {
            LL j = a[get(s[i])][st];
            if (n - j <= lev) break;
            if (s[j + lev] != s[i + lev]) continue;
            if (s[j + lev / 2] != s[i + lev / 2]) continue;
            LL k = 0;
            while (s[j + k] == s[i + k]) ++k;
            if (k > lev) lev = k;
        }
        a[get(s[i])].push_back(i);
        ans += n - i - lev;
    }
    return ans;
}


int main()
{
    freopen("rosalind_ling.txt", "rt", stdin);
    freopen("output.txt", "w", stdout);
    string s;
    cin >> s;
    LL h = number_of_distinct_substrings(s);
    LL t = maximum_number_of_substrings(4, s.length());
    double ans = (double)h / t;
    printf("%.4f\n", ans);
    return 0;
}