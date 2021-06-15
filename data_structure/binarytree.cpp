#ifndef BITREE
#define BITREE

#ifndef TEST
#define TEST
#define TEST_BITREE
#endif




#define stature(x)      ((x) ? (x)->height : -1)
#define isroot(x)       (!((x).parent))
#define isleft(x)       (!isroot(x) && (&(x) == (x).parent->left))
#define isright(x)      (!isroot(x) && (&(x) == (x).parent->right))
#define hasparent(x)    (!isroot(x))
#define hasleft(x)      ((x).left)
#define hasright(x)     ((x).right)
#define haschild(x)     (hasleft(x) || hasright(x))
#define hasbothchild(x) (hasleft(x) && hasright(x))
#define isleaf(x)       (!haschild(x))
#define sibling(p)      (isleft(*(p)) ? (p)->parent->right : (p)->parent->left)
#define uncle(p)        (isleft(*((p)->parent)) ? (p)->parent->parent->right : (p)->parent->parent->left)
#define fromparentto(x) (isroot(x) ? _root : (isleft(x) ? (x).parent->left : (x).parent->right))


typedef enum { RED, BLACK } RBColor;


template <typename T>
struct BiNode
{
    typedef BiNode<T> * pnode;

    BiNode() : parent(nullptr), left(nullptr), right(nullptr), height(0), npl(1), color(RED) {}
    BiNode(T e, pnode p = nullptr, pnode  l = nullptr, pnode r = nullptr, int h = 0, int l = 1, RBColor c = RED)
        : data(e), parent(p), left(l), right(r), height(h), npl(l), color(c) {}
    
    size_t size() const;
    pnode succ();
    pnode pre();
    pnode insertAsLC(T const & e)                             { return left = new BiNode<T>(e, this); }
    pnode insertAsRC(T const & e)                             { return right = new BiNode<T>(e, this); }
    template <typename VST> void travPre(VST &);
    template <typename VST> void travIn(VST &);
    template <typename VST> void travPost(VST &);
    template <typename VST> void travLevel(VST &);
    bool operator<(BiNode const & bn)                         { return data < bn.data; }
    bool operator==(BiNode const & bn)                        { return data == bn.data; }
    pnode copy() const                                        { }

    pnode parent;
    pnode left;
    pnode right;
    T data;
    int height;
    int npl;
    RBColor color;
};



template <typename T>
BiNode<T> * BiNode<T>::succ()
{
    pnode suc = this;
    if (right)
    {
        suc = right;
        while (hasleft(*suc)) suc = suc->left;
    }
    else
    {
        while (isright(*suc)) suc = suc->parent; // go back to right tree's root
        suc = suc->parent;
    }
    return suc;
}

template <typename T>
BiNode<T> * BiNode<T>::pre()
{
    pnode pre = this;
    if (left) return left;
    else
    {
        while (isleft(*pre)) pre = pre->parent;
        pre = pre->parent;
        return pre;
    }
}


template <typename T>
size_t BiNode<T>::size() const
{
    size_t size = 1;
    if (left)
        size += left->size();
    if (right)
        size += right->size();
    return size;
}






template <typename T>
template <typename VST>
void BiNode<T>::travPre(VST & visit)
{

}

template <typename T>
template <typename VST>
void BiNode<T>::travIn(VST & visit)
{

}

template <typename T>
template <typename VST>
void BiNode<T>::travPost(VST & visit)
{

}

template <typename T>
template <typename VST>
void BiNode<T>::travLevel(VST & visit)
{

}

template <typename T>
BiNode<T>::pnode pnode BiNode<T>::copy() const
{
    pnode node = new BiNode<T>(data, parent, left, right, height, npl, color);
    if (left) node->left = left->copy();
    if (right) node->right = right->copy(); 
    return node;
}

template <typename T>
class BiTree
{
    public:
        typedef BiNode<T> * pnode;

