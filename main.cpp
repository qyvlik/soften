#include <iostream>
#include <tuple>
#include "src/object.h"

using namespace std;

#define _TUPLE_GET_ONE_ARGUMENT(_NUMBER_)  \
    /*! arg0 or arg1 .. arg9 ..  */        \
    decltype(std::get<_NUMBER_>(*arguments)) arg##_NUMBER_ = std::get<_NUMBER_>(*arguments);

#define _TUPLE_GET_ARGUMENTS_1  _TUPLE_GET_ONE_ARGUMENT(0)
#define _TUPLE_GET_ARGUMENTS_2  _TUPLE_GET_ONE_ARGUMENT(1) _TUPLE_GET_ARGUMENTS_1
#define _TUPLE_GET_ARGUMENTS_3  _TUPLE_GET_ONE_ARGUMENT(2) _TUPLE_GET_ARGUMENTS_2
#define _TUPLE_GET_ARGUMENTS_4  _TUPLE_GET_ONE_ARGUMENT(3) _TUPLE_GET_ARGUMENTS_3
#define _TUPLE_GET_ARGUMENTS_5  _TUPLE_GET_ONE_ARGUMENT(4) _TUPLE_GET_ARGUMENTS_4
#define _TUPLE_GET_ARGUMENTS_6  _TUPLE_GET_ONE_ARGUMENT(5) _TUPLE_GET_ARGUMENTS_5
#define _TUPLE_GET_ARGUMENTS_7  _TUPLE_GET_ONE_ARGUMENT(6) _TUPLE_GET_ARGUMENTS_6
#define _TUPLE_GET_ARGUMENTS_8  _TUPLE_GET_ONE_ARGUMENT(7) _TUPLE_GET_ARGUMENTS_7
#define _TUPLE_GET_ARGUMENTS_9  _TUPLE_GET_ONE_ARGUMENT(8) _TUPLE_GET_ARGUMENTS_8
#define _TUPLE_GET_ARGUMENTS_10 _TUPLE_GET_ONE_ARGUMENT(9) _TUPLE_GET_ARGUMENTS_9

#define _TUPLE_GET_ARGUMENTS(_ARG_COUNT_)                    \
    /*! arg0 to arg##_ARG_COUNT_ */                          \
    _TUPLE_GET_ARGUMENTS_##_ARG_COUNT_

class MyObject : public soften::Object
{
    SOFTEN_OBJECT(MyObject);

public:
    MyObject(){}
    ~MyObject(){}
    SOFTEN_INVOKABLE std::string toString()const {
        return  "MyObject:" + this->Object::toString();
    }
    SOFTEN_INVOKABLE int complex(int arg0, int arg1) {
        return arg0 + arg1;
    }
    SOFTEN_INVOKABLE void ref(int& arg0) {
        ++arg0;
    }

private:
    SOFTEN_INVOKABLE void privateMethod() {
        cout << "can you call the private method in soften?" << endl;
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

                _TUPLE_GET_ARGUMENTS(2);
                //! decltype(std::get<0>(*arguments)) arg0 = std::get<0>(*arguments);
                //! decltype(std::get<1>(*arguments)) arg1 = std::get<1>(*arguments);

                int* r_ = reinterpret_cast<int*>(r);
                (*r_) = thiz->complex(arg0, arg1);
            })
        } // complex
        ,
        {
            pair<const string, MyObject::call>(
            "privateMethod",
            [&](MyObject* thiz, void* , void* ){
                thiz->privateMethod();
                cout << "soften can use the MetaObject call MyObject::privateMethod() "
                << "becasue the MetaObject is friend class on MyObject"
                << endl;
            })
        } // privateMethod
        ,
        {
            pair<const string, MyObject::call>(
            "ref",
            [&](MyObject* thiz, void* args, void* ){
                typedef std::tuple<int&> * Ap;
                Ap arguments = reinterpret_cast<Ap>(args);
                decltype(std::get<0>(*arguments)) arg0 = std::get<0>(*arguments);
                thiz->ref(arg0);
            })
        } // ref
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

    mObject.callMethod("privateMethod", NULL, NULL);

    int int_ref = 10;
    std::tuple<int&> a0(int_ref);
    mObject.callMethod("ref", &a0, NULL);
    mObject.ref(int_ref);
    cout << int_ref << endl;

    return 0;
}
