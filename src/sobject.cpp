#include "sobject.h"

using namespace std;


ObjectManager<SObject*> SObject::SObjectManager;


const ObjectMetaCall<SObject> SObject::StaticMetaCall = {
    {
        pair<const string, SObject::CallableMethod>
        ( "toString",
        [](SObject* thiz, std::vector<Variant>&, Variant& result)->int{
            result = thiz->toString();
            return 0;
        }),

        pair<const string, SObject::CallableMethod>
        ( "printSelf",
        [](SObject* thiz, std::vector<Variant>&, Variant& )->int{
            cout
            #ifdef QBS_DEBUG
            << "printSelf: "
            #endif
            << thiz->toString() << endl;
            return 0;
        }),

        pair<const string, SObject::CallableMethod>
        ( "isEqual",
        // bool isEqual(const SObject* other)
        [](SObject* thiz, std::vector<Variant>&args, Variant& result)->int{

            if(args.size() != 1) return -1;

            if(!args.at(0).canConvert<SObject*>()) return -2;

            SObject* object = args.at(0).value<SObject*>();

            if(!SObject::SObjectManager.isLive(object)) return -3;

            result = thiz->isEqual(object);
            return 0;
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
        this->children.remove((*iter));
        this->deleteChild((*iter));
        iter++;
    }

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
    properties[name] = value;
}

Variant SObject::property(const std::string &name) const
{
    auto findItem = properties.find(name);
    return findItem != properties.end()
            ? findItem->second
            : Variant();
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
    this->setParentHelper(parentPointer);
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
            this->m_parent = parentPointer;
            this->m_parent->children.push_back(this);

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

