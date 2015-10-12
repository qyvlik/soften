#include "object.h"

namespace soften {


Object::Meta Object::metaObject =
{
    {
        {
            std::pair<const std::string, Object::call>(
            "toString",
            [&](Object* thiz, void* , void* r){
                std::string* r_ = reinterpret_cast<std::string*>(r);
                (*r_) = thiz->toString();
            })
        } // toString
    }
};


Object::Object()
{

}


std::string Object::toString() const
{
    std::string thiz = ::soften::getObjectAddress<Object>(this);
    std::string s("(Object");

    return thiz.empty()
            ? s +  ")"
            : s + ", " + thiz + ")";

}


}