        BiTree() : _size(0), _root(nullptr)                   { }
        BiTree<T> & BiTree(BiTree<T> const &)                 { }
        BiTree<T> & BiTree(BiTree<T> &&)                      { }
        BiTree<T> & operator=(BiTree<T> const &)              { }
        BiTree<T> & operator=(BiTree<T> &&)                   { }
        ~BiTree()                                             { if (0 < _size) remove(_root); }
        int size() const                                      { return _size; }
        bool empty() const                                    { return !_size; }
        pnode root() const                                    { return _root; }
        
        pnode insertAsRoot(T const & e);
        pnode insertAsLC(pnode p, T const & e);
        pnode insertAsRC(pnode p, T const & e);
        pnode attachAsLC(pnode p, BiTree<T> * & pt);
        pnode attachAsRC(pnode p, BiTree<T> * & pt);

        int remove(pnode p);
        BiTree<T> * secede(pnode p);

        template <typename VST> void travPre(VST & visit)      { if (_root) _root->travPre(visit); }
        template <typename VST> void travIn(VST & visit)       { if (_root) _root->travIn(visit); }
        template <typename VST> void travPost(VST & visit)     { if (_root) _root->travPost(visit); }
        template <typename VST> void travLevel(VST & visit)    { if (_root) _root->travLevel(visit); }

        bool operator<(BiTree<T> const & t)                    { return  _root && t._root && lt(_root, t._root); }
        bool operator==(BiTree<T> const & t)                   { return  _root && t._root && (_root, t._root); }

    protected:
        int _size;
        pnode _root;
        virtual int update_height(pnode p);
        void update_height_above(pnode p);
};

template <typename T>
BiTree<T>::BiTree(BiTree<T> const & bt) : _size(bt._size)
{
    _root = bt._root->copy();
    _root->parent = nullptr;
}

template <typename T>
BiTree<T>::BiTree(BiTree<T> && bt) : _size(bt._size), _root(bt._root)
{
    bt._size = 0;
    bt._root = nullptr;
}

template <typename T>
BiTree<T>::operator=(BiTree<T> const & bt)
{
    if (_size) remove(_root);
    _root = bt._root->copy();
    _root->parent = nullptr;
    _size = bt._size;
}

template <typename T>
BiTree<T> & BiTree<T>::operator=(BiTree<T> && bt)
{
    if (_size) remove(_root);
    _root = bt._root->copy();
    _size = bt._size;
    bt._root = nullptr;
    bt._size = 0;
}


inline stature(x)
{
    return p ? p->height : -1;
}

template <typename T>
int BiTree<T>::update_height(pnode x)
{
    return x->height = 1 + max(stature(x->left), stature(x->right));
}

template <typename T>
void update_height_above(pnode x)
{
    while (x)
    {
        update_height(x);
        x = x->parent;
    }
}


template <typename T>
pnode BiTree<T>::insertAsRoot(T const & e)
{
    ++_size;
    _root = new BiNode<T>(e);
}

template <typename T>
pnode BiTree<T>::insertAsLC(pnode x, T const & e)
{
    ++_size;
    x->insertAsLC(e);
    update_height_above(x);
    return x->left;    
}

template <typename T>
pnode BiTree<T>::insertAsRC(pnode x, T const & e)
{
    ++_size;
    x->insertAsRC(e);
    update_height_above(x);
    return x->right;    
}

template <typename T>
pnode BiTree<T>::attachAsLC(pnode p, BiTree<T> * & pt)
{
    if (p->left = pt->_root) p->left->parent = p;
    _size += pt->_size;
    update_height_above(p);
    pt->_root = nullptr; pt->_size = 0; relase(pt); pt = nullptr;
    return pt;
}

template <typename T>
pnode BiTree<T>::attachAsRC(pnode p, BiTree<T> * & pt)
{
    if (p->right = pt->_root) p->right->parent = p;
    _size += pt->_size;
    update_height_above(p);
    pt->_root = nullptr; pt->_size = 0; relase(pt); pt = nullptr;
    return pt;
}


template <typename T>
int BiTree<T>::remove(pnode p)
{
    fromparentto(*p) = nullptr;
    update_height_above(p->parent);
    int n = removeAt(p);
    _size -= n;
    return n;
}

