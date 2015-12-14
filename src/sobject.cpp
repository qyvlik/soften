#include "sobject.h"

using namespace std;

const ObjectMetaCall<SObject> SObject::StaticMetaCall = {
    {
        pair<const string, SObject::CallableMethod >
        ( "toString",
        [](SObject* thiz, std::vector<Variant>&, Variant& result)->int{
            result = thiz->toString();
            return 0;
        }),

        pair<const string, SObject::CallableMethod >
        ( "printSelf",
        [](SObject* thiz, std::vector<Variant>&, Variant& )->int{
            cout
#ifdef QBS_DEBUG
            << "printSelf: "
#endif
            << thiz->toString() << endl;
            return 0;
        })
    }
};



SObject::SObject(SObject *parent)
{

}

SObject::~SObject()
{

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

