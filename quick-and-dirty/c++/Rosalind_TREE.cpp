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

int n;
vector < vector<int> > g;
const int INF = INFINITY;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("rosalind_tree.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif
    cin >> n;
    int ans = 0;
    g.reserve(n);
    REP(i, n) g[i].reserve(n);
    REP(i, n)
    {
        int v, to;
        bool b = cin >> v >> to;
        if (b)
        {
            --v; --to; --ans;
            g[v][to] = -1;
            g[to][v] = -1;
        }
    }
    debug(ans);
    vector<bool> used (n);
    vector<int> min_e (n, INF), sel_e (n, -1);
    min_e[0] = 0;
    REP(i, n)
    {
        int v = -1;
        REP(j, n)
        if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
            v = j;
        if (min_e[v] == INF)
        {
            cout << "No MST!";
            exit(0);
        }

        used[v] = true;
        if (sel_e[v] != -1) ++ans;
        //cout << v << " " << sel_e[v] << endl;

        for (int to = 0; to < n; ++to)
            if (g[v][to] < min_e[to])
            {
                min_e[to] = g[v][to];
                sel_e[to] = v;
            }
    }
    debug(ans);
    cout << ans;
    return 0;
}