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

map<string, string> kmers;

string rc(string s)
{
    string ans(s.length(), 'A');
    REP(i, s.length()) switch (s[s.length() - 1 - i])
    {
    case 'A': ans[i] = 'T'; break;
    case 'T': ans[i] = 'A'; break;
    case 'G': ans[i] = 'C'; break;
    default: ans[i] = 'G'; break;
    }
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("rosalind_pcov.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif
    string s, first = "";
    int l = 0;
    while (cin >> s)
    {
        if (first == "") first = s;
        if (l == 0) l = s.length();
        kmers[s.substr(0, l - 1)] = s.substr(1, l - 1);
        s = rc(s);
        kmers[s.substr(0, l - 1)] = s.substr(1, l - 1);
    }
    string cur = first.substr(0, l - 1);
    string ans = first;
    cur = kmers[cur];
    while (cur != first.substr(0, l - 1))
    {
        debug(cur);
        ans += kmers[cur].substr(l - 2, 1);
        cur = kmers[cur];
    }
    cout << ans.substr(0, ans.length() - l + 1);
    return 0;
}