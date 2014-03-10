#include <iostream>
#include <cstdio>

using namespace std;

#define REP(i,n) for(int (i)=0;(i)<(int)(n);(i)++)

int main()
{
#ifndef ONLINE_JUDGE
    freopen("rosalind_sseq.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif
    string s, t;
    cin >> s >> t;
    int cur = 0;
    REP(i, s.length()) if (s[i] == t[cur])
    {
    	cout << i + 1 << ' ';
    	++cur;
    }
    return 0;
}