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
#include <limits>
#include <tr1/unordered_map>
#include <tr1/unordered_set>

using namespace std;
using namespace tr1;

#define LL long long
#define pb push_back
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

typedef map<string, set<string> > graph;

graph g;

int len;

set<string> kmers;

vector<string> dfs(string cur, set<string> cur_kmers)
{
    debug(cur);
    //debug(cur_kmers.size());
    if (cur_kmers.size() == kmers.size())
        return vector<string>(1, cur);
    vector<string> ans;
    string s1 = cur.substr(cur.length() - len + 1, len - 1);
    set<string> to = g.find(s1)->second;
    foreach(to, itr)
    {
        string s_add = itr->substr(itr->length() - 1, 1);
        string kmer = s1 + s_add;
        if (cur_kmers.find(kmer) == cur_kmers.end())
        {
            set<string> new_cur_kmers(cur_kmers);
            new_cur_kmers.insert(kmer);
            vector<string> cur2 = dfs(cur + s_add, new_cur_kmers);
            foreach(cur2, itr2) ans.push_back(*itr2);
        }
    }
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("rosalind_grep.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif
    string tmp, fst;
    while (cin >> tmp)
    {
        kmers.insert(tmp);
        string s1 = tmp.substr(0, tmp.length() - 1);
        string s2 = tmp.substr(1, tmp.length() - 1);
        if (fst == "")
        {
            fst = tmp;
            len = fst.length();
        }
        graph::iterator p = g.find(s1);
        if (p == g.end())
        {
            g.insert(make_pair(s1, set<string>()));
            g.find(s1)->second.insert(s2);
        }
        else
            p->second.insert(s2);

    }
    debug(kmers.size());
    set<string> start_kmers;
    start_kmers.insert(fst);
    vector<string> ans = dfs(fst, start_kmers);
    foreach(ans, itr)
    {
        cout << itr->substr(0, itr->length() - len + 1) << endl;
    }
    return 0;
}