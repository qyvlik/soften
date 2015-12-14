#ifndef SOBJECT_H
#define SOBJECT_H

#include "objectmetacall.h"
#include "variant.h"

class SObject
{
public:
    typedef ObjectMetaCall<SObject>::CallableMethod CallableMethod;
    static const ObjectMetaCall<SObject> StaticMetaCall;

private:
    friend struct ObjectMetaCall<SObject>;
    std::map<const std::string, CallableMethod> dynamicMetaCall;

public:
    //! 优先调用动态添加的方法
    virtual int callMethod(const std::string& methodName,
                           std::vector<Variant>& args,
                           Variant& result);

public:

    CALLABLE_METHOD(printSelf)
    CALLABLE_METHOD(toString)

    explicit SObject();
    virtual ~SObject();

    virtual bool isEqual(const SObject* object) const;

    virtual std::string toString() const;

    int callSampleMethod(const std::string methodName);

    void setProperty(const std::string& name, const Variant& value);

    Variant property(const std::string& name) const;

    void addMethod(const std::string& methodName,const CallableMethod& callable);

    void removeMethod(const std::string& methodName);

private:
    VariantMap properties;
};


#endif // SOBJECT_H
