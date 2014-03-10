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
const int MAXN = 200;

char aa[] = {'A',
             'C',
             'D',
             'E',
             'F',
             'G',
             'H',
             'I',
             'K',
             'L',
             'M',
             'N',
             'P',
             'Q',
             'R',
             'S',
             'T',
             'V',
             'W',
             'Y'
            };

double mass[] = {71.03711,
                 103.00919,
                 115.02694,
                 129.04259,
                 147.06841,
                 57.02146,
                 137.05891,
                 113.08406,
                 128.09496,
                 113.08406,
                 131.04049,
                 114.04293,
                 97.05276,
                 128.05858,
                 156.10111,
                 87.03203,
                 101.04768,
                 99.06841,
                 186.07931,
                 163.06333
                };

map<double, char> mass_table;
int n, target;
char graph[MAXN][MAXN];
int p[MAXN];
vector<double> ions;
vector<char> ans;

bool dfs(int v, vector<char> cur)
{
    if (cur.size() > ans.size())
    {
        ans = cur;
    }
    bool ans = false;
    REP2(to, v + 1, n) if (graph[v][to] != '-')
    {
        p[to] = v;
        vector<char> cur2(ALL(cur));
        ans = (ans || dfs(to, cur2));
    }
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("rosalind_full.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif
    REP(i, 20) mass_table[floor(mass[i] * 100) / 100] = aa[i];
    double total;
    cin >> total;
    double ion;
    while (cin >> ion) ions.push_back(ion);
    n = ions.size();
    target = (ions.size() - 2) / 2;
    debug(target);
    fill_n(p, MAXN, -1);
    REP(i, MAXN) REP(j, MAXN) graph[i][j] = '-';
    REP(i, n) REP2(j, i + 1, n) if (contains(mass_table, floor((ions[j] - ions[i]) * 100) / 100))
        graph[i][j] = mass_table[floor((ions[j] - ions[i]) * 100) / 100];
        vector<char> v;
    REP(i, n) if (dfs(i, v))
    {
        foreach(ans, itr) cout << *itr;
        break;
    }
    return 0;
}