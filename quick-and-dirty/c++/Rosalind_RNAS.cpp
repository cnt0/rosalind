#include <iostream>
#include <gmpxx.h>

using namespace std;

const int MAXLEN = 200;

string RNA;

mpz_class cache[MAXLEN][MAXLEN];

bool complement(char c1, char c2)
{
    switch (c1)
    {
    case 'A': return c2 == 'U';
    case 'U': return (c2 == 'A') || (c2 == 'G');
    case 'G': return (c2 == 'C') || (c2 == 'U');
    default: return c2 == 'G';
    }
}

mpz_class dp(int l, int r)
{
    if (cache[l][r] != mpz_class(-1))
        return cache[l][r];
    else
    {
        mpz_class ans(0);
        for (int i = l; i <= r; ++i)
            for (int j = i + 4; j <= r; ++j)
                if (complement(RNA[i], RNA[j]))
                    ans += dp(i + 1, j - 1) * dp(j + 1, r);
        cache[l][r] = ans + 1;
        return ans + 1;
    }
}

int main()
{
    freopen("rosalind_rnas_2.txt", "r", stdin); 
    freopen("output.txt", "w", stdout);
	for (int i = 0; i < MAXLEN; ++i)
        for (int j = 0; j < MAXLEN; ++j)
            cache[i][j] = mpz_class(-1);
    cin >> RNA;
    mpz_class ans = dp(0, RNA.length() - 1);
    cout << ans.get_str();
    return 0;
}