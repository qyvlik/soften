#ifndef MYOBJECT_H
#define MYOBJECT_H

#include "../src/sobject.h"

class MyObject : public SObject
{

    SOFTEN_OBJECT(MyObject, SObject);

    //public:
    //    typedef ObjectMetaCall<MyObject>::CallableMethod CallableMethod;
    //    static const ObjectMetaCall<MyObject> StaticMetaCall;
    //private:
    //    friend struct ObjectMetaCall<MyObject>;
    //    friend int callMethodHelper<MyObject, SObject> (MyObject* thiz,
    //                                                    const std::string& methodName,
    //                                                    std::vector<Variant> args,
    //                                                    Variant result);
    //public:
    //    virtual int callMethod(const std::string methodName,
    //                           std::vector<Variant> &args,
    //                           Variant& result)
    //    { return callMethodHelper<MyObject, SObject>(this, methodName, args, result); }

public:
    explicit MyObject();
    std::string toString()const;
};

class MyMyObject : public MyObject
{
    SOFTEN_OBJECT(MyMyObject, MyObject);
public:
    std::string toString() const;
};



#endif // MYOBJECT_H
