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

map<string, int> kmers;

void fill_kmers()//bydlocode
{
    string alphabet = "ACGT";
    string kmer = "AAAA";
    REP(i, 4) REP(j, 4) REP(k, 4) REP(l, 4)
    {
        kmer[0] = alphabet[i];
        kmer[1] = alphabet[j];
        kmer[2] = alphabet[k];
        kmer[3] = alphabet[l];
        kmers[kmer] = 0;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("rosalind_kmer.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif
    fill_kmers();
    string fasta_descr, data = "", tmp;
    cin >> fasta_descr;
    while (cin >> tmp) data += tmp;
    REP(i, data.length() - 3) kmers[data.substr(i, 4)] += 1;
    debug(kmers.size());
    foreach(kmers, kmer) cout << kmer->second << ' ';
    return 0;
}