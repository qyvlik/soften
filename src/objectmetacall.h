#ifndef OBJECTMETACALL
#define OBJECTMETACALL

#include "variant.h"

#include <functional>

#define CALLABLE_METHOD(X)

struct ObjectMetaCallState {
    enum {
        Unkonwn = 1
        , CallSuccess = 0
        , NativeMethodNotFound = -1
        , ArgumentsTypeError = -2
        , ArgumentsLengthError = -3
        , NativeMethodHasExcept = -4
        , ObjectDeath = -5
        , NullMethod = -6
    };
};

template<typename Class>
struct ObjectMetaCall
{
    static_assert(std::is_class<Class>::value, "ONLY SUPPORT CLASS OR STRUCT");

    typedef Class CallableClass;

    typedef std::function<int (Class*, std::vector<Variant>&, Variant&)> CallableMethod;

    CallableMethod findMethod(const std::string& methodName) const {
        auto findCall = methods.find(methodName);
        return findCall != methods.end()
                ? findCall->second
                : [](Class*, std::vector<Variant>&, Variant&) -> int {
            return ObjectMetaCallState::NativeMethodNotFound;
        };
    }

    const std::map<std::string, CallableMethod> methods;

    // static const CallableMethod NotFoundMethod;
};

//template<typename Class>
//const typename ObjectMetaCall<Class>::CallableMethod
//ObjectMetaCall<Class>::NotFoundMethod =
//        [](ObjectMetaCall::CallableClass*, std::vector<Variant>&, Variant&) -> int {
//    return -1;
//};

//-------------------------------------------------------------------------------------


template<typename D, typename B>
int callMethodHelper(D* thiz,
                     const std::string& methodName,
                     std::vector<Variant>& args,
                     Variant& result)
{
    //! 静态检查
    static_assert(std::is_base_of<B, D>::value, "NOT BASE OF SObject");

    auto callMethod_d = thiz->D::StaticMetaCall.methods.find(methodName);

    return callMethod_d != thiz->D::StaticMetaCall.methods.end()
            ? callMethod_d->second(thiz, args, result)
            : thiz->B::callMethod(methodName, args, result);

//    if(callMethod_d != thiz->D::StaticMetaCall.methods.end()) {
//        return callMethod_d->second(thiz, args, result);
//    } else {
//        callMethod_d = thiz->D::dynamicMetaCall.find(methodName);
//        auto end = thiz->D::dynamicMetaCall.end();
//        if(callMethod_d != end) {
//            return callMethod_d->second(thiz, args, result);
//        } else {
//            return thiz->B::callMethod(methodName, args, result);
//        }
//    }
}

#define SOFTEN_OBJECT(_D_, _B_) \
    public: \
        typedef ObjectMetaCall<_D_>::CallableMethod CallableMethod; \
        static const ObjectMetaCall<_D_> StaticMetaCall; \
    private: \
        friend struct ObjectMetaCall<_D_>; \
        friend int callMethodHelper<_D_, _B_> (_D_* thiz, \
                                                const std::string& methodName, \
                                                std::vector<Variant>& args, \
                                                Variant& result); \
    public: \
        virtual int callMethod(const std::string& methodName, \
                                std::vector<Variant>& args, \
                                Variant& result) \
        { return callMethodHelper<_D_, _B_>(this, methodName, args, result); }


#endif // OBJECTMETACALL

