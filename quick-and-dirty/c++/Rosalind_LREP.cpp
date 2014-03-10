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

int enough_n, K;

string DNA;

size_t LEN;

int parse(string node)
{
    return atoi(node.substr(4).c_str());
}

struct Link
{
    size_t location, length, to;
    Link(size_t _location, size_t _length, size_t _to)
    {
        location = _location;
        length = _length;
        to = _to;
    }
};

struct Vertex
{
    size_t total_length, n_children;
    vector<Link> links;
};

ostream &operator<< (ostream &os, const Link &obj)
{
    os << "Link(" << obj.location << ", " << obj.length << ", " << obj.to << ')';
    return os;
}

vector<Vertex> tree;

int d(size_t v)
{
    int ans = 0;
    foreach(tree[v].links, link)
    {
        int rec = d(link->to);
        ans += rec == 0 ? 1 : rec;
    }
    tree[v].n_children = ans;
    return ans;
}

string getans()
{
    pair<size_t, size_t> ans = make_pair(0, 0);
    queue<size_t> q;
    q.push(0);
    while (!q.empty())
    {
        size_t to = q.front();
        q.pop();
        foreach(tree[to].links, link)
        {
            tree[link->to].total_length = tree[to].total_length + link->length;
            if ((tree[link->to].n_children >= K) && (tree[link->to].total_length > ans.second))
            {
                ans.first = link->location + link->length;
                ans.second = tree[link->to].total_length;
            }
            q.push(link->to);
        }
    }
    return DNA.substr(ans.first - ans.second, ans.second);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("rosalind_lrep.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif
    cin >> DNA >> K;
    LEN = DNA.length();
    tree.reserve(LEN * 10);
    string tmp_parent, tmp_child;
    size_t loc, len;
    while (cin >> tmp_parent)
    {
        cin >> tmp_child >> loc >> len;
        int parent = parse(tmp_parent);
        int child = parse(tmp_child);
        tree[parent - 1].links.push_back(Link(loc - 1, len, child - 1));
    }
    debug(d(0));
    cout << getans();
    return 0;
}