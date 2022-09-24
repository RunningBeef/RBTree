#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <unordered_map>
#define NODE_COLOR_RED 0
#define NODE_COLOR_BLACK 1
using namespace std;

template <class T1 = int, class T2 = int>
class RedBlackTree
{
private:
    struct Node
    {
        Node(T1 k, T2 v) : color(NODE_COLOR_RED), parent(nullptr), left_son(nullptr), right_son(nullptr), key(k), value(v) {}
        Node() : color(NODE_COLOR_RED), parent(nullptr), left_son(nullptr), right_son(nullptr) {}
        bool color;
        T1 key;
        T2 value;
        Node *parent;
        Node *left_son;
        Node *right_son;
    };
    Node *root_ = nullptr;

public:
    RedBlackTree();

    ~RedBlackTree();

    void insert(T1 key, T2 value);

    bool erase(T1 key);

    T2 *getValue(T1 key);

    Node *getNode(T1 key);

    void checkRedBlackTree();

    void printRedBlackTree();

private:
    void swapKeyAndValue(Node *a, Node *b);

    Node *getRoot();

    Node *getGrandparent(Node *son);

    Node *getUncle(Node *son);

    Node *getBrother(Node *son);

    Node *getPreNode(Node *traver);

    void rotatedLeft(Node *son);

    void rotatedRight(Node *son);

    void insertCaseOne(Node *son);

    void insertCaseTwo(Node *son);

    void insertCaseThree(Node *son);

    void insertCaseFour(Node *son);

    void insertCaseFive(Node *son);

    void eraseAndAdjust(Node *son);

    void eraseCaseOne(Node *son);

    void eraseCaseTwo(Node *son);

    void eraseCaseThree(Node *son);

    int getHeight(Node *root_);

    int checkBlackBalanceAndPointerAndColor(Node *temp);

    void checkBst(Node *root_);
};

template <class T1, class T2>
RedBlackTree<T1, T2>::RedBlackTree() : root_(nullptr) {}

template <class T1, class T2>
RedBlackTree<T1, T2>::~RedBlackTree()
{
    queue<Node *> q;
    if (root_)
    {
        q.push(root_);
        while (!q.empty())
        {
            root_ = q.front();
            q.pop();
            if (root_->left_son)
                q.push(root_->left_son);
            if (root_->right_son)
                q.push(root_->right_son);
            delete root_;
        }
    }
}

template <class T1, class T2>
typename RedBlackTree<T1, T2>::Node *RedBlackTree<T1, T2>::getRoot()
{
    return root_;
}

template <class T1, class T2>
typename RedBlackTree<T1, T2>::Node *RedBlackTree<T1, T2>::getGrandparent(Node *son)
{
    if (son->parent == nullptr || son->parent->parent == nullptr)
    {
#ifdef DEBUG
        cout << "error: no getUncle error " << endl;
#endif
        return nullptr;
    }
    return son->parent->parent;
}

template <class T1, class T2>

typename RedBlackTree<T1, T2>::Node *RedBlackTree<T1, T2>::getUncle(Node *son)
{
    Node *grandparent = getGrandparent(son);
    Node *father = son->parent;
    return grandparent->left_son == father ? grandparent->right_son : grandparent->left_son;
}

/* 返回兄弟结点 */
template <class T1, class T2>
typename RedBlackTree<T1, T2>::Node *RedBlackTree<T1, T2>::getBrother(Node *son)
{
    if (son == son->parent->left_son)
        return son->parent->right_son;
    else
        return son->parent->left_son;
}

