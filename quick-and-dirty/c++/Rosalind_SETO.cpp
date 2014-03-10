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

template< typename T >
ostream &operator<< (ostream &os, const set<T> &obj)
{
    os << "{";
    size_t cnt = 0;
    foreach(obj, item)
    {
        ++cnt;
        os << *item;
        if (cnt < obj.size()) os << ", ";
    }
    os << "}";
    return os;
}

template< typename T >
set<T> operator- (set<T> &obj1, set<T> &obj2)
{
    set<T> ans;
    foreach(obj1, item) if (!contains(obj2, *item)) ans.insert(*item);
    return ans;
}

template< typename T >
set<T> operator+ (set<T> &obj1, set<T> &obj2)
{
    set<T> ans;
    foreach(obj1, item) ans.insert(*item);
    foreach(obj2, item) ans.insert(*item);
    return ans;
}

template< typename T >
set<T> operator* (set<T> &obj1, set<T> &obj2)
{
    set<T> ans;
    foreach(obj1, item) if (contains(obj2, *item)) ans.insert(*item);
    return ans;
}

set<int> parse(string s)
{
    s = s.substr(1, s.length() - 2);
    REP(i, s.length()) if (s[i] == ',') s[i] = ' ';
    stringstream t;
    t << s;
    set<int> ans;
    int cur;
    while (t >> cur) ans.insert(cur);
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("rosalind_seto.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif
    cin >> n;
    string tmp;
    getline(cin, tmp);
    set<int> A, B, C;
    REP2(i, 1, n + 1) C.insert(i);
    getline(cin, tmp);
    A = parse(tmp);
    getline(cin, tmp);
    B = parse(tmp);
    cout << A + B << '\n' << A * B << '\n' << A - B << '\n' << B - A << '\n' << C - A << '\n' << C - B;
    return 0;
}