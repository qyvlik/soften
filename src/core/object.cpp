#include "object.h"
#include "bridge.h"

using namespace std;

namespace soften {


Object::Meta Object::metaCall = {
    {
        pair<const string, Object::Meta::Call>(
        "toString",
        [](Object* thiz, std::vector<Bridge*>, Bridge*)->int{
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


int Object::callMethod(const string &methodName, std::vector<Bridge *> args, Bridge *r)
{
    return Object::metaCall.findMethod(methodName)(this, args, r);
}


string Object::toString() const
{
    string thiz = ::soften::getObjectAddress<Object>(this);
    string s("(Object");

    return thiz.empty()
            ? s +  ")"
            : s + ", " + thiz + ")";
}


}
