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
};

template<typename R, typename T, typename... Args>
struct FunctionMeta< R( T::* )( Args... )> {
    static const size_t value = sizeof...(Args);
    typedef std::tuple<Args...> ArgsTypeTuple;

};

template<typename R, typename... Args>
struct FunctionMeta<R(Args...)> {
    static const size_t value = sizeof...(Args);
    typedef std::tuple<Args...> ArgsTypeTuple;
};

template<typename Sig>
inline size_t get_arguments_count(Sig) {
    return FunctionMeta<Sig>::value;
}


}

#endif // FUNCTIONMETA_H