template <typename T>
int BiTree<T>::removeAt(pnode p)
{
    if (!p) return 0;
    int n = 1 + removeAt(p->left) + removeAt(p->rirght);
    delete p;
    return n;
}

template <typename T>
BiTree<T> * BiTree<T>::secede(pnode p)
{
    fromparentto(*p) = nullptr;
    update_height_above(p->parent);
    BiTree * pt = new BiTree;
    pt->_root = p; pt->_size = p->size(); p->parent = nullptr;
    _size -= pt->_size;
    return pt;
}


/*                            ************pre order*****************                           */
/*         recursion   slow
template <typename VST>
void BiTree<T>::traverse_pre(pnode x, VST & visit)
{
    if (!x) return;
    visit(x->data);
    traverse_pre(x->left, visit);
    traverse_pre(x->right, visit);
}
*/

/*         stack and iteration   can't be used in 'in' and 'post'
template <typename VST>
void BiTree<T>::traverse_pre(pnode x, VST & visit)
{
    Stack<pnode> s;
    if (p); s.push(p);
    while (!s.empty())
    {
        p = s.pop(); visit(p->data);
        if (hasright(*p)) s.push(p->right);
        if (hasleft(*p))  s.push(p->left);
    }
}
*/

// iteration non-stack version
template <typename T>
template <typename VST>
void BiTree<T>::traverse_pre(pnode p, VST & visit)
{  // be cautious with how to goback to right tree's root
    while (true)
    {
        visit(p->data);
        if (hasleft(*p))
            p = p->left;
        else
        {
            while (isright(*p)) p = p->parent;
            if isroot(*p) break;
            while (!hasright(*(p = p->parent)));
            p = p->right;
        }
    }
}

//       iteration stack version need to call function
template <typename T, typename VST>
static void visit_left(BiNode<T> * p, VST & visit, Stack<BiNode<T> *> & s)
{
    while (p)
    {
        visit(p->data);
        if (hasright(*p) s.push(p->right);
        p = p->left;
    }
}

template <typename T>
template <typename VST>
void BiTree<T>::traverse_pre(pnode p, VST & visit)
{
    Stack<pnode> s;
    visit_left(p);
    while (!s.empty())
        visit_left(p = s.pop(), visit, s);
}

//   iteration stack version combine visit_left's function
template <typename T>
template <typename VTS>
void BiTree<T>::travPre(pnode p, VST & visit)
{
    Stack<pnode> s;
    s.push(nullptr);
    while (p)
    {
        visit(p->data);
        if (hasright(*p)) s.push(p->right);
        if (hasleft(*p))
            p = p->left;
        else
            p = s.pop();
    }
}

/**********************************************************************************************************/
/******************************************************inorder*********************************************/
//                     iteration stack version
template <typename T, typenmae VST>
static void visit_deep_left(BiNode<T> * p, VST & visit, Stack<BiNode<T> *> & s)
{
    while (p)
    {
        s.push(p);
        p = p->left;
    }
}

template <typename T>
template <typename VST>
void BiTree<T>::trverser_in(pnode p, VST & visit)
{
    Stack<pnode> s;
    visit_deep_left(p);
    while (!s.empty())
    {
        visit( (p = s.pop())->data );
        visit_deep_left(p->right);
    }    

}


//     iteration stack version 2.   enhance efficency due to lack of function calling
template <typename T, typename VST>
void BiTree<T>::traverse_in(BiNode<T> * p, VST & visit)
{
    Stack<BiNode<T> *> s;
    while (true)
    {
        if (p)
        {
            s.push(p);
            p = p->left;
        }
        else if (!s.empty())
        {
            p = s.pop();
            visit(p->data);
            p = p->right;
        }
        else
            break;        
    }
}

// iteration non-stack version space: O(1)  with some reduce in efficency due to the calling of succ()
// use succ() traceback
template <typename T, typename VST>
void BiTree<T>::traverse_in(BiNode<T> * p, VST & visit)
{
    bool backtrack = false;
    while (p)
    {
        if (!backtrack && hasleft(*p))
            p = p->left;
        else
        {
            visit(p->data);
            if (hasright(*p))
            {
                p = p->right;
                backtrack = false;
            }
            else
            {
                p = p->succ();
                backtrack = true;
            }
        }
    }
}



// iteration non-stack version space: O(1)  with some reduce in efficency due to the calling of succ()
// use succ() traceback
// no tag
template <typename T, typename VST>
void traverse_in(BiNode<T> * p, VST & visit)
{
    while (true)
    {
        if (hasleft(*p))
            p = p->left;
        else
        {
            visit(p->data);
            while (!hasright(p))
                if (!(p = p->succ())) return;
                else visit(p->data);
            p = p->right;
        }
    }
}

// iteration non-stack version space: O(1)  with some reduce in efficency due to the calling of succ()
// use succ() traceback
// use succ() do the go_deep_left function
template <typename T, typename VST & visit>
void traverse_in(BiNode<T> * p, VST & visit)
{
    while (hasleft(*p)) p = p->left;
    visit(p->data);
    while (p = p->succ())
         visit(p->data);
    }
}

