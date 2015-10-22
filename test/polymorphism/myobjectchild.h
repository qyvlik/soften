#ifndef MYOBJECTCHILD_H
#define MYOBJECTCHILD_H

#include "myobject.h"

class MyObjectChild : public MyObject
{
public:
    SOFTEN_OBJECT(MyObjectChild, MyObject)
    virtual std::string toString() const;
};

#endif // MYOBJECTCHILD_H
