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

vector<string> raw_data;
map<string, string> graph;

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

vector<string> get_kmers(int k)
{
    vector<string> ans;
    foreach(raw_data, data)
    {
        REP(i, data->length() - k + 1)
        {
            string tmp = data->substr(i, k);
            ans.push_back(tmp);
            ans.push_back(rc(tmp));
        }
    }
    return ans;
}


bool build_graph(vector<string> data)
{
    graph.clear();
    foreach(data, itr)
    {
        string s1 = itr->substr(0, itr->length() - 1);
        string s2 = itr->substr(1, itr->length() - 1);
        if ((contains(graph, s1)) && (graph[s1] != s2)) return false;
        graph[s1] = s2;
    }
    return true;
}

string test_graph()
{
    set<string> used;
    string first = graph.begin()->first, cur = graph.begin()->second;
    string ans = first;
    while (cur != first)
    {
        used.insert(cur);
        ans.append(1, cur[cur.length() - 1]);
        if (!contains(graph, cur))
            return "";
        else
            cur = graph[cur];
    }
    bool found = false;
    foreach(graph, itr) if (!contains(used, itr->first))
    {
        first = itr->first;
        found = true;
    }
    if (!found) return "";
    string ans2 = first;
    cur = graph[first];
    while (cur != first)
    {
        used.insert(cur);
        ans2.append(1, cur[cur.length() - 1]);
        if (!contains(graph, cur))
            return "";
        else
            cur = graph[cur];
    }
    if (used.size() == graph.size() - 2)
        return ans.substr(0, ans.length() - first.length() + 1);
    else 
        return "";
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("rosalind_gasm.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif
    string s;
    while (cin >> s)
    {
        raw_data.push_back(s);
    }
    debug(raw_data[0].length());
    REPD(i, raw_data[0].length(), 1)
    {
        build_graph(get_kmers(i));
        string ans = test_graph();
        if (ans != "")
        {
            cout << ans;
            debug(i);
            break;
        }
    }
    return 0;
}