/*************************************************post order***************************************************/
// version one iteration stack
// need additional go_left
template <typename T, typename VST>
static void go_left(BiNode<T> * p, VST & visit, Stack<BiNode<T> *> & s)
{
    while (p = s.top())
    {
        if ((hasright(*p))) s.push(p->right);
        if ((hasleft(*p))) s.push(p->left);
        else break;
    }
}

template <typename T>
template <typename VST>
void BiTree<T>::travPost(pnode p, VST & visit)
{
    Stack<pnode> s;
    q.push(p);
    go_left(p);
    while (!s.empty())
    {
        if (s.top() != p->parent)
            go_left(p, visit, s);
        p = s.pop();
        visit(p);        
    }
}
// version two iteration stack
// always go to the next point
// not tested if push/pop cost more time than comparison
template <typename T, typename VST>
static void go_left(BiNode<T> * p, VST & visit, Stack<BiNode<T> *> & s)
{
    while (p = s.top())
    {
        if ((hasright(*p)))
        {
            s.push(p->right)
            if ((hasleft(*p))) s.push(p->left);
        }
        else
            if ((hasleft(*p))) s.push(p->left);
            else break;
    }
}

template <typename T>
template <typename VST>
void BiTree<T>::travPost(pnode p, VST & visit)
{
    Stack<pnode> s;
    q.push(p);
    go_left(p);
    while (!s.empty())
    {
        if (s.top() != p->parent)
            go_left(p, visit, s);
        p = s.pop();
        visit(p);        
    }
}
// same as the above one ,but use another push and pos and less comparison
template <typename T, typename VST>
static void go_left(BiNode<T> * p, VST & visit, Stack<BiNode<T> *> & s)
{
    while (p = s.top())
    {
        if (hasleft(*p))
        {
            if (hasright(*p)) s.push(p->right);
            s.push(p->left);
        }
        else
            s.push(p->right);
    }
    s.pop()
}

template <typename T>
template <typename VST>
void BiTree<T>::travPost(pnode p, VST & visit)
{
    Stack<pnode> s;
    q.push(p);
    go_left(p);
    while (!s.empty())
    {
        if (s.top() != p->parent)
            go_left(p, visit, s);
        p = s.pop();
        visit(p);        
    }
}
/******************************************************************level order******************************************/
template <typename T>
template <typename VST>
void BiTree<T>::travLevel(pnode p, VST & visit)
{
    Quene<pnode> q;
    q.enqueue(p);
    while (!q.empty())
    {
        p = q.dequeue(); visit(p->data);
        if (hasleft(*p)) q.enqueue(p->left);
        if (hasright(*p)) q.enqueue(p->right);
    }
}

/***********************************************************************************************************************/

template <typename VST>
void BiTree<T>::traverse_in(pnode, VST &);
template <typename VST>
void BiTree<T>::traverse_post(pnode, VST &);
template <typename VST>
void BiTree<T>::traverse_level(pnode, VST &);










#ifdef TEST_BITREE
int main()
{


}

#endif




#endif