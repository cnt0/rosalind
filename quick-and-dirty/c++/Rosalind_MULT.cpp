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

const int INF = INFINITY;

int score(char c1, char c2, char c3, char c4)
{
    int ans = 0;
    ans += c1 != c2 ? 1 : 0;
    ans += c1 != c3 ? 1 : 0;
    ans += c1 != c4 ? 1 : 0;
    ans += c2 != c3 ? 1 : 0;
    ans += c2 != c4 ? 1 : 0;
    ans += c3 != c4 ? 1 : 0;
    return ans;
}

int *getstate(int mask)
{
    int *ans = new int[4];
    REP(i, 4) ans[i] = (mask >> i) & 1;
    return ans;
}

vector<int> pp;

template <class T> int edit_distance(const T &s1, const T &s2, const T &s3, const T &s4)
{
    const size_t len1 = s1.length(),
                 len2 = s2.length(),
                 len3 = s3.length(),
                 len4 = s4.length();
    bool fst = true;
    int d[len1 + 1][len2 + 1][len3 + 1][len4 + 1];
    int p[len1 + 1][len2 + 1][len3 + 1][len4 + 1];
    REP(i, len1 + 1) REP(j, len2 + 1) REP(k, len3 + 1) REP(l, len4 + 1)
    {
        int cur = INFINITY, bestmask, *state;
        REP(mask, (1 << 4) - 1)
        {
            state = getstate(mask);
            int newcur = INFINITY;
            if ((i + state[0] - 1 >= 0) &&
                (j + state[1] - 1 >= 0) &&
                (k + state[2] - 1 >= 0) &&
                (l + state[3] - 1 >= 0))
            {
                int prevd = d[i + state[0] - 1]
                             [j + state[1] - 1]
                             [k + state[2] - 1]
                             [l + state[3] - 1];
                newcur = prevd;
                if (newcur != INF)
                    newcur += score(state[0] == 0 ? s1[i - 1] : GAP,
                                    state[1] == 0 ? s2[j - 1] : GAP,
                                    state[2] == 0 ? s3[k - 1] : GAP,
                                    state[3] == 0 ? s4[l - 1] : GAP);
            }
            delete state;
            if (cur > newcur)
            {
                cur = newcur;
                bestmask = mask;
            }
        }
        d[i][j][k][l] = fst ? 0 : cur;
        p[i][j][k][l] = bestmask;
        fst = false;
    }
    int x1 = len1, x2 = len2, x3 = len3, x4 = len4;
    while ((x1 != 0) || (x2 != 0) || (x3 != 0) || (x4 != 0))
    {
        pp.push_back(p[x1][x2][x3][x4]);
        int *state = getstate(p[x1][x2][x3][x4]);
        if (state[0] == 0) --x1;
        if (state[1] == 0) --x2;
        if (state[2] == 0) --x3;
        if (state[3] == 0) --x4;
        delete state;
    }
    reverse(ALL(pp));
    return d[len1][len2][len3][len4];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("rosalind_mult.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif
    string p, q, s, t;
    cin >> p >> q >> s >> t;
    //debug(t);
    debug(edit_distance(p, q, s, t));
    cout << '-' << edit_distance(p, q, s, t) << endl;
    string s1(pp.size(), 'A'), s2(pp.size(), 'A'), s3(pp.size(), 'A'), s4(pp.size(), 'A');
    int cur1 = 0, cur2 = 0, cur3 = 0, cur4 = 0;
    REP(i, pp.size())
    {
        int *state = getstate(pp[i]);
        if (state[0] == 0)
        {
            if (cur1 < p.length()) s1[i] = p[cur1];
            ++cur1;
        }
        else s1[i] = GAP;
        if (state[1] == 0)
        {
            if (cur2 < q.length()) s2[i] = q[cur2];
            ++cur2;
        }
        else s2[i] = GAP;
        if (state[2] == 0)
        {
            if (cur3 < s.length())s3[i] = s[cur3];
            ++cur3;
        }
        else s3[i] = GAP;
        if (state[3] == 0)
        {
            if (cur4 < t.length())s4[i] = t[cur4];
            ++cur4;
        }
        else s4[i] = GAP;
    }
    cerr << '\n';
    debugv(pp);
    debug(edit_distance(p, q, s, t));
    debug(s1);
    debug(s2);
    debug(s3);
    debug(s4);
    cout << s1 << endl << s2 << endl << s3 << endl << s4;
    return 0;
}