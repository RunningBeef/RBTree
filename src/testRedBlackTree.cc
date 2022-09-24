#include "../include/RedBlackTree.hpp"

void test(int n)
{
    RedBlackTree<int, int> red_black_tree;
    unordered_map<int, int> mp; /* 标记已经生成的key */
    vector<int> index;          /* 保存key方便删除 */
    int x = n;
    /* 测试插入 */
    while (x--)
    {
        /* 随机生成key */
        int key;
        while (mp.find(key = (rand() * 1000 + rand()%1000)) != mp.end());

        mp[key] = 1;    index.push_back(key);
        cout << "insert key: " << key << endl;
        
        red_black_tree.insert(key, 1);
        red_black_tree.checkRedBlackTree();
    }

    cout << "--------------------------------" << endl;
    cout << "--------------------------------" << endl;

    /* 随机将插入的key删除 */
    while (index.size())
    {
        /* 随机生成已有的key并删除对应结点 */
        int id = rand() % index.size();
        int key = index[id];

        cout << "erase key: " << key << endl;
        index.erase(index.begin() + id);

        red_black_tree.erase(key);
        red_black_tree.checkRedBlackTree();
    }

    cout << "RedBlackTree test success!!!" << endl;
}

int main(){
    int n;  
    cout << "Please enter a non negative integer to indicate the data volume of the test red black tree" << endl;
    cin >> n;
    test(n);

    return 0;
}