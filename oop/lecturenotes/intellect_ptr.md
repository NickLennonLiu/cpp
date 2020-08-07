# 智能指针与引用计数

> A、B对象共享一个C对象，C不想交由外部销毁  
> 应当在A、B都销毁时C才能销毁  
> 如何自动处理？

## 智能指针

**shared_ptr**  \<memory\>库
```cpp
#include <memory>
shared_ptr<int> p1(new int(1));
shared_ptr<MyClass> p2 = make_shared<MyClass>(2);
shared_ptr<MyClass> p3 = p2;
shared_ptr<int> p4;

int x = *p1;
int y = p2->val;

// p2和p3指向同一对象，当两者均出作用域才会被销毁！

```

## 引用计数

智能指针依靠**引用计数**来判断何时销毁对象

```cpp
#include <memory>
#include <iostream>
using namespace std;
int main()
{
	shared_ptr<int> p1(new int(4));
	cout << p1.use_count() << ' '; // 1
	{
		shared_ptr<int> p2 = p1;
		cout << p1.use_count() << ' '; // 2
		cout << p2.use_count() << ' '; // 2
	}	//p2出作用域
	cout << p1.use_count() << ' '; // 1
}
```

### 实现自己的引用计数
> 哪个男孩不想拥有属于自己的引用计数呢？

```cpp
template <typename T>
class SmartPtr;

template <typename T>
class U_Ptr {
private:
    friend class SmartPtr<T>;
    U_Ptr(T *ptr) : p(ptr), count(1) {}
    ~Uptr() { delete p;}

    int count;  // 引用计数
    T *p;   // 实际数据存放
};

class SmartPtr {
    U_Ptr *rp;
public:
    // 构造函数：初始化成员辅助指针rp，将类型T的数据存放给rp
    SmartPtr(T *ptr) :rp(new U_Ptr<T>(ptr)) {}
    // 拷贝构造函数：先初始化rp为来源rp，并将rp的计数+1
    SmartPtr(const SmartPtr<T> &sp) :rp(sp.rp) {
        ++rp->count;
    }
    // 赋值运算符：将原先的引用计数-1，如果为0则删除；再换新的rp
    SmartPtr& operator=(const SmartPtr<T>& rhs) {
        ++rhs.rp->count;
        if(--rp->count == 0)
            delete rp;
        rp = rhs.rp;
        return *this;
    }
    // 析构
    ~SmartPtr() {
        if (--rp->count == 0)
            delete rp;
    }
    T& operator *() {return *(rp->p); }
    T* operator ->() {return rp->p;}
};

int main(int argc, char *argv[]) {
    int *pi = new int(2);
    SmartPtr<int> ptr1(pi);
    SmartPtr<int> ptr2(ptr1);
    SmartPtr<int> ptr3(new int(3));
    ptr3 = ptr2;
    cout << *ptr1 << endl;  // 2
    *ptr1 = 20;
    cout << *ptr2 << endl;  // 20

    return 0; 
}

```

## shared_ptr的其他用法

```cpp
p.get() //获取裸指针
p.reset() // 清除指针并减少引用次数
static_pointer_cast<int>(p)
dynamic_pointer_cast<Base>(p)
```

注意！
- 不能使用同一个裸指针初始化多个智能指针，会产生多个辅助指针！
- 不能直接使用智能指针维护**对象数组**  
  因为删除数组需要delete[], 而智能指针所有的实现都是delete p;

## 智能指针并不总是智能的

当出现环状结构（如两个对象互相用智能指针指向对方）时，对象不能够正确地销毁

### How to fix this?

- 弱引用 **weak_ptr**     **指向对象但不计数**
  ```cpp
  shared_ptr<int> sp(new int(3));
  weak_ptr<int> wp1 = sp;

  //Usage:
  wp.use_count()
  wp.reset()    // 释放指针
  wp.expired()  // 检查对象是否无效
  sp = wp.lock()    // 从弱引用获得一个智能指针
  ```
- 独占所有权 **unique_ptr 保证对象只被一个指针引用**
  ```cpp
  auto up1 = std::make_unique<int>(20);
  unique_ptr<int> up2 = std::move(up1); // 可以移动unique指针(移交控制权)
  int *p = up2.release();               // 放弃指针控制权，返回裸指针
  delete p;
  ```

## 智能指针总结

### 优点
- 可以帮助管理内存，避免内存泄漏
- 区分unique_ptr和shared_ptr能够明确语义
- 在手动维护指针不可行，复制对象开销太大时，智能指针是唯一选择

### 缺点
- 引用计数会影响性能
- 智能指针不总是智能，需要了解内部原理
- 需要小心环状结构和数组指针