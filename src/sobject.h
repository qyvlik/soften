#ifndef SOBJECT_H
#define SOBJECT_H

#include "objectmetacall.h"
#include "variant.h"

class SObject
{
public:
    friend struct ObjectMetaCall<SObject>;
    typedef ObjectMetaCall<SObject>::CallableMethod CallableMethod;
    static const ObjectMetaCall<SObject> StaticMetaCall;

    explicit SObject();
    virtual ~SObject();

    virtual bool isEqual(const SObject* object);

    virtual std::string toString() const;

    //! 优先调用动态添加的方法
    virtual int callMethod(const std::string methodName,
                           std::vector<Variant> &args,
                           Variant& result);

    void setProperty(const std::string& name, const Variant& value);

    Variant property(const std::string& name) const;

    void addMethod(const std::string& methodName,const CallableMethod& callable);

    void removeMethod(const std::string& methodName);

private:
    VariantMap properties;
    std::map<const std::string, CallableMethod> dynamicMetaCall;
};

template<typename D, typename B>
int callMethod(D* thiz,
               const std::string& methodName,
               std::vector<Variant> args,
               Variant result) {
    //! 静态检查
    static_assert(std::is_base_of<B, D>::value, "NOT BASE OF SObject");
    static_assert(std::is_base_of<SObject, D>::value, "NOT BASE OF SObject");

    auto c = thiz->metaCall.methods.find(methodName);
    auto end = thiz->metaCall.methods.end();

    if( c != end) {
        return c->second(thiz, args, result);
    } else {
        // 向上
       return thiz->B::callMethod(methodName, args, result);
    }
}


#endif // SOBJECT_H
