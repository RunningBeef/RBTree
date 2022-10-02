#include "../include/RedBlackTree.hpp"
#include <map>
#include <ctime>
// 数据量较小情况下红黑树是否正常，并且打印测试每一步树的结构
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

// 数据量较大情况下红黑树是否正常
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
    cout<< "insert ok!" << endl;
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
    cout << "erase ok!" << endl;
    cout << "RedBlackTree test success!!!" << endl;
}

template <class T1, class T2>
void testRedBlackTreeInsert(int n, RedBlackTree<T1, T2> &redBlackTree)
{
    clock_t begin = clock();
    while (n--)
        redBlackTree.insert(n, 1);
    clock_t end = clock();
    cout << "RedBlackTree insert cost: " << end - begin << endl;
}

template <class T1, class T2>
void testRedBlackTreeErase(int n, RedBlackTree<T1, T2> &redBlackTree)
{
    clock_t begin = clock();
    while (n--)
        redBlackTree.erase(n);
    clock_t end = clock();
    cout << "RedBlackTree erase cost: " << end - begin << endl;
}

void testMapInsert(int n, map<int, int> &mp)
{
    clock_t begin = clock();
    while (n--)
        mp[n] = 1;
    clock_t end = clock();
    cout << "map insert cost: " << end - begin << endl;
}

void testMapErase(int n, map<int, int> &mp)
{
    clock_t begin = clock();
    while (n--)
        mp.erase(mp.find(n));
    clock_t end = clock();
    cout << "map erase cost: " << end - begin << endl;
}

// 通过对比map的插入删除时间消耗，判断红黑树性能是否正常
void testTimeCost()
{
    cout << "\n\n\n--------------------compare time cost with map------------------" << endl;
    int volume = 1e5;
    map<int, int> mp;
    RedBlackTree<int, int> redBlackTree;

    testRedBlackTreeInsert(volume, redBlackTree);
    testRedBlackTreeErase(volume, redBlackTree);

    testMapInsert(volume, mp);
    testMapErase(volume, mp);
    return;
}

int main()
{
    int n;
    cout << "Please enter a non negative integer < 50 to test the accuracy " << endl;
    cin >> n;
    testSmallData(n);
    cout << "\n\n\nPlease enter a non negative integer < 1000000 to test the performance" << endl;
    cin >> n;
    testBigData(n);
    testTimeCost();
    return 0;
}