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
const int LEN = 6, fact[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};

int *bits6(int n)
{
    int *ans = new int[LEN];
    REP(i, LEN)
    {
        ans[i] = (n & 1) == 0 ? -1 : 1;
        n >>= 1;
    }
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("rosalind_sign.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif
    int n; cin >> n;
    int bits[1 << n][n];
    REP(j, 1 << n)
    {
        int *ke = bits6(j);
        REP(i, n) bits[j][i] = ke[i];
        delete ke;
    }
    int a[n];
    REP(i, n) a[i] = i + 1;
    cout << (1 << n) * fact[n] << '\n';
    do
        REP(i, 1 << n)
    {
        REP(j, n) cout << (a[j] * bits[i][j]) << ' ';
        cout << '\n';
    }
    while (next_permutation(a, a + n));
    return 0;
}