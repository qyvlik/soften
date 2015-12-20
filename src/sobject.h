#ifndef SOBJECT_H
#define SOBJECT_H

#include "objectmetacall.h"

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

class SObjectFactory;

class SObject
{
public:

    typedef std::function<void(void)> Delegate;

    struct Handle
    {
        Handle(const std::string& id, const Delegate& delegate):
            id(id),
            delegate(delegate)
        { }

        bool operator < (const Handle& other) const
        { return this->id < other.id; }

        friend bool operator == (const Handle& lhs, const Handle& rhs)
        { return lhs.id == rhs.id; }

        void operator ()(void) const
        { this->delegate(); }

        std::string id;
        Delegate delegate;
    };

    typedef ObjectMetaCall<SObject>::CallableMethod CallableMethod;
    static const ObjectMetaCall<SObject> StaticMetaCall;
    static ObjectManager<SObject*> SObjectManager;

private:
    friend struct ObjectMetaCall<SObject>;
    friend class SObjectFactory;
    std::map<const std::string, CallableMethod> dynamicMetaCall;

public:
    //! 优先调用动态添加的方法
    virtual int callMethod(const std::string& methodName,
                           std::vector<Variant>& args,
                           Variant& result);

public:

    CALLABLE_METHOD(printSelf)
    CALLABLE_METHOD(toString)
    CALLABLE_METHOD(isEqual)

    explicit SObject(SObject* m_parent = 0);
    virtual ~SObject();

    virtual bool isEqual(const SObject* object) const;

    virtual std::string toString() const;

    int callSampleMethod(const std::string methodName);

    void setProperty(const std::string& name, const Variant& value);

    Variant property(const std::string& name) const;

    void removePropertyChangeHandle(const std::string& propertyName, const std::string& handleId);

    void setPropertyChangedHandle(const std::string& propertyName, const Handle& handle);

    void propertyChanged(const std::string propertyName);

    void addMethod(const std::string& methodName,const CallableMethod& callable);

    void removeMethod(const std::string& methodName);

    std::string objectName()const;

    void setObjectName(const std::string& name);

protected:

    SObject *parent() const;

    void setParent(SObject* parentPointer);

    void deleteChild(SObject* child);

private:
    SObject& operator =(const SObject& other) = delete;
    SObject(const SObject& other) = delete;

    void setParentHelper(SObject* parentPointer);

    VariantMap properties;
    std::map<std::string, std::set<Handle> > propertyChangedHandles;

    SObject* m_parent;
    std::list<SObject*> children;

};


class SObjectFactory
{
public:
    virtual ~SObjectFactory()
    {}

    virtual SObject* create() = 0;

    static void setObjectOwnerShip(SObject* child, SObject* parent) {
        child->setParent(parent);
    }
};

STATIC_REGISTER_TYPE(SObject*, "SObject*");

template<>
class Bridge<SObject*> : public AbstractBridge
{
public:
    explicit Bridge(SObject* data):
        d_ptr(data)
    { }

    ~Bridge()
    {
        /**
          \note don't delete data
        */
#ifdef QBS_DEBUG
        std::cout << "don't delete data:" << d_ptr->toString() << std::endl;
#endif
    }

    inline std::string typeString() const
    { return ::typeString<SObject*>(); }

    inline void set(SObject* value)
    { d_ptr = value; }

    inline SObject* get()
    { return d_ptr; }

    inline const SObject* get() const
    { return d_ptr; }

    bool isEqual(const AbstractBridge* other) const
    {
        Bridge<SObject*> * other_ =
                dynamic_cast<Bridge<SObject*> *>
                (const_cast<AbstractBridge*>(other));
        return other_ && d_ptr && other_->d_ptr
                ? d_ptr->isEqual(other_->d_ptr)                 // 多态
                : false;
    }

    inline bool assign(const AbstractBridge* other) {
        (void)other;
        return false;
    }

    AbstractBridge* clone() const
    { return new Bridge<SObject*>(d_ptr); }

    std::string toString()const
    { return d_ptr ? d_ptr->toString() : ""; }

private:
    SObject* d_ptr;
};

#endif // SOBJECT_H
