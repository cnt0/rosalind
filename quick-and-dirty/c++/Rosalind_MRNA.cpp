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
#define hashmap std::tr1::unordered_map
#define hashset std::tr1::unordered_set
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
const int MOD = 1000000;

hashmap<char, int> codons;

int main()
{
    freopen("rna_codon_table.txt", "r", stdin);
    REP(i, 64)
    {
        string rna; char codon;
        cin >> rna >> codon;
        if (codons.find(codon) != codons.end()) 
            ++codons[codon]; 
        else 
            codons[codon] = 1;
    }

#ifndef ONLINE_JUDGE
    freopen("rosalind_mrna.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif

    string protein_string;
    cin >> protein_string;
    size_t len = protein_string.length();
    LL ans = 1;
    REP(i, len) ans = ans * codons[protein_string[i]] % MOD;
    ans = ans * codons['s'] % MOD; //Stop
    cout << ans;
    return 0;
}