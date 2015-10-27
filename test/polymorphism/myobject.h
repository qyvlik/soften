#ifndef MYOBJECT_H
#define MYOBJECT_H

#include "../../src/core/object.h"

class MyObject : public soften::Object
{
public:
    SOFTEN_OBJECT(MyObject, Object)

//    typedef MetaCall<MyObject> Meta;
//    static Meta metaCall;
//    virtual int callMethod(const std::string& methodName, void* args, void*r) {
//        return internal::callMethod<MyObject, Object>(this, methodName, args, r);
//    }

    SOFTEN_INVOKABLE virtual std::string toString()const;
    SOFTEN_INVOKABLE int add(int a, int b);
};


#endif // MYOBJECT_H