#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<int, int> m;
vector<int> a;
int len = 0;

void p(vector<int> &L, map<int, int> &remain)
{
    if (remain.size() == 0)
    {
        for (auto i : L) cout << i << ' ';
        exit(0);
    }

    for (int i = 0; i < 2; ++i)
    {
        map<int, int> newremain(remain.begin(), remain.end());
        auto it = newremain.rbegin();
        int cur = i == 0 ? it->first : len - it->first;
        bool correctBranch = true;
        for (auto i: L)
        {
            auto it2 = newremain.find(fabs(i - cur));
            if (it2 == newremain.end())
            {
                correctBranch = false;
                break;
            }
            else if (--it2->second == 0)
                newremain.erase(it2);
        }
        if (correctBranch)
        {
            vector<int> newL(L);
            newL.push_back(cur);
            p(newL, newremain);
        }
    }
    return;
}

int main()
{
    freopen("rosalind_pdpl.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    while (cin >> n) a.push_back(n);
    for (int n = 0; n < a.size(); ++n)
        if (m.find(a[n]) == m.end())
            m.insert(make_pair(a[n], 1));
        else
            ++m.find(a[n])->second;
    len = m.rbegin()->first;
    vector<int> L = {0};
    p(L, m);
    return 0;
}