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
#define DEBUG 1
#define debug(x) { if(DEBUG) cerr << #x << " = " << x << endl; }
#define debugv(x) { if (DEBUG) cerr << #x << " = "; foreach((x), it) cerr << *it << ", "; cout << endl; }

const double PI = 3.1415926535897932384626433832795;

const char GAP = '-';

vector<int> pp;

template <class T> unsigned int edit_distance(const T &s1, const T &s2)
{
    const size_t len1 = s1.size(), len2 = s2.size();
    vector<vector<unsigned int> > d(len1 + 1, vector<unsigned int>(len2 + 1));
    vector<vector<unsigned int> > p(len1 + 1, vector<unsigned int>(len2 + 1));

    d[0][0] = 0;
    for (unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
    for (unsigned int i = 1; i <= len2; ++i) d[0][i] = i;

    for (unsigned int i = 1; i <= len1; ++i)
        for (unsigned int j = 1; j <= len2; ++j)
        {
            d[i][j] = min( min(d[i - 1][j] + 1, d[i][j - 1] + 1),
                           d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) );
            if (d[i][j] == d[i - 1][j] + 1)
                p[i][j] = 1;
            else if (d[i][j] == d[i][j - 1] + 1)
                p[i][j] = -1;
            else
                p[i][j] = 0;
        }
    int x = len1, y = len2;
    while ((x != 0) | (y != 0))
    {
        pp.push_back(p[x][y]);
        if (p[x][y] == 1) --x;
        else if (p[x][y] == -1) --y;
        else
        {
            --x; --y;
        }
    }
    reverse(ALL(pp));
    return d[len1][len2];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("rosalind_edta.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif
    string s, t;
    cin >> s >> t;
    cout << edit_distance(s, t) << endl;
    char s1[pp.size()], s2[pp.size()];
    int cur1 = 0, cur2 = 0;
    REP(i, pp.size()) switch (pp[i])
    {
    case 1: s1[i] = s[cur1]; s2[i] = GAP; ++cur1; break;
    case -1: s1[i] = GAP; s2[i] = t[cur2]; ++cur2; break;
    default: s1[i] = s[cur1]; s2[i] = t[cur2]; ++cur1; ++cur2; break;
    }
    REP(i, pp.size()) cout << s1[i]; cout << endl;
    REP(i, pp.size()) cout << s2[i];
    return 0;
}