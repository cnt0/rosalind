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
#define debugv(x) { if (DEBUG) cerr << #x << " = "; foreach((x), it) cerr << *it << ", "; cerr << endl; }

const double PI = 3.1415926535897932384626433832795;

char proteins[] = {'A',
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

LL masses[] = {7103711LL,
               10300919LL,
               11502694LL,
               12904259LL,
               14706841LL,
               5702146LL,
               13705891LL,
               11308406LL,
               12809496LL,
               11308406LL,
               13104049LL,
               11404293LL,
               9705276LL,
               12805858LL,
               15610111LL,
               8703203LL,
               10104768LL,
               9906841LL,
               18607931LL,
               16306333LL
              };


map<char, LL> mass_table;

LL mass(string s)
{
    LL ans = 0;
    REP(i, s.length()) ans += mass_table[s[i]];
    return ans;
}
vector<LL> mass_spectrum_2(string s0)
{
    vector<LL> ans;
    string s = s0.substr(0 , s0.length() - 1);
    REP(i, s.length())
    {
        string s1 = s.substr(0, i + 1);
        string s2 = s.substr(i, s.length() - i);
        LL pb1 = mass(s1);
        LL pb2 = mass(s2);
        //cerr << s1 << ": " << pb1 << '\t' << s2 << ": " << pb2 << '\n';
        if (i < s.length() - 1) ans.push_back(pb1);
        ans.push_back(pb2);
    }
    sort(ALL(ans));
    return ans;
}

pair<LL, LL> spectral_convolution(vector<LL> set1, vector<LL> set2)
{
    map<LL, LL> dif;
    foreach(set1, itr1) foreach(set2, itr2)
    {
        LL key = (*itr1) - (*itr2);
        if (contains(dif, key)) ++dif[key];
        else dif[key] = 1;
    }
    LL key = -1LL;
    LL cnt = 0LL;
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

vector<LL> get_mass_spectrum(string s)
{
    vector<LL> ans;
    LL cur = 0;
    REP(i, s.length())
    {
        cur += mass_table[s[i]];
        ans.push_back(cur);
    }
    REP(i, s.length())
    {
        cur -= mass_table[s[i]];
        if (i < s.length() - 1) ans.push_back(cur);
    }
    sort(ALL(ans));
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("rosalind_prsm.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif
    REP(i, 20) mass_table[proteins[i]] = masses[i];
    //foreach(mass_table, itr) cerr<<itr->first<<' '<<itr->second<<'\n';
    int n;
    vector<string> database;
    vector<LL> mass_spectrum;
    cin >> n;
    string tmp;
    REP(i, n)
    {
        cin >> tmp;
        database.push_back(tmp);
    }
    double tmp2;
    while (cin >> tmp2)
        mass_spectrum.push_back((LL)(100000LL * tmp2));

    LL conv = 0LL;
    string ans;
    vector<LL> ms2 = get_mass_spectrum("GSDMQS");
    vector<LL> ms3 = mass_spectrum_2("GSDMQS");
    debugv(ms2);
    debugv(ms3);
    foreach(database, str)
    {
        vector<LL> ms2 = mass_spectrum_2(*str);
        //vector<LL> ms3 = mass_spectrum_2(*str);
        LL cur_conv = spectral_convolution(mass_spectrum, ms2).first;
        if (cur_conv > conv)
        {
            conv = cur_conv;
            ans = *str;
        }
    }
    debug(conv);
    debug(ans);
    cout << conv << '\n' << ans;
    return 0;
}