/* 左旋 注意：要记得修改被转移结点的父指针

这里一定要考虑要调整的结点不一定是叶子节点，
因为上面有一种插入情况是要向上做递归检查的,
所以我们这边记得需要迁移的结点的左右儿子做适当的迁移*/
template <class T1, class T2>
void RedBlackTree<T1, T2>::rotatedLeft(Node *son)
{
    Node *parent = son->parent;
    Node *grandparent = parent->parent;

    /*  将旋转结点的左儿子转移成父节点的右儿子 */
    parent->right_son = son->left_son;
    if (son->left_son)
        son->left_son->parent = parent;

    /* 将父节点转移到旋转结点的左儿子 */
    son->left_son = parent;
    parent->parent = son;

    /* 修改son的父指针 */
    son->parent = grandparent;

    /* 修改grandparent的son指针 */
    if (grandparent) /* 可能没有祖父结点 */
        if (grandparent->left_son == parent)
            grandparent->left_son = son;
        else
            grandparent->right_son = son;

    else
        root_ = son;
}

/* 右旋 RR结构*/
template <class T1, class T2>
void RedBlackTree<T1, T2>::rotatedRight(Node *son)
{
    Node *parent = son->parent;
    Node *grandparent = parent->parent;

    /* 将旋转结点的右儿子转移到父节点的左儿子 */
    parent->left_son = son->right_son;
    if (son->right_son)
        son->right_son->parent = parent;

    /* 将旋转结点的右儿子改为父节点 */
    son->right_son = parent;
    parent->parent = son;

    /* 修改son的父指针 */
    son->parent = grandparent;

    /* 修改grandparent的son指针 */
    if (grandparent)
        if (grandparent->left_son == parent)
            grandparent->left_son = son;
        else
            grandparent->right_son = son;
    else
        root_ = son;
}

/* 没有根结点 */
template <class T1, class T2>
void RedBlackTree<T1, T2>::insertCaseOne(Node *son)
{
#ifdef DEBUG
    cout << "insertCaseOne" << endl;
#endif
    if (son->parent == nullptr)
    {
        root_ = son;
        root_->color = NODE_COLOR_BLACK;
    }
    else
        insertCaseTwo(son);
}

/* 父节点是黑色结点，插入结点默认是红色结点，所以直接插入即可 */
template <class T1, class T2>
void RedBlackTree<T1, T2>::insertCaseTwo(Node *son)
{
#ifdef DEBUG
    cout << "insertCaseTwo" << endl;
#endif
    if (son->parent->color == NODE_COLOR_BLACK) /* 父节点是黑色结点，那么直接插入一个红色结点 不影响黑色平衡 */
        return;
    else /* 父节点是红色结点需要调整 */
        insertCaseThree(son);
}

/* 父节点是红色结点，那么必定有祖父结点且为黑色。
当叔叔存在且是红色结点时将祖父结点变为红色。黑色下降，让父亲结点和叔叔结点都变为黑色.
考虑祖父结点的父节点可能为空（说明祖父结点是根结点，则只能把祖父结点变成黑色，也只有这种情况让黑色高度+1），或者祖父结点的父节点也可能为红色，
所以需要把祖父结点当做新插入的结点，进行插入做递归检查
可以思考下：是否影响了原树其他结点的黑色平衡？
*/
template <class T1, class T2>
void RedBlackTree<T1, T2>::insertCaseThree(Node *son)
{
#ifdef DEBUG
    cout << "insertCaseThree " << endl;
#endif
    if (getUncle(son) && getUncle(son)->color == NODE_COLOR_RED)
    {
        // //cout << "insertCaseThree if" << endl;
        getUncle(son)->color = son->parent->color = NODE_COLOR_BLACK;
        getGrandparent(son)->color = NODE_COLOR_RED;
        /* 递归检查祖父结点 */
        insertCaseOne(getGrandparent(son));
    }
    else
        insertCaseFour(son);
}

