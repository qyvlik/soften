#ifndef MYOBJECT_H
#define MYOBJECT_H

#include "../../src/core/object.h"

class MyObject : public soften::Object
{
public:
    SOFTEN_OBJECT(MyObject, Object)

    SOFTEN_INVOKABLE std::string toString()const;
    SOFTEN_INVOKABLE int add(int a, int b);
};


#endif // MYOBJECT_H
