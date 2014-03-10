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

#define LL long long
#define pb push_back
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

const int inf = numeric_limits<int>::max();
typedef unsigned char UChar;

int n, cnt = 0;
vector<int> strangers;

struct Link
{
    int start, end;
    int to;

    Link()
    {
        to = -1;
    }

    Link(int _start, int _end, int _to)
    {
        start = _start;
        end = _end;
        to = _to;
    }
};

struct Vertex
{
    vector<Link> links;
    int suffix;
    set<int> lines;
    bool lines_computed;
    bool lcs_computed;
    string lcs;

    Vertex()
    {
        links.assign(256, Link());
        suffix = -1;
    }
};

vector<Vertex> tree;
int root, dummy;

string sample;

UChar t(int i)
{
    return (i < 0) ? (-i - 1) : sample[i];
}

int newVertex()
{
    int i = tree.size();
    tree.push_back(Vertex());
    return i;
}

void link(int from, int start, int end, int to)
{
    tree[from].links[t(start)] = Link(start, end, to);
}

int &f(int v)
{
    return tree[v].suffix;
}

void print(int v, int start = 0, int end = 0, string prefix = "")
{
    printf("%s", prefix.c_str());
    //printf("%d %d %d ", v, start, end);
    foreach(tree[v].lines, itr) cout << (*itr) << ' ';
    for (int i = start; i < end && i < sample.length(); i++)
        printf("%c", t(i));
    if (end == inf) printf(".");

    printf(" [%2d]", v);
    if (f(v) != -1)
        printf(" f = %d", f(v));
    printf("\n");

    for (int i = 0; i < 256; i++)
        if (tree[v].links[i].to != -1)
        {
            print(tree[v].links[i].to, tree[v].links[i].start,
                  tree[v].links[i].end, prefix + "   ");
        }
}

void initTree()
{
    tree.clear();
    dummy = newVertex();
    root = newVertex();

    f(root) = dummy;
    for (int i = 0; i < 256; i++)
        link(dummy, -i - 1, -i, root);
}

pair<int, int> canonize(int v, int start, int end)
{
    if (end <= start)
    {
        return make_pair(v, start);
    }
    else
    {
        Link cur = tree[v].links[t(start)];
        while (end - start >= cur.end - cur.start)
        {
            start += cur.end - cur.start;
            v = cur.to;
            if (end > start)
                cur = tree[v].links[t(start)];
        }
        return make_pair(v, start);
    }
}

pair<bool, int> testAndSplit(int v, int start, int end, UChar c)
{
    if (end <= start)
    {
        return make_pair(tree[v].links[c].to != -1, v);
    }
    else
    {
        Link cur = tree[v].links[t(start)];
        if (c == t(cur.start + end - start))
            return make_pair(true, v);

        int middle = newVertex();
        link(v, cur.start, cur.start + end - start, middle);
        link(middle, cur.start + end - start, cur.end, cur.to);
        return make_pair(false, middle);
    }
}

pair<int, int> update(int v, int start, int end)
{
    //Link cur = tree[v].links[t(start)];
    pair<bool, int> splitRes;
    int oldR = root;

    splitRes = testAndSplit(v, start, end, t(end));
    while (!splitRes.first)
    {
        link(splitRes.second, end, inf, newVertex());

        if (oldR != root)
            f(oldR) = splitRes.second;
        oldR = splitRes.second;

        pair<int, int> newPoint = canonize(f(v), start, end);
        v = newPoint.first;
        start = newPoint.second;
        splitRes = testAndSplit(v, start, end, t(end));
    }
    if (oldR != root)
        f(oldR) = splitRes.second;
    return make_pair(v, start);
}

void ukkonen()
{
    initTree();
    pair<int, int> activePoint = make_pair(root, 0);
    for (int i = 0; i < sample.length(); i++)
    {
        activePoint = update(activePoint.first, activePoint.second, i);
        activePoint = canonize(activePoint.first, activePoint.second, i + 1);
    }
}

bool present(string word)
{
    int v = root, start = 0, end = 0;
    for (int i = 0; i < word.length(); i++)
    {
        UChar cur = word[i];
        if (end == start)
        {
            if (tree[v].links[cur].to == -1) return false;
            start = tree[v].links[cur].start;
            end = start + 1;
        }
        else
        {
            if (cur != t(end)) return false;
            end++;
        }
        if (end == tree[v].links[t(start)].end)
        {
            v = tree[v].links[t(start)].to;
            start = 0;
            end = 0;
        }
    }
    return true;
}

char inBig[1000], inSmall[1000];

void printlinks(int v)
{
    REP(i, 256)
    if ((tree[v].links[i].start >= 0) && (tree[v].links[i].start < sample.length()))
        /*{
            cout<<tree[v].links[i].start<<' '<<tree[v].links[i].end<<'\n';
        }*/
        cout << sample.substr(tree[v].links[i].start, min((ulong)tree[v].links[i].end - 1, (ulong)sample.length() - 1) - tree[v].links[i].start + 1) << '\n';

}

void printlinks2(int v)
{
    REP(i, 256)
    if (tree[v].links[i].to > -1)
        cout << tree[v].links[i].to << '\n';
}

int firstStranger(int l, int r)
{
    int ans = *lower_bound(ALL(strangers), l);
    /*if (sample[ans] + 127 == 198)
    {
        debug(l);
        debug(r);
    }*/
    if (ans > r) return -1;
    else return sample[ans] + 127;
}

void getLines(int v)
{
    if (!tree[v].lines_computed)
    {
        REP(i, 256) if (tree[v].links[i].end > 0) if (tree[v].links[i].start < sample.size())
            {
                int l = tree[v].links[i].start;
                int r = min((int)tree[v].links[i].end - 1, (int)sample.size() - 1);
                int f = firstStranger(l, r);
                if (f == -1)
                {
                    getLines(tree[v].links[i].to);
                    foreach(tree[tree[v].links[i].to].lines, itr)
                    tree[v].lines.insert(*itr);
                }
                else
                    tree[v].lines.insert(f);
            }
        tree[v].lines_computed = true;
    }
}

string lcs(int v)
{
    string ans = "";
    if (tree[1].lines.size() == cnt)
        REP(i, 256)
        if ((tree[v].links[i].to > -1)
                && (tree[v].links[i].end > 0)
                && (tree[v].links[i].start < sample.length()))
        {
            int l = tree[v].links[i].start;
            int r = min((int)tree[v].links[i].end - 1, (int)sample.size() - 1);
            int f = firstStranger(l, r);
            if (tree[tree[v].links[i].to].lines.size() == cnt)
                if (f == -1)
                {
                    string ans2 = sample.substr(l, r - l + 1) + lcs(tree[v].links[i].to);
                    if (ans2.length() > ans.length())
                        ans = ans2;
                }
        }
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("rosalind_suff.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif
    cin >> sample;
    n = sample.length();
    ukkonen();
    queue<int> q;
    q.push(1);
    while (!q.empty())
    {
        int v = q.front();
        debug(v);
        q.pop();
        printlinks(v);
        foreach(tree[v].links, link) if (link->to >= 0)
            q.push(link->to);
    }
    return 0;
}