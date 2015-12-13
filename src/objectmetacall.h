#ifndef OBJECTMETACALL
#define OBJECTMETACALL

#include "variant.h"

#include <functional>

template<typename Class>
struct ObjectMetaCall
{
    static_assert(std::is_class<Class>::value, "ONLY SUPPORT CLASS OR STRUCT");

    typedef std::function<int (Class*, std::vector<Variant>&, Variant&)> CallableMethod;

    CallableMethod findMethod(const std::string& methodName) const {
        auto findCall = methods.find(methodName);
        return findCall != methods.end()
                ? findCall->second
                : [methodName](Class* , std::vector<Variant>&, Variant&) -> int {
#ifdef QBS_DEBUG
            std::cout << "CallableMethod findMethod(const std::string& methodName) const "
                         "not find :"
                      << methodName << std::endl;
#endif
            return -1;
        }
        ;
    }

    const std::map<const std::string, CallableMethod> methods;
};

template<typename D, typename B>
int callMethodHelper(D* thiz,
                     const std::string& methodName,
                     std::vector<Variant> args,
                     Variant result) {
    //! 静态检查
    static_assert(std::is_base_of<B, D>::value, "NOT BASE OF SObject");

    auto findCall = thiz->StaticMetaCall.methods.find(methodName);
    auto end = thiz->StaticMetaCall.methods.end();

    return findCall != end
            ? findCall->second(thiz, args, result)
            : thiz->B::callMethod(methodName, args, result);
}




#endif // OBJECTMETACALL

