#include <iostream>
#include "src/object.h"
#include <tuple>

using namespace std;

class MyObject : public soften::Object
{
    SOFTEN_OBJECT(MyObject)

    public:
        MyObject(){}
    ~MyObject(){}
    SOFTEN_INVOKABLE std::string toString()const {
        return  "MyObject:" + this->Object::toString();
    }
    SOFTEN_INVOKABLE int complex(int arg0, int arg1) {
        return arg0 + arg1;
    }
};

MyObject::Meta MyObject::metaObject = {
    {
        {
            pair<const string, MyObject::call>(
            "toString",
            [&](MyObject* thiz, void* , void* r){
                string* r_ = reinterpret_cast<string*>(r);
                (*r_) = thiz->toString();
            })
        } // toString
        ,
        {
            pair<const string, MyObject::call>(
            "complex",
            [&](MyObject* thiz, void* args, void* r){

                typedef tuple<int, int>* Ap;
                Ap arguments = reinterpret_cast<Ap>(args);

                int arg0 = std::get<0>(*arguments);
                int arg1 = std::get<1>(*arguments);

                int* r_ = reinterpret_cast<int*>(r);
                (*r_) = thiz->complex(arg0, arg1);
            })
        } // complex
    }
};

void test(soften::Object* obj, string* s)
{
    obj->callMethod("toString", obj, NULL, s);
}


int main(int, char**)
{
    soften::Object obj;
    MyObject mObject;

    string name;

    test(&obj, &name);
    cout << "name:" << name << endl;
    test(&mObject, &name);
    cout << "name:" << name << endl;

    int r = 0;

    std::tuple<int, int> a(10, 10);
    mObject.callMethod("complex", &mObject, &a, &r);
    cout << "complex r: " << r << endl;

    std::tuple<int, int> a1(100, 100);
    mObject.callMethod("complex", &a1, &r);
    cout << "complex r: " << r << endl;

    /*!
     * don't run this code
     */
    //! mObject.callMethod("complex", &obj, &a, &r);
    //! cout << "complex r: " << r << endl;

    return 0;
}




