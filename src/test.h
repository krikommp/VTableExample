#define SIMILAR_TO_F(Class) \
public: \
    void func_##Class##_0(); \
    virtual void func_##Class##_1(); \
    static void func_##Class##_2(); \
    virtual ~##Class(); \
private: \
    int v_##Class; \
    static int g_##Class;

class A {
    SIMILAR_TO_F(A)
};

class A1 : public A
{
    SIMILAR_TO_F(A1)
};

class A2 : public A
{
    SIMILAR_TO_F(A2)
};

class E : virtual public A1, virtual public A2 
{
    SIMILAR_TO_F(E);
};
