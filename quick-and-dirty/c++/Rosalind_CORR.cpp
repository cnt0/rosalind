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
using namespace tr1;

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
#define debug(x) { if(DEBUG) cerr << #x << " = " << x << endl; }
#define debugv(x) { if (DEBUG) cerr << #x << " = "; foreach((x), it) cerr << *it << ", "; cerr << endl; }

const double PI = 3.1415926535897932384626433832795;

#define DEBUG 1

typedef unordered_map<string, int> counter;

const string alphabet = "ATGC";

string rc(string s)
{
    string ans(s);
    size_t n = ans.length();
    REP(i, ans.length()) switch (s[n - 1 - i])
    {
    case 'A': ans[i] = 'T'; break;
    case 'T': ans[i] = 'A'; break;
    case 'G': ans[i] = 'C'; break;
    default: ans[i] = 'G'; break;
    }
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("rosalind_corr.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif
    counter cnt;
    string s;
    while (cin >> s)
    {
        counter::iterator itr = cnt.find(s);
        counter::iterator itr_rc = cnt.find(rc(s));
        if (itr == cnt.end())
            if (itr_rc == cnt.end())
                cnt.insert(make_pair(s, 1));
            else
                itr_rc->second += 1;
        else
            itr->second += 1;
    }
    unordered_set<string> errs;
    foreach(cnt, read) if (read->second == 1)
        errs.insert(read->first);
    while (!errs.empty())
    {
        string err = *errs.begin(), corr = err, err_rc = rc(err), corr_rc = err_rc, candidate = "";
        errs.erase(errs.begin());
        bool multiple_candidates = false;
        REP(i, corr.length())
        {
            bool found = false;
            REP(j, alphabet.size())
            {
                if (alphabet[j] != err[i])
                {
                    corr[i] = alphabet[j];
                    counter::iterator find = cnt.find(corr);
                    if (find != cnt.end() && find->second > 1)
                    {
                        if (candidate == "")
                            candidate = corr;
                        else if (corr != candidate && rc(corr) != candidate)
                            multiple_candidates = true;
                        found = true;
                        break;
                    }
                }
                if (alphabet[j] != err_rc[i])
                {
                    corr_rc[i] = alphabet[j];
                    counter::iterator find = cnt.find(corr_rc);
                    if (find != cnt.end() && find->second > 1)
                    {
                        if (candidate == "")
                            candidate = rc(corr_rc);
                        else if (corr_rc != candidate && rc(corr_rc) != candidate)
                            multiple_candidates = true;
                        found = true;
                        break;
                    }
                }
            }
            if (found) break;
            corr[i] = err[i];
            corr_rc[i] = err_rc[i];
        }
        if (candidate.length() > 0 && !multiple_candidates)
            cout << err << "->" << candidate << endl;
    }
    return 0;
}