/*
当叔叔结点为黑色或者为空时(我们把空的叶子节点也当做黑色结点)
需要做旋转，根据插入结点和插入结点的父节点结构做不同旋转
LL: 右旋一次 insertCaseFive
RR：左旋一次 insertCaseFive
LR：先左旋一次变为LL再来处理
RL：先右旋一次变为RR再处理

注意：这边新插入的结点是红色的，所以没有改变之前的黑色平衡
但是插入结点的父节点是红色的，所以需要调整
我们在调整的时候只要保证对应从祖父结点向下经过的黑色结点个数一样
就仍能保持黑色平衡
*/
template <class T1, class T2>
void RedBlackTree<T1, T2>::insertCaseFour(Node *son)
{

#ifdef DEBUG
    cout << "insertCaseFour" << endl;
#endif
    /* 左右结构 调整为 左左结构 */
    if (son == son->parent->right_son && son->parent == getGrandparent(son)->left_son)
    {
        // //cout << "LR" << endl;
        rotatedLeft(son);
        son = son->left_son;

    } /* 右左结构 调整为 右右结构 */
    else if (son == son->parent->left_son && son->parent == getGrandparent(son)->right_son)
    {

        // //cout << "RL" << endl;
        rotatedRight(son);
        son = son->right_son;
    }
    /* 统一处理左左结构 和右右结构 */
    insertCaseFive(son);
}

/* 当叔叔是黑色结点或空结点，且插入结点结构是LL 或者 RR */
template <class T1, class T2>
void RedBlackTree<T1, T2>::insertCaseFive(Node *son)
{
    // cout << "insertCaseFive" << endl;
    son->parent->color = NODE_COLOR_BLACK;
    getGrandparent(son)->color = NODE_COLOR_RED;
    /* 左左结构 右旋即可 */
    if (son == son->parent->left_son)
    {
        rotatedRight(son->parent);
    }
    else
    { /* 右右结构 左旋即可 */

        rotatedLeft(son->parent);
    }
}

template <class T1, class T2>
typename RedBlackTree<T1, T2>::Node *RedBlackTree<T1, T2>::getPreNode(Node *traver)
{
    traver = traver->left_son;
    if (traver == nullptr)
        return traver;
    while (traver->right_son != nullptr)
        traver = traver->right_son;
    return traver;
}

/* 只交换结点的key value 不交换结点在树中的结构*/
template <class T1, class T2>
void RedBlackTree<T1, T2>::swapKeyAndValue(Node *a, Node *b)
{
    T1 temp_value = a->value;
    T2 temp_key = a->key;
    a->value = b->value;
    a->key = b->key;
    b->value = temp_value;
    b->key = temp_key;
}

template <class T1, class T2>
void RedBlackTree<T1, T2>::eraseAndAdjust(Node *son)
{
#ifdef DEBUG
    cout << "eraseAndAdjust" << endl;
#endif
    /* 特殊情况：删除结点是根 没有前驱结点 说明可能有右儿子且只能是红色结点 */
    if (son == root_)
    {
        root_ = son->right_son;
        if (root_ != nullptr)
            root_->color = NODE_COLOR_BLACK;
        delete son;
    }
    /* 特殊情况：这个结点是红色结点 不影响黑色平衡，且只有空儿子*/
    else if (son->color == NODE_COLOR_RED)
    {
        // cout << "???" << endl;
        if (son->parent->left_son == son)
            son->parent->left_son = nullptr;
        else
            son->parent->right_son = nullptr;
        delete son;
    }

    /* 特殊情况：被删除的结点为黑色且有左儿子 或者右儿子(因为这被删除的结点可能没有前驱结点，但是有右儿子)(红色）
    则可以用红色结点代替黑色结点并重绘红色结点为黑色*/
    else if (son->color == NODE_COLOR_BLACK && son->left_son != nullptr)
    {
        swapKeyAndValue(son, son->left_son);
        delete son->left_son;
        son->left_son = nullptr;
    }
    else if (son->color == NODE_COLOR_BLACK && son->right_son != nullptr)
    {
        swapKeyAndValue(son, son->right_son);
        delete son->right_son;
        son->right_son = nullptr;
    }
    else /* 要删除的结点是黑色结点且没有儿子
    先调整这棵删除一个黑色结点后导致树的黑色平衡被打破的树
    之后在真正删除那个需要删除的结点 根据具体情况分类讨论*/
    {
        /* 把这棵缺少一个黑色高度的树拿来调整（就是试着把兄弟树的结点匀过来一个保存黑色平衡，
        如果不行那只能把父节点这颗大树整体黑色高度减1，
        然后递归把父节点这颗大的树当做缺少一个黑色高度的树拿来调整） */
        eraseCaseOne(son);
        if (son->parent && son->parent->left_son == son)
            son->parent->left_son = nullptr;
        else
            son->parent->right_son = nullptr;

        delete son;
    }
}

