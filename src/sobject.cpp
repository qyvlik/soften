#include "sobject.h"

using namespace std;

ObjectManager<SObject*> SObject::SObjectManager;

const ObjectMetaCall<SObject> SObject::StaticMetaCall = {
    {
        pair<string, SObject::CallableMethod>
        ( "toString",
        [](SObject* thiz, std::vector<Variant>&, Variant& result)->int{
            result = thiz->toString();
            return ObjectMetaCallState::CallSuccess;
        }),

        pair<string, SObject::CallableMethod>
        ( "printSelf",
        [](SObject* thiz, std::vector<Variant>&, Variant& )->int{
            cout
            #ifdef QBS_DEBUG
            << "printSelf: "
            #endif
            << thiz->toString() << endl;
            return ObjectMetaCallState::CallSuccess;
        }),

        pair<string, SObject::CallableMethod>
        ( "isEqual",
        // bool isEqual(const SObject* other)
        [](SObject* thiz, std::vector<Variant>&args, Variant& result)->int{

            if(args.size() != 1)
            return ObjectMetaCallState::ArgumentsLengthError;

            if(!args.at(0).canConvert<SObject*>())
            return ObjectMetaCallState::ArgumentsTypeError;

            SObject* object = args.at(0).value<SObject*>();

            if(!SObject::SObjectManager.isLive(object))
            return ObjectMetaCallState::ObjectDeath;

            result = thiz->isEqual(object);
            return ObjectMetaCallState::CallSuccess;
        })
    }
};


SObject::SObject(SObject *parent):
    m_parent(nullptr)
{
    SObjectManager.add(this);
    setParentHelper(parent);
}

SObject::~SObject()
{
#ifdef QBS_DEBUG
    cout << "parent:" << this->parent() << " this:" << this << endl;
#endif
    auto iter = this->children.begin();
    auto end = this->children.end();

    while(iter != end) {
        // this->children.remove((*iter));
        this->deleteChild((*iter));
        iter++;
    }

    this->children.clear();

    SObjectManager.remove(this);
}

bool SObject::isEqual(const SObject *object) const
{
    return this == object;
}

string SObject::toString() const
{
    std::stringstream sstream;
    sstream << this;
    std::string address;
    sstream >> address;
    return "SObject(" + address + ")";
}

//! 优先调用动态添加的方法
int SObject::callMethod(const string &methodName,
                        std::vector<Variant>& args,
                        Variant& result)
{
    auto findDynamicMethod = this->SObject::dynamicMetaCall.find(methodName);
    auto end = this->SObject::dynamicMetaCall.end();
    return findDynamicMethod != end
            ? findDynamicMethod->second(this, args, result)
            : SObject::StaticMetaCall.findMethod(methodName)(this, args, result);
}


int SObject::callSampleMethod(const string methodName)
{
    VariantVector arguments;
    Variant result;
    return this->callMethod(methodName, arguments, result);
}

void SObject::setProperty(const std::string &name, const Variant &value)
{
    if(properties[name] != value) {
        properties[name] = value;
        propertyChanged(name);
    }
}

Variant SObject::property(const std::string &name) const
{
    auto findItem = properties.find(name);
    return findItem != properties.end()
            ? findItem->second
            : Variant();
}


void SObject::propertyChanged(const string propertyName)
{
#ifdef QBS_DEBUG
    cout << propertyName << endl;
#endif
    auto handle = propertyChangedHandles.find(propertyName);
    auto end = propertyChangedHandles.end();
    if(handle != end) {
        handle->second();
    }
}

void SObject::setPropertyChangedHandle(const string &propertyName, const SObject::Handle &handle)
{
    propertyChangedHandles.insert(
                pair<string, SObject::Handle>(
                    propertyName, handle)
                );
}

void SObject::addMethod(const string &methodName, const SObject::CallableMethod &callable)
{
    this->SObject::dynamicMetaCall[methodName] = callable;
    //    return SObject::StaticMetaCall.methods.find(methodName)
    //            == SObject::StaticMetaCall.methods.end()
    //            ? (this->SObject::dynamicMetaCall[methodName] = callable, true)
    //            : false;
}

void SObject::removeMethod(const string &methodName)
{
    this->SObject::dynamicMetaCall.erase(methodName);
}

void SObject::setParent(SObject *parentPointer)
{
    if(this != parentPointer) {
        this->setParentHelper(parentPointer);
    }
}

SObject *SObject::parent() const
{
    return this->m_parent;
}

void SObject::deleteChild(SObject *child)
{
    if(SObjectManager.isLive(child)){
        delete child;
    }
}

void SObject::setParentHelper(SObject *parentPointer)
{
    if(parentPointer) {
        // 自身的 parent 为空
        // 则设置 parent
        if(this->m_parent == nullptr) {
            SObjectManager.isLive(parentPointer)
                    ? ( this->m_parent = parentPointer,
                        this->m_parent->children.push_back(this) )
                    : []()->void{}();
        } else {
            // 自身的 parent 不为空
            // 先移除原有的父子关系
            // 再建立新的父子关系
            SObjectManager.isLive(m_parent) ? this->m_parent->children.remove(this)
                                            : []()->void{}();
            this->m_parent = parentPointer;
            this->m_parent->children.push_back(this);
        }
    }
}

