#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <tr1/unordered_map>
#include <tr1/unordered_set>

using namespace std;
using namespace tr1;

#define LL long long
#define pb push_back
#define mp make_pair
#define hashmap unordered_map
#define hashset unordered_set
#define contains(hs, key) ((hs).find((key))!=(hs).end())
#define REP(i,n) for(int (i)=0;(i)<(int)(n);(i)++)
#define REP2(i,j,n) for(int (i)=(j);(i)<(int)(n);(i)++)
#define REPD(i,j,n) for(int (i)=(j);(i)>=(int)(n);(i)--)
#define REPC(i,j,expr) for(int (i)=(j);expr;(i)++)
#define foreach(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)
#define ALL(lst) (lst).begin(), (lst).end()
#define inbounds(i,j,a,b) ((i)>=(a)&(i)<=(b)&(j)>=(a)&(j)<=(b))
#define bitcount(n) __builtin_popcount(n)
#define debug(x) { if(DEBUG) cerr << #x << " = " << x << endl; }
#define debugv(x) { if (DEBUG) cerr << #x << " = "; foreach((x), it) cerr << *it << ", "; cerr << endl; }

const double PI = 3.1415926535897932384626433832795;

#define DEBUG 0

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
    int n = (int) s.length();

    const int p = 31;
    vector<LL> p_pow (s.length());
    p_pow[0] = 1;
    for (size_t i = 1; i < p_pow.size(); ++i)
        p_pow[i] = p_pow[i - 1] * p;

    vector<LL> h (s.length());
    for (size_t i = 0; i < s.length(); ++i)
    {
        h[i] = (s[i] - 'a' + 1) * p_pow[i];
        if (i)  h[i] += h[i - 1];
    }

    LL result = 0;

    for (int l = 1; l <= n; ++l)
    {
        vector<LL> hs (n - l + 1);
        for (int i = 0; i < n - l + 1; ++i)
        {
            LL cur_h = h[i + l - 1];
            if (i)  cur_h -= h[i - 1];
            cur_h *= p_pow[n - i - 1];
            hs[i] = cur_h;
        }

        sort (hs.begin(), hs.end());
        hs.erase (unique (hs.begin(), hs.end()), hs.end());
        result += (int) hs.size();
        //vector<LL>().swap(h);
        if (l % 1000 == 0) cerr << l << " Done. \n";
    }

    return result;
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