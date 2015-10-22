#ifndef MYOBJECTCHILD_H
#define MYOBJECTCHILD_H

#include "myobject.h"

class MyObjectChild : public MyObject
{
public:
    SOFTEN_OBJECT(MyObjectChild, MyObject)
    //    typedef MetaCall<MyObjectChild> Meta;
    //    static Meta metaCall;
    //    virtual int callMethod(const std::string& methodName, void* args, void*r) {
    //        return internal::callMethod<MyObjectChild, MyObject>(this, methodName, args, r);
    //    }

    virtual std::string toString() const;
};

#endif // MYOBJECTCHILD_H
