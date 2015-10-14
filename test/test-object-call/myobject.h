#ifndef MYOBJECT_H
#define MYOBJECT_H


#include "../../src/core/object.h"
#include <tuple>
#include <string>

using std::string;

class MyObject : public soften::Object
{
    SOFTEN_OBJECT(MyObject);

public:
    MyObject();
    ~MyObject();
    SOFTEN_INVOKABLE std::string toString()const {
        return  "MyObject:" + this->Object::toString();
    }
    SOFTEN_INVOKABLE int complex(int arg0, int arg1) {
        return arg0 + arg1;
    }
    SOFTEN_INVOKABLE void ref(int& arg0) {
        ++arg0;
    }

    static void test(soften::Object* obj, std::string* s);
    static int main(int, char**);

private:
    SOFTEN_INVOKABLE void privateMethod();

};



#endif // MYOBJECT_H
