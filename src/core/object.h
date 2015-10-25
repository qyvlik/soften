#ifndef OBJECT_H
#define OBJECT_H

#include <functional>
#include <map>
#include <list>

#include "../soften.h"
#include "metacall.h"

namespace soften {

class Bridge;
class Object
{
public:
    SOFTEN_HACK class MetaCall<Object>;
    typedef MetaCall<Object> Meta;
    static Meta metaCall;
    virtual int callMethod(const std::string& methodName, std::vector<Bridge*> args, Bridge* r);

public:
    explicit Object();
    virtual ~Object();

    SOFTEN_INVOKABLE virtual std::string toString() const;
};

namespace internal {

template<typename D, typename B>
int callMethod(D* thiz, const std::string& methodName,
               std::vector<soften::Bridge*> args, soften::Bridge* r) {
    //! 静态检查
    static_assert(std::is_base_of<B, D>::value, "E10: is not base");

    auto c = thiz->metaCall.methods.find(methodName);
    auto end = thiz->metaCall.methods.end();

    if( c != end) {
        return c->second(thiz, args, r);
    } else {
        // 向上
       return thiz->B::callMethod(methodName, args, r);
    }
}


}


#define SOFTEN_OBJECT(_DERIVED_, _BASE_)                                                            \
    public:                                                                                         \
        SOFTEN_HACK class soften::MetaCall<_DERIVED_>;                                              \
        typedef soften::MetaCall<_DERIVED_> Meta;                                                   \
        static Meta metaCall;                                                                       \
        virtual int callMethod(const std::string& methodName,                                       \
                                std::vector<soften::Bridge*> args, soften::Bridge* r)               \
        {                                                                                           \
            return soften::internal::callMethod<_DERIVED_, _BASE_>(this, methodName, args, r);      \
        }


}

#endif // OBJECT_H