/* 按兄弟结点颜色分类讨论（被删除的点一定有兄弟结点） */
template <class T1, class T2>
void RedBlackTree<T1, T2>::eraseCaseOne(Node *son)
{
#ifdef DEBUG
    cout << "eraseCaseOne" << endl;
#endif
    /* 当前需要调整的树是根 其实这个时候就不用调整了
    其实是为erase_case6特别判断的一种情况*/
    if (son == root_)
        return;
    if (getBrother(son)->color == NODE_COLOR_BLACK)
        eraseCaseTwo(son);
    else
        eraseCaseThree(son);
}

/* brother->color = NODE_COLOR_BLACK */
template <class T1, class T2>
void RedBlackTree<T1, T2>::eraseCaseTwo(Node *son)
{
#ifdef DEBUG
    cout << " eraseCaseTwo " << endl;
#endif
    Node *brother = getBrother(son);
    Node *parent = son->parent;

    /* 兄弟结点有一个儿子为红 */
    if ((brother->left_son != nullptr && brother->left_son->color == NODE_COLOR_RED) || (brother->right_son != nullptr && brother->right_son->color == NODE_COLOR_RED))
    {

        if (brother == parent->right_son)
        {
            /* 调整成brother->right_son->color = NODE_COLOR_RED 的情况 然后左旋 再根据parent颜色 是否修改brother->right_son颜色*/
            /* 情况三：brother为黑色，且其左孩子是红色结点，右孩子是黑色结点或为空。 变为情况4*/
            if (brother->right_son == nullptr || brother->right_son->color == NODE_COLOR_BLACK)
            {
                rotatedRight(brother->left_son);
                brother = brother->parent; /* 更新brother */
                brother->color = NODE_COLOR_BLACK;
                brother->right_son->color = NODE_COLOR_RED;
            }
            // if (parent->color == NODE_COLOR_BLACK)
            //       brother->right_son->color = NODE_COLOR_BLACK;
            brother->color = parent->color;
            parent->color = brother->right_son->color = NODE_COLOR_BLACK;
            rotatedLeft(brother);
        }
        else /* 对称 */
        {
            /* 调整成brother->left_son->color = NODE_COLOR_RED */
            if (brother->left_son == nullptr || brother->left_son->color == NODE_COLOR_BLACK)
            {
                rotatedLeft(brother->right_son);
                brother = brother->parent;
                brother->color = NODE_COLOR_BLACK;
                brother->left_son->color = NODE_COLOR_RED;
            }
            // if (parent->color == NODE_COLOR_BLACK)
            //     brother->left_son->color = NODE_COLOR_BLACK;
            brother->color = parent->color;
            parent->color = brother->left_son->color = NODE_COLOR_BLACK;
            rotatedRight(brother);
        }
    }
    else /* 兄弟结点左右儿子都为空 或者都是黑色*/
    {

        /*  p黑 b黑  只能让parent黑色高度 - 1 ,然后继续调整parent*/
        if (parent->color == NODE_COLOR_BLACK)
        {
            brother->color = NODE_COLOR_RED;
            eraseCaseOne(parent);
        }
        else
        {
            parent->color = NODE_COLOR_BLACK;
            brother->color = NODE_COLOR_RED;
        }
    }
}

