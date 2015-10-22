#include "object.h"

using namespace std;

namespace soften {


Object::Meta Object::metaCall = {
    {
        pair<const string, Object::Meta::Call>(
        "toString",
        [](Object* thiz, void* , void*)->int{
            cout << thiz->toString();
            return (int)soften::State::NormalCall;
        })
    }
};


Object::Object()
{

}


Object::~Object()
{

}


int Object::callMethod(const string &methodName, void *args, void *r)
{
    return Object::metaCall.findMethod(methodName)(this, args, r);

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
