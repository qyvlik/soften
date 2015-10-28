#ifndef FUNCTIONMETA_H
#define FUNCTIONMETA_H

#include <tuple>

namespace soften {


template<typename Sig>
struct FunctionMeta;

template<typename R, typename... Args>
struct FunctionMeta<R(*)(Args...)> {
    static const size_t value = sizeof...(Args);
    typedef std::tuple<Args...> ArgsTypeTuple;
    typedef R ReturnType;
};

template<typename R, typename T, typename... Args>
struct FunctionMeta< R( T::* )( Args... )> {
    static const size_t value = sizeof...(Args);
    typedef std::tuple<Args...> ArgsTypeTuple;
    typedef R ReturnType;
};

template<typename R, typename... Args>
struct FunctionMeta<R(Args...)> {
    static const size_t value = sizeof...(Args);
    typedef std::tuple<Args...> ArgsTypeTuple;
    typedef R ReturnType;
};

/**

void z1(int, int){}
typedef void(*z2)(int, int);
typedef void(*z3)();
typedef void(*z4)(void);

void test_function_meta()
{
    cout << FunctionMeta<decltype (z1)>::value << endl;             // 2
    cout << FunctionMeta<z2>::value << endl;                        // 2
    cout << FunctionMeta<z3>::value << endl;                        // 0
    cout << FunctionMeta<z4>::value <<  endl;                       // 0
    cout << FunctionMeta<decltype(Bridge::ADD)>::value << endl;     // 1

    typedef std::tuple_element<0, FunctionMeta<decltype (z1)>::ArgsTypeTuple >::type Type_Int;
    Type_Int i = 0;
    cout << i << endl;
}

*/
}

#endif // FUNCTIONMETA_H
