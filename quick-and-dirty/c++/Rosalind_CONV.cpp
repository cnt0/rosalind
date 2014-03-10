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

pair<int, LL> spectral_convolution(vector<LL> set1, vector<LL> set2)
{
    map<LL, int> dif;
    foreach(set1, itr1) foreach(set2, itr2)
    {
        LL key = fabs(*itr1 - *itr2);
        if (contains(dif, key)) ++dif[key];
        else dif[key] = 1;
    }
    LL key = -1;
    int cnt = 0;
    foreach(dif, itr)
    {
        if (itr->second > cnt)
        {
            key = itr->first;
            cnt = itr->second;
        }
    }
    return make_pair(cnt, key);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("rosalind_conv.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif
    vector<LL> set1, set2;
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);
    stringstream s;
    s << s1;
    double cur;
    while (s >> cur) set1.push_back((LL)(cur * 1000000));
    s.clear();
    s << s2;
    while (s >> cur) set2.push_back((LL)(cur * 1000000));
    pair<int, LL> ans = spectral_convolution(set1, set2);
    printf("%d\n%.5f", ans.first, (double)ans.second/1e6);
    return 0;
}