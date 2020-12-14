#include <cstdio>

#define isRChild(x) (!isRoot(x) && (&(x) == (x).parent->rc))
#define isLChild(x) (!isRoot(x) && (&(x) == (x).parent->lc))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define isRoot(x) (!((x).parent))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

struct node
{
    int val;
    node *parent, *lc, *rc;
    node()
        : parent(nullptr), lc(nullptr), rc(nullptr), val(0)
    {}
    node(const int &e, node *p = nullptr, node *lc = nullptr, node *rc = nullptr)
        : parent(p), lc(lc), rc(rc), val(e)
    {}
    node *succ()
    {
        node *s = this;
        if (rc)
        {
            s = rc;
            while (s->lc)
                s = s->lc;
        }
        else
        {
            while (isRChild(*s))
                s = s->parent;
            s = s->parent;
        }
        return s;
    }
    node *pred()
    {
        node *s = this;
        if (lc)
        {
            s = lc;
            while (s->rc)
                s = s->rc;
        }
        else
        {
            while (isLChild(*s))
                s = s->parent;
            s = s->parent;
        }
        return s;
    }
};

class BST
{
    static int pred_or_succ;

public:
    node *root;
    node *_hot;
    BST()
        : root(nullptr), _hot(nullptr)
    {
    }
    node *&search(const int &e)
    {
        if (!root || (root->val == e))
        {
            return root;
        }
        _hot = root;
        while (1)
        {
            node *&c = (e < _hot->val) ? _hot->lc : _hot->rc;
            if (!c || (e == c->val))
                return c;
            _hot = c;
        }
    }

    node *removeAt(node *&x, node *&hot)
    {
        node *w = x;          // 实际被删除的节点
        node *succ = nullptr; // 实际被删除节点的接替者
        if (!HasLChild(*x))
            succ = x = x->rc;
        else if (!HasRChild(*x))
            succ = x = x->lc;
        else
        {
            // 随机选取后继或者前驱作为实际被删除的节点。
            if (++pred_or_succ & 1)
            {
                w = w->succ();
                int temp = x->val;
                x->val = w->val;
                w->val = temp;
                node *u = w->parent;
                ((u == x) ? u->rc : u->lc) = succ = w->rc;
            }
            else
            {
                w = w->pred();
                int temp = x->val;
                x->val = w->val;
                w->val = temp;
                node *u = w->parent;
                ((u == x) ? u->lc : u->rc) = succ = w->lc;
            }
        }
        hot = w->parent;
        if (succ)
            succ->parent = hot;
        delete w;
        return succ;
    }

    node *connect34(node *a, node *b, node *c,
                    node *t0, node *t1, node *t2, node *t3)
    {
        a->lc = t0;
        if (t0)
            t0->parent = a;
        a->rc = t1;
        if (t1)
            t1->parent = a;
        c->lc = t2;
        if (t2)
            t2->parent = c;
        c->rc = t3;
        if (t3)
            t3->parent = c;
        b->lc = a;
        a->parent = b;
        b->rc = c;
        c->parent = b;
        return b;
    }
    node *rotateAt(node *v)
    {
        node *p = v->parent;
        node *g = p->parent;
        if (isLChild(*p))
        {
            if (isLChild(*v))
            {
                p->parent = g->parent;
                return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
            }
            else
            {
                v->parent = g->parent;
                return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
            }
        }
        else
        {
            if (isLChild(*v))
            {
                v->parent = g->parent;
                return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
            }
            else
            {
                p->parent = g->parent;
                return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
            }
        }
    }
};

