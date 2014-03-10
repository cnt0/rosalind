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

class LCS
{
    class LCSTable
    {
        size_t   m_;
        size_t   n_;
        size_t  *data_;
    public:
        LCSTable(size_t m, size_t n)
            : m_(m)
            , n_(n)
        {
            data_ = new size_t[(m_ + 1) * (n_ + 1)];
        }
        ~LCSTable()
        {
            delete [] data_;
        }

        void setAt(size_t i, size_t j, size_t value)
        {
            data_[i + j * (m_ + 1)] = value;
        }

        size_t getAt(size_t i, size_t j) const
        {
            return data_[i + j * (m_ + 1)];
        }

        template<typename T> void
        build(const T *X, const T *Y)
        {
            for (size_t i = 0; i <= m_; ++i)
                setAt(i, 0, 0);

            for (size_t j = 0; j <= n_; ++j)
                setAt(0, j, 0);

            for (size_t i = 0; i < m_; ++i)
            {
                for (size_t j = 0; j < n_; ++j)
                {
                    if (X[i] == Y[j])
                        setAt(i + 1, j + 1, getAt(i, j) + 1);
                    else
                        setAt(i + 1, j + 1, std::max(getAt(i + 1, j), getAt(i, j + 1)));
                }
            }
        }
    };

    template<typename T> static void
    backtrackOne(const LCSTable &table,
                 const T *X, const T *Y, size_t i, size_t j,
                 std::vector<T> &result)
    {
        if (i == 0 || j == 0)
            return;
        if (X[i - 1] == Y[j - 1])
        {
            backtrackOne(table, X, Y, i - 1, j - 1, result);
            result.push_back(X[i - 1]);
            return;
        }
        if (table.getAt(i, j - 1) > table.getAt(i - 1, j))
            backtrackOne(table, X, Y, i, j - 1, result);
        else
            backtrackOne(table, X, Y, i - 1, j, result);
    }

public:
    template<typename T> static void
    findOne(T *X, size_t m, T *Y, size_t n,
            std::vector<T> &result)
    {
        LCSTable table(m, n);
        table.build(X, Y);
        backtrackOne(table, X, Y, m, n, result);
    }
};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("rosalind_lcsq.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif
    string s0, t0;
    cin >> s0 >> t0;
    char s[s0.length()], t[t0.length()];
    strcpy(s, s0.c_str());
    strcpy(t, t0.c_str());
    vector<char> result;
    LCS::findOne(s, s0.length(), t, t0.length(), result);
    string resultString(&result.front(), result.size());
    cout << resultString;
    return 0;
}