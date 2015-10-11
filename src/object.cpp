#include "object.h"
#include <strstream>
#include <iostream>

using namespace std;

namespace soften {

MetaObject<Object> Object::metaObject =
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
    string thiz;
    strstream tem;
    tem << this;
    tem >> thiz;

    string s("(Object");

    return thiz.empty()
            ? s+")"
            : s + ", " + thiz + ")";

}


}
