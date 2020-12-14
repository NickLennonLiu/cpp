#include <stdio.h>
using namespace std;

/*
宏的定义以及AVL接口的实现参考了DSA第10章(高级搜索树)中的内容
*/

#define isRChild(x) (!isRoot(x) && (&(x) == (x).parent->rc))
#define isLChild(x) (!isRoot(x) && (&(x) == (x).parent->lc))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define stature(x) ((x) ? (x)->height : -1)
#define isRoot(x) (!((x).parent))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define sibling(x) (((x)->parent->lc == (x)) ? (x)->parent->rc : (x)->parent->lc)
#define IsBlack(x) (!(x) || (x)->color == BLACK)
#define IsRed(x) (!IsBlack(x))

#define BlackHeightUpdated(x) (/*RedBlack高度更新条件*/          \
        (stature((x).lc) == stature((x).rc)) && \
        ((x).height == (IsRed(&x) ? stature((x).lc) : stature((x).lc) + 1)))
#define FromParentTo(x) /*来自父亲的引用*/ \
    (isRoot(x) ? root : (isLChild(x) ? (x).parent->lc : (x).parent->rc))

typedef enum {RED, BLACK} RBColor;

struct node
{
    int val;
    int height;
    RBColor color;
    node *parent, *lc, *rc;
    node()
        : parent(nullptr), lc(nullptr), rc(nullptr), height(0), val(0)
    {
    }
    node(const int &e, node *p)
        : parent(p), lc(nullptr), rc(nullptr), height(0), val(e)
    {
    }
    node *insertAsLC(const int &e)
    {
        return lc = new node(e, this);
    }
    node *insertAsRC(const int &e)
    {
        return rc = new node(e, this);
    }
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
    int updateHeight(node *x)
    {
        int h = -1;
        if (x->lc)
            h = MAX(h, x->lc->height);
        if (x->rc)
            h = MAX(h, x->rc->height);
        return x->height = 1 + h;
    }

    void updateHeightAbove(node *x)
    {
        while (x)
        {
            updateHeight(x);
            x = x->parent;
        }
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
        updateHeight(a);
        updateHeight(b);
        updateHeight(c);
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
        return max;
    }
};

int BST::pred_or_succ = 1;

class RedBlack : public BST
{
protected:
    void solveDoubleRed(node* x)
    {
        while(x->parent && x->parent->color == RED)
        {
            node* p = x->parent;
            node* g = p->parent;
            node* u = sibling(p);
            if(IsBlack(u)) {
                if(isLChild(*x) == isLChild(*p))
                    p->color = BLACK;
                else
                    x->color = BLACK;
                g->color = RED;
                node* gg = g->parent;
                node*& pp = FromParentTo(*g);
                pp = rotateAt(x);
                pp->parent = gg;
            } else {
                p->color = BLACK;
                u->color = BLACK;
                if(g->parent)
                    g->color = RED;
                x = g;
            }
        }
        if(!x->parent)
        {
            x->color = BLACK;
            return;
        }
    }
    void solveDoubleBlack(node *r)
    {
        node* p = r ? r->parent : _hot;
        if(!p)
            return;
        node* s = sibling(r);
        if(IsBlack(s))
        {
            node* t = nullptr;
            if(IsRed(s->rc)) t = s->rc;
            if(IsRed(s->lc)) t = s->lc;
            if(t) {
                RBColor ocolor = p->color;
                node*& b = FromParentTo(*p);
                b = rotateAt(t);
                if(HasLChild(*b))
                {
                    b->lc->color = BLACK;
                    updateHeight(b->lc);
                }
                if(HasRChild(*b))
                {
                    b->rc->color = BLACK;
                    updateHeight(b->rc);
                }
                b->color = ocolor;
                updateHeight(b);
            } else {
                s->color = RED;
                s->height--;
                if(IsRed(p))
                {
                    p->color = BLACK;
                } else {
                    p->height--;
                    solveDoubleBlack(p);
                }
            }
        } else {
            s->color = BLACK;   p->color = RED;
            node* t = isLChild(*s) ? s->lc : s->rc;
            _hot = p;
            node*& b = FromParentTo(*p);
            b = rotateAt(t);
            solveDoubleBlack(r);
        }
    }
    int updateHeight(node* x)
    {
        x->height = MAX(stature(x->lc),stature(x->rc));
        if(IsBlack(x)) x->height++;
        return x->height;
    }
public:
    node* insert(const int& e)
    {
        node*& x = search(e);
        if(x)
            return x;
        x = new node(e, _hot);
        x->color = RED;
        node* xold = x;
        solveDoubleRed(x);
        return xold;
    }
    bool remove(const int e)
    {
        node*& x = search(e);
        if(!x) return false;
        RBColor xcolor = x->color;
        node* r = removeAt(x, _hot);
        if(!r) return true; // 若树空
        if(!_hot){          // 若删根
            root->color = BLACK;
            updateHeight(root);
            return true;
        }
        if(BlackHeightUpdated(*_hot)) return true;  // 若均衡
        if(IsRed(r))    // 若r红
        {
            r->color = BLACK;
            r->height ++;
            return true;
        }
        solveDoubleBlack(r);    // r,p双黑
        return true;
    }
};

RedBlack rb;
int n;

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
            rb.insert(peach);
            break;
        case 'B':
            rb.remove(peach);
            break;
        case 'C':
            p = rb.find(peach);
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