#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int idx = 1;

struct TrieNode
{
    unordered_map<char, TrieNode *> children;
    int key;

    TrieNode *getOrElseUpdate(char k)
    {
        if (children.find(k) == children.end())
            children.insert(make_pair(k, new TrieNode()));
        return children.find(k)->second;
    }

    TrieNode()
    {
        key = idx++;
        children = unordered_map<char, TrieNode *>();
    }
};

void print(TrieNode cur)
{
    for (auto kv : cur.children)
    {
        cout << cur.key << ' ' << kv.second->key << ' ' << kv.first << '\n';
        print(*kv.second);
    }
}

int main()
{
    freopen("rosalind_trie.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(0);
    string s;
    TrieNode *root = new TrieNode();
    while (cin >> s)
    {
        TrieNode *v = root; 
        for (char c : s) v = v->getOrElseUpdate(c);
    }
    print(*root);
    return 0;
}