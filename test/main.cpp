#include <iostream>

#include "../src/sobject.h"
#include "myobject.h"
#include "objectfactory.h"
#include "test_vector2d.h"

using namespace std;

void test_01() {
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

    auto ageObject = ObjectFactory<SObject>::create();

    ageObject->callMethod("getAge", arguments, result);

    cout << result << endl;

    ageObject->callMethod("setAge", arguments, result);

    ageObject->callMethod("getAge", arguments, result);

    cout << result << endl;

    ageObject->callSampleMethod("doSomething");

    ageObject->callSampleMethod("tryToUseBingArg");
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

void test_4()
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

int main(
        // int argc, const char* argv[]
        )
{
    test_02();
    cout << "------------------" << endl;
    test_03();
    cout << "------------------" << endl;
    test_4();
    TestVector2d::Test();
    return 0;
}


