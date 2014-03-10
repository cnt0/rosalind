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

typedef vector<int> V;

vector<string> introns;

string DNA;

map<string, string> rna_codon_table;

string dna_to_rna(string dna)
{
    string rna = dna;
    REP(i, dna.size()) if (rna[i] == 'T') rna[i] = 'U';
    return rna;
}

int main()
{
    freopen("rna_codon_table.txt", "r", stdin);
    string rna, codon;
    REP(i, 64)
    {
        cin >> rna >> codon;
        rna_codon_table[rna] = codon;
    }
    debug(1);
    //foreach(rna_codon_table, itr) cerr << itr->first << '\t' << itr->second << '\n';
    freopen("rosalind_splc.txt", "r", stdin); freopen("output.txt", "w", stdout);
    cin >> DNA;
    string intron;
    while (cin >> intron) introns.push_back(intron);
    vector<pair<int, int> > occurs;
    size_t cur = 0;
    while (cur != string::npos)
    {
        size_t cur2 = string::npos;
        size_t len = 0;
        int t = -1;
        REP(i, introns.size()) if (DNA.find(introns[i], cur) < cur2)
        {
            cur2 = DNA.find(introns[i], cur);
            len = introns[i].length();
            t = i;
        }
        if (cur2 < string::npos)
        {
            occurs.push_back(make_pair(t, cur2));
            cur2 += len;
        }
        cur = cur2;
    }
    string ans = "";
    ans += DNA.substr(0, occurs[0].second);
    REP2(i, 1, occurs.size())
    {
        size_t idx = occurs[i - 1].second + introns[occurs[i - 1].first].size();
        ans += DNA.substr(idx, occurs[i].second - idx);
    }
    size_t idx = occurs[occurs.size() - 1].second + introns[occurs[occurs.size() - 1].first].size();
    ans += DNA.substr(idx, DNA.length() - idx);
    ans = dna_to_rna(ans);
    REP(i, ans.length() / 3) cout << rna_codon_table[ans.substr(i * 3, 3)];
    return 0;
}