/* brother->color = NODE_COLOR_RED
--> parent->color == brother->left_son->color = brother->right_son->color = NODE_COLOR_BLACK*/
/* 转换成兄弟结点是黑色的情况 */
template <class T1, class T2>
void RedBlackTree<T1, T2>::eraseCaseThree(Node *son)
{
#ifdef DEBUG
    cout << "erase case3" << endl;
#endif
    Node *brother = getBrother(son);
    Node *parent = brother->parent;

    if (brother == parent->right_son)
        rotatedLeft(brother);

    else
        rotatedRight(brother);

    brother->color = NODE_COLOR_BLACK;
    parent->color = NODE_COLOR_RED;
    eraseCaseTwo(son);
}

/* 求树的高度 */
template <class T1, class T2>
int RedBlackTree<T1, T2>::getHeight(Node *root_)
{
    if (root_ == nullptr)
        return 0;
    return 1 + max(getHeight(root_->left_son), getHeight(root_->right_son));
}

/* 打印这颗红黑树 */
template <class T1, class T2>
void RedBlackTree<T1, T2>::printRedBlackTree()
{
    if (root_ == nullptr)
        return;
    /*
     first:前置空格数 second:结点
     左儿子坐标 = 父结点坐标 - n/结点当前高度
     右儿子坐标 = 父节点坐标 + n/结点当前高度
    */
    vector<pair<int, Node *>> a, b;
    int n = 1 << getHeight(root_); /* 对应高度满二叉树结点个数 */
    a.push_back(pair<int, Node *>(n >> 1, root_));
    int h = 2;

    while (1)
    {
        int cnt = 0;
        for (auto it : a)
        {
            /* 前面有空缺用空格替代 */
            while (cnt < it.first)
            {
                ++cnt;
                printf("    ");
            }

            /*层序输出结点的键值 和 颜色 */

            if (it.second->color)
                printf("%3dB", it.second->key);
            else
                printf("%3dR", it.second->key);

            if (it.second->left_son)
            {
                b.push_back(pair<int, Node *>(it.first - (n >> h), it.second->left_son));
            }
            if (it.second->right_son)
            {
                b.push_back(pair<int, Node *>(it.first + (n >> h), it.second->right_son));
            }
        }
        // cout << "\n\n\n";
        ++h;
        a = b;
        b.clear();
        if (!a.size())
            break;
    }
}

/* 检查黑色平衡、指针、结点颜色，函数返回黑色高度 */
template <class T1, class T2>
int RedBlackTree<T1, T2>::checkBlackBalanceAndPointerAndColor(Node *temp)
{
    if (temp == nullptr)
        return 0;

    /* 黑色节点计数，判断黑色平衡 */
    int ct_black = 0;

    if (temp->color == NODE_COLOR_BLACK)
        ct_black = 1;

    /* 判断parent指针是否正确 */
    if (temp->left_son && temp->left_son->parent != temp)
    {
#ifdef DEBUG
        cout << temp->key << "ERROR: pointer left error: " << temp->left_son->key << endl;
#endif
        exit(-1);
    }
    if (temp->right_son && temp->right_son->parent != temp)
    {
#ifdef DEBUG
        cout << temp->key << "ERROR: pointer right error: " << temp->right_son->key << endl;
#endif
        exit(-1);
    }

    /* 判断是否有两个连续红色节点 */
    if (temp->color == NODE_COLOR_RED)
    {
        // printRedBlackTree();
        if (temp->left_son != nullptr && temp->left_son->color == NODE_COLOR_RED)
        {
#ifdef DEBUG
            cout << temp->key << "ERROR: color error with left: " << temp->left_son->key << endl;
#endif
            exit(-1);
        }
        if (temp->right_son != nullptr && temp->right_son->color == NODE_COLOR_RED)
        {
#ifdef DEBUG
            cout << temp->key << "ERROR: color error with right: " << temp->right_son->key << endl;
#endif
            exit(-1);
        }
    }

    /* 判断黑色平衡 */
    int left_black = checkBlackBalanceAndPointerAndColor(temp->left_son);

    if (left_black != checkBlackBalanceAndPointerAndColor(temp->right_son))
    {
#ifdef DEBUG
        cout < temp->key << endl;
        cout << "ER<ROR: check_Node error in color" << endl;
#endif
        exit(-1);
    }

    return ct_black + left_black;
}

