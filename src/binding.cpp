#include "binding.h"

using namespace std;

const ObjectMetaCall<Binding> Binding::StaticMetaCall = {
    {
        pair<string, Binding::CallableMethod>
        ( "runBindingExpression",
        [](Binding* thiz, std::vector<Variant>&, Variant&)->int{
            Variant result;
            thiz->m_expression(thiz->m_sources, result);
            if(SObject::SObjectManager.isLive(thiz->m_target)) {
                thiz->m_target->setProperty(thiz->m_property, result);
                return ObjectMetaCallState::CallSuccess;
            } else {
                return ObjectMetaCallState::ObjectDeath;
            }
        }),
    }
};


Binding::Binding(SObject *target,
                 const std::string &property,
                 const Binding::BindingExpression &bindingExpression,
                 SObject *parent)
    : SObject(parent),
      m_target(target),
      m_property(property),
      m_expression(bindingExpression)
{

}

Binding::~Binding()
{
    // std::vector<std::pair<SObject*, std::string> >
    auto remove_source_iter = m_sources.begin();
    auto remove_source_end = m_sources.end();

    SObject* remove_source_pointer;
    std::string remove_property_handle;
    while(remove_source_iter != remove_source_end) {
        remove_source_pointer = (*remove_source_iter).first;
        remove_property_handle = (*remove_source_iter).second;
        if(SObject::SObjectManager.isLive(remove_source_pointer)) {
            remove_source_pointer->removePropertyChangeHandle(
                        remove_property_handle,
                        AddressToString(this));
        }
        remove_source_iter++;
    }

#ifdef QBS_DEBUG
    cout << "Binding::~Binding() this: " << this << endl;
#endif
}

void Binding::addSourceObject(SObject *source, const std::string &propertyName)
{
    m_sources.push_back(pair<SObject *, string>(source, propertyName));

    source->setPropertyChangedHandle(propertyName,
                                     SObject::Handle(
                                         AddressToString(this),
                                         [this]() {
        if(SObject::SObjectManager.isLive(this)) {
            this->callSampleMethod("runBindingExpression");
        }
    }));
}

