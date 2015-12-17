#include <iostream>

#include "../src/sobject.h"
#include "myobject.h"
#include "objectfactory.h"
#include "test_vector2d.h"
#include "test_callmethod_time.h"

using namespace std;

void test_01()
{
    SObject obj;

    VariantVector arguments;
    Variant result;

    obj.callMethod("toString",
                   arguments,
                   result);

    std::string getResultString;

    bool ok = result.get(getResultString);

    if(ok) {
        cout << getResultString << endl;
    } else {
        cout << "can't get the result string" << endl;
    }
}

void test_02()
{
    VariantVector arguments;
    Variant result;

    ObjectFactory objectFactory;

    SObject* ageObject = objectFactory.create();

    ageObject->callMethod("getAge", arguments, result);

    cout << result << endl;

    ageObject->callMethod("setAge", arguments, result);

    ageObject->callMethod("getAge", arguments, result);

    cout << result << endl;

    ageObject->callSampleMethod("doSomething");

    ageObject->callSampleMethod("tryToUseBingArg");

    arguments.push_back("1");
    arguments.push_back(1);
    arguments.push_back(1.2);

    ageObject->callMethod("print", arguments, result);
}

void test_03()
{
    cout << "sizeof(Variant)" << sizeof(Variant) << endl;

    cout << "sizeof(SObject::CallableMethod): "
         << sizeof(SObject::CallableMethod) << endl;

    cout << "sizeof(std::map<const std::string, CallableMethod>): "
         << sizeof(std::map<const std::string, SObject::CallableMethod>) << endl;

    cout << "sizeof(VariantMap): " << sizeof(VariantMap) << endl;

    cout << "sizeof(SObject): " << sizeof(SObject) << endl;
}


void test_04()
{
    cout << "sizeof(MyObject): " << sizeof(MyObject) << endl;
    MyObject myObj;
    myObj.callSampleMethod("printSelf");
    cout << endl;
    VariantVector vec;
    vec.push_back(12);
    vec.push_back("12");
    myObj.setProperty("vector", vec);
    cout << myObj.property("vector") << endl;
}

/**
  \title test parent-children tree
*/
void test_05()
{
    SObject* parent = new SObject();
    SObject* child = new SObject(parent);
    cout << child->property("toString");

    delete parent;
}

/**
  \title test Variant bridge SObject*
*/

void test_06()
{
    SObject* well = new SObject();

    well->setProperty("myName", "Well SObject");

    Variant wellVar;
    wellVar = well;

    cout << wellVar << endl;
    cout << wellVar.canConvert<SObject*>() << endl;
    cout << wellVar.value<SObject*>()->property("myName") << endl;

    VariantVector args;
    args.push_back(wellVar);

    Variant result;
    well->callMethod("isEqual", args, result);
    cout << result;

}

/**
  \title test callMethod time
*/
void internal_test_07_0()
{
    SObject* well = new SObject();

    VariantVector args;
    args.push_back(well);

    Variant result;
    for(int i=0; i<2000000; i++) {
        well->callMethod("isEqual", args, result);
    }
    cout << result << endl;
    delete well;
}

void internal_test_07_1()
{
    SObject* well = new SObject();
    bool result;
    for(int i=0; i<2000000; i++) {
        result = well->isEqual(well);
    }
    cout << result << endl;
    delete well;
}


void internal_test_07_2()
{
    SObject* well = new SObject();

    well->addMethod(
                "internal_test_07_1",
                [](SObject* thiz, VariantVector& , Variant& result){
        bool r = false;
        for(int i=0; i<2000000; i++) {
            r = thiz->isEqual(thiz);
        }
        result = r;
        return 0;
    });

    well->callSampleMethod("internal_test_07_1");
    delete well;
}

void test_07()
{
    cout << "unnative code"
         << test_function_time(internal_test_07_0)
         << " s" << endl;
    // 1.28607

    cout << "native code"
         <<
            test_function_time(internal_test_07_1)
         << " s" << endl;
    // 0.006

    cout << "register code"
         <<
            test_function_time(internal_test_07_2)
         << " s" << endl;
    //0.006001

    // 200 times
}



int main(
        // int argc, const char* argv[]
        )
{
    //*
//    test_01();
    cout << "------------------" << endl;
    test_02();
//    cout << "------------------" << endl;
//    test_03();
//    cout << "------------------" << endl;
//    test_04();
//    cout << "------------------" << endl;
//    test_05();
//    cout << "------------------" << endl;
//    test_06();
//    cout << "------------------" << endl;
//    TestVector2d::Test();
//    cout << "------------------" << endl;
    //*/
//    test_07();
    return 0;
}


