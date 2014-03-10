#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <cmath>

using namespace std;

#define LL long long
#define pb push_back
#define mp make_pair
#define hashmap tr1::unordered_map
#define hashset tr1::unordered_set
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

const uint wtf = 4294967168;

const char sep = ' ';

const int LEN = 10, fact[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800}, f10 = 3628800, INF = INFINITY;
int prms[f10][LEN];

int d[f10], p[f10];

int *unpack(const int n, int i)
{
    int *perm = new int[n];
    /*REP(k, n)     //<---------- alternative version
    {
        perm[k] = i / fact[n - 1 - k];
        i = i % fact[n - 1 - k];
    }
    REPD(k, n - 1, 0)
    REPD(j, k - 1, 0)
    if (perm[j] <= perm[k])
        perm[k]++;*/
    REP(k, n) perm[k] = prms[i][k];
    return perm;
}

int pack(int *ar, int cur, int size)
{
    if (cur == size) return 0;
    else
    {
        REP2(i, cur + 1, size) if (ar[i] > ar[cur]) --ar[i];
        return ar[cur] * fact[size - 1 - cur] + pack(ar, cur + 1, size);
    }
}

int *reversal(int *v, int l, int r)
{
    int *to = new int[LEN];
    REP(i, l) to[i] = v[i];
    REP(i, r - l + 1) to[i + l] = v[r - i];
    REP2(i, r + 1, LEN) to[i] = v[i];
    return to;
}

void clear(int *a)
{
    REP(i, LEN) a[i] = i;
}

void fill_prms()
{
    int a[LEN];
    clear(a);
    REP(i, f10)
    {
        d[i] = INF;
        REP(j, LEN) prms[i][j] = a[j];
        next_permutation(a, a + LEN);
    }
}

void preprocessing()
{
    int cnt = 0, a[LEN];
    clear(a);
    REP(i, f10)
    {
        d[i] = INF;
        REP(j, LEN) prms[i][j] = a[j];
        next_permutation(a, a + LEN);
    }
    clear(a);
    d[pack(a, 0, LEN)] = 0;
    queue<int> q;
    q.push(pack(a, 0, LEN));
    while (!q.empty())  //BFS
    {
        ++cnt;
        if (cnt % 100000 == 0) cerr << cnt << " Done; queue size is " << q.size() << '\n';
        int vu = q.front();
        q.pop();
        int *v = unpack(LEN, vu);
        REP(l, LEN) REP2(r, l + 1, LEN)
        {
            int *to = reversal(v, l, r);
            int tu = pack(to, 0, LEN);
            delete to; //crucial, prevents memory leak
            if (d[tu] == INF)
            {
                int cto = d[vu] + 1;
                p[tu] = vu;

                d[tu] = cto;
                q.push(tu);
            }
        }
        delete v; //crucial, prevents memory leak
    }
    cerr << "All Done\n";
    freopen("rear_preprocessing.txt", "w", stdout);
    REP(i, f10) cout << i << '\t' << d[i] << '\t' << p[i] << '\n';
}

int l(int *a, int *b)
{
    REP(i, LEN) if (a[i] != b[i]) return i + 1;
    return -1;
}

int r(int *a, int *b)
{
    REPD(i, LEN - 1, 0) if (a[i] != b[i]) return i + 1;
    return -1;
}

int main()
{
    //preprocessing();
    fill_prms();
    freopen("rear_preprocessing.txt", "r", stdin);
    int tmp;
    REP(i, f10) cin >> tmp >> d[i] >> p[i];
    freopen("rosalind_sort.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int a[LEN], b[LEN], c[LEN];
    REP(i, LEN) cin >> a[i];
    REP(i, LEN) cin >> b[i];
    REP(i, LEN) c[i] = find(b, b + LEN, a[i]) - b;
    REP(i, LEN) cerr << a[i] << ' '; cerr << '\n';
    REP(i, LEN) cerr << b[i] << ' '; cerr << '\n';
    REP(i, LEN) cerr << c[i] << ' '; cerr << '\n';
    cerr << '\n';
    int N = pack(c, 0, LEN);
    cout << d[N] << '\n';
    while (N != 0)
    {
        int *e = unpack(LEN, N);
        REP(i, LEN) cerr << e[i] << ' '; cerr << '\n';
        int *parent = unpack(LEN, p[N]);
        REP(i, LEN) cerr << parent[i] << ' '; cerr << '\n';
        cout << l(e, parent) << ' ' << r(e, parent) << '\n';
        N = p[N];
        cerr << '\n';
    }
    return 0;
}