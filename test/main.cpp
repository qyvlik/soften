#include <iostream>

#include "../src/sobject.h"

using namespace std;

class Factory
{
public:
    static SObject* create(int) {
        SObject* object = new SObject;
        object->setProperty("age", Variant(12));

        // int getAge();
        object->addMethod("getAge",
                          [](SObject* thiz, VariantVector&, Variant& result)->int{
            result = thiz->property("age");
            return 0;
        });

        // void setAge(int age);
        object->addMethod("setAge",
                          [](SObject* thiz, VariantVector& args, Variant&)->int{
            if(args.size() == 1) {
                // 这里可以做类型判断
                if(thiz->property("age").typeString()
                        == args.at(0).typeString()) {
                    thiz->setProperty("age", args.at(0));
                    return 0;
                } else {
                    return -2;
                }
            } else {
                return -1;
            }
        });

        object->addMethod("doSomething", Factory::doSomething);

        object->addMethod("tryToUseBingArg",
                          bind(Factory::tryToUseBindArg,
                               nullptr, std::placeholders::_2, std::placeholders::_3));

        return object;
    }

    static int tryToUseBindArg(SObject* thiz, VariantVector& , Variant&) {
        //! thiz is nullptr
        cout << "tryToUseBindArg:" << thiz <<endl;
        return 0;
    }

    static int doSomething(SObject* thiz, VariantVector& , Variant&) {
        cout << "doSomething: " <<thiz->toString() <<endl;
        return 0;
    }
};

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

    SObject *ageObject = Factory::create(0);

    ageObject->callMethod("getAge", arguments, result);

    cout << result << endl;


    ageObject->callMethod("setAge", arguments, result);

    ageObject->callMethod("getAge", arguments, result);

    cout << result << endl;

    ageObject->callMethod("doSomething");

    ageObject->callMethod("tryToUseBingArg");

    delete ageObject;
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

int main(
        // int argc, const char* argv[]
        )
{
    test_02();
    cout << "------------------" << endl;
    test_03();
    return 0;
}


