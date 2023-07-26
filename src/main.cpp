#include <iostream>

class A {
public:
    virtual void vfunc1() { printf("A::vfunc1\n"); }
    virtual void vfunc2() { printf("A::vfunc2\n"); }
    void func1() {}
    void func2() {}
private:
    int m_data1, m_data2;
};
class B : public A {
public:
    virtual void vfunc1() { printf("B::vfunc1\n"); }
    void func1() {}
private:
    int m_data3;
};
class C: public B {
public:
    virtual void vfunc2() { printf("C::vfunc2\n"); }
    void func2() {}
private:
    int m_data1, m_data4;
};
class E : virtual public A {
public:
    virtual void vfunc2() { printf("C::vfunc2\n"); }
    void func2() {}
    virtual void vfunc4() {}
private:
    int m_data1, m_data4;
};

#define _PTR_MAX_VALUE ((void*)0x000F'0000'0000'0000)
inline bool IsValidPtr(void* p) { return (p >= (void*)0x10000) && (p < _PTR_MAX_VALUE) && p != nullptr; }
inline void forech_v_func(void** vtable) {
    int32_t count = 0;
    for (;;count++) {
        if (!IsValidPtr((void*)vtable[count]) || count > 500)
        {
            break;
        }else {
            printf("v_%d_func address: %p\n", count, (void*)vtable[count]);
        }
    }
}

template <typename T, typename U>
int64_t get_base_class_offset(U* class_ptr)
{
    T* base_ptr = dynamic_cast<T*>(class_ptr);
    if (base_ptr)
        return (uint64_t)base_ptr - (uint64_t)class_ptr;
    return 0;
}

int main() {
    A* a = new A;
    void** vtable_a = *(void***)a;
    printf("vtable_a address: %p\n", vtable_a);
    forech_v_func(vtable_a);

    B* b = new B;
    void** vtable_b = *(void***)b;
    printf("vtable_b address: %p\n", vtable_b);
    forech_v_func(vtable_b);

    C* c = new C;
    void** vtable_c = *(void***)c;
    printf("vtable_c address: %p\n", vtable_c);
    forech_v_func(vtable_c);

    E* e = new E;
    void** vtable_e = *(void***)e;
    printf("vtable_e address: %p\n", vtable_e);
    forech_v_func(vtable_e);
    int64_t v_offset = get_base_class_offset<A>(e);
    vtable_e = *(void***)((char*)e + v_offset);
    printf("vtable_e address: %p\n", vtable_e);
    forech_v_func(vtable_e);

    B* c_to_b_ptr = (B*)c;
    vtable_b = *(void***)c_to_b_ptr;
    printf("vtable_b address: %p\n", vtable_b);
    forech_v_func(vtable_b);

    C pure_c;
    vtable_c = *(void***)&pure_c;
    printf("vtable_c address: %p\n", vtable_c);
    forech_v_func(vtable_c);
    pure_c.vfunc1();
    pure_c.vfunc2();

    B pure_c_to_b = *dynamic_cast<B*>(&pure_c);
    vtable_b = *(void***)&pure_c_to_b;
    printf("vtable_b address: %p\n", vtable_b);
    forech_v_func(vtable_b);
    pure_c_to_b.vfunc1();
    pure_c_to_b.vfunc2();

    return 0;
}