/* BST中序遍历的得到的key从小到大 */
template <class T1, class T2>
void RedBlackTree<T1, T2>::checkBst(Node *root_)
{
    stack<Node *> st;
    Node *last = nullptr, *now = root_;
    while (true)
    {
        while (now != nullptr)
        {
            st.push(now);
            now = now->left_son;
        }
        if (st.size())
            now = st.top();
        else
            return;
        st.pop();
        if (last != nullptr && now->key <= last->key)
        {
#ifdef DEBUG
            cout << "EROOR: not BST" << std::endl;
#endif
            exit(-1);
        }
        last = now;
        now = now->right_son;
    }
    return;
}

/* 先找到合适位置插入，之后再根据父节点颜色判断是否进行调整 */
template <class T1, class T2>
void RedBlackTree<T1, T2>::insert(T1 key, T2 value)
{
    Node *insertNode = new Node(key, value);

    Node *traver = root_;
    while (traver)
    {
        if (key < traver->key)
        {
            if (traver->left_son)
                traver = traver->left_son;
            else
            {
                traver->left_son = insertNode;
                break;
            }
        }
        else if (key > traver->key)
        {
            if (traver->right_son)
                traver = traver->right_son;
            else
            {
                traver->right_son = insertNode;
                break;
            }
        }
        else /* 这个结点已经有过就更新 */
        {
            traver->value = value;
            delete insertNode;
            return;
        }
    }

    insertNode->parent = traver;
    insertCaseOne(insertNode);
}

/*
交换要删除的结点和要删除的结点的前驱结点
删除原来结点的前驱结点注意删除后记得给指针置为nullptr
*/
template <class T1, class T2>
bool RedBlackTree<T1, T2>::erase(T1 key)
{
    Node *traver = root_;

    while (traver)
    {
#ifdef DEBUG
        cout << traver->key << endl;
#endif
        if (key < traver->key)
            traver = traver->left_son;
        else if (traver->key < key)
            traver = traver->right_son;
        else
            break;
    }

    /* 没有找到要删除的结点 */
    if (traver == nullptr)
        return false;

    /* 获得前驱结点 */
    Node *preNode = getPreNode(traver);

    /* 将前驱结点和要删除结点的值交换，问题变为删除这个点的前驱结点
    如果没有前驱结点删除自身*/
    if (preNode)
        swapKeyAndValue(traver, preNode);
    else
        preNode = traver;

    eraseAndAdjust(preNode);
    return true;
}

template <class T1, class T2>
T2 *RedBlackTree<T1, T2>::getValue(T1 key)
{
    Node *traver = root_;
    while (traver)
    {
        if (key < traver->key)
            traver = traver->left_son;
        else if (key > traver->key)
            traver = traver->right_son;
        else
            return traver->value;
    }
    return nullptr;
}

template <class T1, class T2>
typename RedBlackTree<T1, T2>::Node *RedBlackTree<T1, T2>::getNode(T1 key)
{
    Node *traver = root_;
    while (traver)
    {
        if (key < traver->key)
            traver = traver->left_son;
        else if (key > traver->key)
            traver = traver->right_son;
        else
            return traver;
    }
    return nullptr;
}
/* 判断红黑树的正确性 */
template <class T1, class T2>
void RedBlackTree<T1, T2>::checkRedBlackTree()
{
    /* 判断是否是BST */
    checkBlackBalanceAndPointerAndColor(root_);
    /* 判断红黑树其他要求 */
    checkBst(root_);
    if (root_ != nullptr && root_->color == NODE_COLOR_RED)
    {
#ifdef DEBUG
        cout << "ERROR: root_ color is  not black" << std::endl;
#endif
        exit(-1);
    }
}