class Splay : public BST
{
protected:
    inline void attachAsLChild(node* p, node* lc)
    {
        p->lc = lc;
        if(lc) lc->parent = p;
    }
    inline void attachAsRChild(node* p, node* rc)
    {
        p->rc = rc;
        if(rc) rc->parent = p;
    }
    node* splay(node* v)
    {
        if(!v) return nullptr;
        node *p, *g;
        while((p = v->parent) && (g = p->parent)) {
            node *gg = g->parent;
            if(isLChild(*v)) {
                if(isLChild(*p))    // zig-zig
                {
                    attachAsLChild(g, p->rc);
                    attachAsLChild(p, v->rc);
                    attachAsRChild(p, g);
                    attachAsRChild(v, p);
                }
                else                // zig-zag
                {
                    attachAsLChild(p, v->rc);
                    attachAsRChild(g, v->lc);
                    attachAsLChild(v, g);
                    attachAsRChild(v, p);
                }
            } else {
                if(isRChild(*p))    // zag-zag
                {
                    attachAsRChild(g, p->lc);
                    attachAsRChild(p, v->lc);
                    attachAsLChild(p, g);
                    attachAsLChild(v, p);
                }
                else                // zag-zig
                {
                    attachAsRChild(p, v->lc);
                    attachAsLChild(g, v->rc);
                    attachAsRChild(v, g);
                    attachAsLChild(v, p);
                }
            }
            if(!gg) 
                v->parent = nullptr;
            else {
                if(g == gg->lc)
                    attachAsLChild(gg,v);
                else
                    attachAsRChild(gg,v);
            }
        }
        if(p = v->parent)
        {
            if (isLChild(*v))
            {
                attachAsLChild(p, v->rc);
                attachAsRChild(v, p);
            }
            else
            {
                attachAsRChild(p, v->lc);
                attachAsLChild(v, p);
            }
        }
        v->parent = nullptr;
        return v;
    }
public:
    Splay() : BST()
    {}
    node*& search(const int& e)
    {
        node* p = BST::search(e);
        root = splay(p ? p : _hot);
        return root;
    }
    node *find(const int &e)
    {
        node *cur = root;
        node *max = nullptr;
        while (cur)
        {
            if (cur->val > e)
                cur = cur->lc;
            else
            {
                max = cur;
                cur = cur->rc;
            }
        }
        if(max || cur) root = splay(max ? max : cur);
        return max;
    }
    node* insert(const int& e)
    {
        if (!root)
        {
            return root = new node(e);
        } //处理原树为空的退化情况
        if (e == search(e)->val)
            return root; //确认目标节点不存在
        node* t = root; //创建新节点。以下调整<=7个指针以完成局部重构
        if (root->val < e)
        {                                                          //插入新根，以t和t->rc为左、右孩子
            t->parent = root = new node(e, NULL, t, t->rc); //2 + 3个
            if (HasRChild(*t))
            {
                t->rc->parent = root;
                t->rc = NULL;
            } //<= 2个
        }
        else
        {                                                          //插入新根，以t->lc和t为左、右孩子
            t->parent = root = new node(e, NULL, t->lc, t); //2 + 3个
            if (HasLChild(*t))
            {
                t->lc->parent = root;
                t->lc = NULL;
            } //<= 2个
        }
        return root;         //新节点必然置于树根，返回之
    }
    bool remove(const int& e)
    {
        if (!root || (e != search(e)->val))
            return false;         //若树空或目标不存在，则无法删除
        node* w = root; //assert: 经search()后节点e已被伸展至树根
        if (!HasLChild(*root))
        { //若无左子树，则直接删除
            root = root->rc;
            if (root)
                root->parent = NULL;
        }
        else if (!HasRChild(*root))
        { //若无右子树，也直接删除
            root = root->lc;
            if (root)
                root->parent = NULL;
        }
        else
        { //若左右子树同时存在，则
            node* lTree = root->lc;
            lTree->parent = NULL;
            root->lc = NULL; //暂时将左子树切除
            root = root->rc;
            root->parent = NULL; //只保留右子树
            search(w->val);      //以原树根为目标，做一次（必定失败的）查找
                                  ///// assert: 至此，右子树中最小节点必伸展至根，且（因无雷同节点）其左子树必空，于是
            root->lc = lTree;
            lTree->parent = root; //只需将原左子树接回原位即可
        }
        delete w;
        return true;             //返回成功标志
    }
};

int n;
Splay tree;

int main()
{
    scanf("%d", &n);
    while (n--)
    {
        char op;
        int peach;
        scanf(" %c %d", &op, &peach);
        node *p;
        switch (op)
        {
        case 'A':
            tree.insert(peach);
            break;
        case 'B':
            tree.remove(peach);
            break;
        case 'C':
            p = tree.find(peach);
            if (!p)
                printf("-1\n");
            else
                printf("%d\n", p->val);
            break;
        default:
            break;
        }
    }
    return 0;
}