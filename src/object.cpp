#include "object.h"
#include <strstream>
#include <iostream>

using namespace std;

namespace soften {

Object::Meta Object::metaObject =
{
    {
        {
            pair<const string, Object::call>(
            "toString",
            [&](Object* thiz, void* , void* r){
                string* r_ = reinterpret_cast<string*>(r);
                (*r_) = thiz->toString();
            })
        } // toString
    }
};

Object::Object()
{

}



string Object::toString() const
{
    string thiz = soften::getObjectAddress<Object>(this);

    string s("(Object");

    return thiz.empty()
            ? s+")"
            : s + ", " + thiz + ")";

}


}
