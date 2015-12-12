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
                : [](Class* , std::vector<Variant>&, Variant&) -> int { return 0; }
        ;
    }

    const std::map<const std::string, CallableMethod> methods;
};

#endif // OBJECTMETACALL

