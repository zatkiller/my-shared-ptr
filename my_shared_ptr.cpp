#include <bits/stdc++.h>

using namespace std;

template<typename T>
class SharedPtr {
public:
    T* ptr;
    int* refCount;

    SharedPtr() : ptr(nullptr), refCount(new int(1)) {}
    SharedPtr(T* ptr) : ptr(ptr), refCount(new int(1))  {}

    ~SharedPtr() {
        if (refCount != nullptr) {
            --(*refCount);
            if(!(*refCount)) {
                delete ptr;
                delete refCount;
            }
        }
    }

    SharedPtr(const SharedPtr &p) : ptr(p.ptr), refCount(p.refCount) {
        ++(*refCount);
    }

    SharedPtr& operator=(const SharedPtr &p) {
        if (&p == this)
            return *this;

        ptr = p.ptr;
        refCount = p.refCount;
        ++(*refCount);
        return *this;
    }

    SharedPtr(SharedPtr &&p) : ptr(p.ptr), refCount(p.refCount) {
        p.ptr = nullptr;
        p.refCount = nullptr;
    }

    SharedPtr& operator=(SharedPtr &&p) {
        if (&p == this)
            return *this;

        ptr = p.ptr;
        refCount = p.refCount;

        p.ptr = nullptr;
        p.refCount = nullptr;

        return *this;
    }

    T* getPtr() {
        return ptr;
    }

    int getCount() {
        return *refCount;
    }

    void print() {
        if (!refCount || !ptr) {
            cout << "NULL" << endl;
        } else {
            cout << *ptr << endl;
            cout << "COUNT " << *refCount << endl;
        }
    }
};

int main() {

    int* x = new int(5);
    SharedPtr<int> sp1(x);
    SharedPtr<int> sp2(move(sp1));

    assert(sp1.getPtr() == nullptr);
    assert(sp2.getPtr() == x);
    assert(sp2.getCount() == 1);

    {
        SharedPtr<int> sp3;
        sp3 = sp2;
        assert(sp2.getCount() == 2);
        assert(sp3.getPtr() == x);
        assert(sp3.getCount() == 2);
    }
    
    assert(sp2.getCount() == 1);
    
    {
        SharedPtr<int> sp4(sp2);
        assert(sp2.getCount() == 2);
        assert(sp4.getPtr() == x);
        assert(sp4.getCount() == 2);
    }

    {
        SharedPtr<int> sp6;
        sp6 = move(sp2);

        assert(sp2.getPtr() == nullptr);
        assert(sp6.getPtr() == x);
        assert(sp6.getCount() == 1);
    }

    return 0;
}