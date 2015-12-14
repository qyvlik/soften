#ifndef SOBJECT_H
#define SOBJECT_H

#include "objectmetacall.h"
#include "variant.h"

#include <set>

template<typename Class>
struct ObjectManager
{
    static bool isLive(const Class object)
    {  return ObjectSet.find(object) != ObjectSet.end() ; }

    static void remove(const Class object)
    { ObjectSet.erase(object); }

    static bool add(const Class object)
    { return ObjectSet.insert(object).second; }

private:
    static std::set<Class> ObjectSet;
};

template<typename Class>
std::set<Class> ObjectManager<Class>::ObjectSet;

class SObject
{
public:
    typedef ObjectMetaCall<SObject>::CallableMethod CallableMethod;
    static const ObjectMetaCall<SObject> StaticMetaCall;

private:
    static ObjectManager<SObject*> SObjectManager;
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

    explicit SObject(SObject* m_parent = 0);
    virtual ~SObject();

    virtual bool isEqual(const SObject* object) const;

    virtual std::string toString() const;

    int callSampleMethod(const std::string methodName);

    void setProperty(const std::string& name, const Variant& value);

    Variant property(const std::string& name) const;

    void addMethod(const std::string& methodName,const CallableMethod& callable);

    void removeMethod(const std::string& methodName);

protected:

    SObject *parent() const;

    void setParent(SObject* parentPointer);

    void deleteChild(SObject* child);

private:
    VariantMap properties;

    SObject& operator =(const SObject& other) = delete;
    SObject(const SObject& other) = delete;

    SObject* m_parent;
    std::list<SObject*> children;

    void setParentHelper(SObject* parentPointer);

};


#endif // SOBJECT_H
