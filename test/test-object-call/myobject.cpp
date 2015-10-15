#include "myobject.h"
#include <tuple>

using namespace std;

MyObject::MyObject()
{

}

MyObject::~MyObject()
{

}

void MyObject::test(soften::Object *obj, string *s)
{
    obj->callMethod("toString", obj, NULL, s);
}

int MyObject::main(int, char **) {
    soften::Object obj;
    MyObject mObject;

    string name;

    test(&obj, &name);
    std::cout << "name:" << name << std::endl;
    test(&mObject, &name);
    std::cout << "name:" << name << std::endl;

    int r = 0;

    std::tuple<int, int> a(10, 10);
    mObject.callMethod("complex", &mObject, &a, &r);
    std::cout << "complex r: " << r << std::endl;

    std::tuple<int, int> a1(100, 100);
    mObject.callMethod("complex", &a1, &r);
    std::cout << "complex r: " << r << std::endl;

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
    std::cout << int_ref << std::endl;

    return 0;
}

void MyObject::privateMethod() {
    cout << "can you call the private method in soften?" << endl;
}

MyObject::Meta MyObject::metaObject = {
    {
        {
            pair<const string, MyObject::call>(
            "toString",
            [&](MyObject* thiz, void* , void* r) -> soften::State{
                string* r_ = reinterpret_cast<string*>(r);
                (*r_) = thiz->toString();
                return soften::State::NormalCall;
            })
        } // toString
        ,
        {
            pair<const string, MyObject::call>(
            "complex",
            [&](MyObject* thiz, void* args, void* r) -> soften::State {

                typedef tuple<int, int>* Ap;
                Ap arguments = reinterpret_cast<Ap>(args);

                _TUPLE_GET_ARGUMENTS(2);
                //! decltype(std::get<0>(*arguments)) arg0 = std::get<0>(*arguments);
                //! decltype(std::get<1>(*arguments)) arg1 = std::get<1>(*arguments);

                int* r_ = reinterpret_cast<int*>(r);
                (*r_) = thiz->complex(arg0, arg1);
                return soften::State::NormalCall;
            })
        } // complex
        ,
        {
            pair<const string, MyObject::call>(
            "privateMethod",
            [&](MyObject* thiz, void* , void* ) -> soften::State {
                thiz->privateMethod();
                cout << "soften can use the MetaObject call MyObject::privateMethod() "
                << "becasue the MetaObject is friend class on MyObject"
                << endl;
                return soften::State::NormalCall;
            })
        } // privateMethod
        ,
        {
            pair<const string, MyObject::call>(
            "ref",
            [&](MyObject* thiz, void* args, void* ) -> soften::State {
                typedef std::tuple<int&> * Ap;
                Ap arguments = reinterpret_cast<Ap>(args);
                decltype(std::get<0>(*arguments)) arg0 = std::get<0>(*arguments);
                thiz->ref(arg0);
                return soften::State::NormalCall;
            })
        } // ref
    }
};
