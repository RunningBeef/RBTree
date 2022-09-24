#include "../include/RedBlackTree.hpp"

void testSmallData(int n)
{
    RedBlackTree<int, int> red_black_tree;
    unordered_map<int, int> mp; /* 标记已经生成的key */
    vector<int> index;          /* 保存key方便删除 */
    int x = n;
    /* 随机生成要插入的结点的key*/
    while (x--)
    {
        int key;
        while (mp.find(key = rand() % 1000) != mp.end())
        {
        }

        mp[key] = 1;
        index.push_back(key);
        cout << "insert key: " << key << endl;

        red_black_tree.insert(key, 1);
        red_black_tree.checkRedBlackTree();
        red_black_tree.printRedBlackTree(); /* 如果树的结点太多或者key太大输出结果会变形 */
    }

    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;

    /* 随机将插入的结点删除 */
    while (index.size())
    {
        int id = rand() % index.size();
        int key = index[id];

        cout << "erase key: " << key << endl;
        index.erase(index.begin() + id);

        red_black_tree.erase(key);
        red_black_tree.checkRedBlackTree();
        red_black_tree.printRedBlackTree(); /* 如果树的结点太多或者key太大输出结果会变形 */
    }

    cout << "RedBlackTree test success!!!" << endl;
}

void testBigData(int n)
{
    RedBlackTree<int, int> red_black_tree;
    unordered_map<int, int> mp; /* 标记已经生成的key */
    vector<int> index;          /* 保存key方便删除 */
    int x = n;
    /* 随机生成要插入的结点的key*/
    while (x--)
    {
        int key;
        while (mp.find(key = rand() % 10000 * 10000 + rand() % 10000) != mp.end())
        {
        }

        mp[key] = 1;
        index.push_back(key);
        // cout << "insert key: " << key << endl;

        red_black_tree.insert(key, 1);
        red_black_tree.checkRedBlackTree();
    }

    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;

    /* 随机将插入的结点删除 */
    while (index.size())
    {
        int id = rand() % index.size();
        int key = index[id];

        // cout << "erase key: " << key << endl;
        index.erase(index.begin() + id);

        red_black_tree.erase(key);
        red_black_tree.checkRedBlackTree();
    }

    cout << "RedBlackTree test success!!!" << endl;
}

int main()
{
    int n;
    cout << "Please enter a non negative integer < 50 to test the accuracy " << endl;
    cin >> n;
    testSmallData(n);
    cout << "Please enter a non negative integer < 1000000 to test the performance" << endl;
    cin >> n;
    testBigData(n);
    return 0;
}