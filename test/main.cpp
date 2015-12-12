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
                thiz->setProperty("age", args.at(0));
                return 0;
            } else {
                return -1;
            }
        });
        return object;
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

    arguments.push_back(Variant(19));

    ageObject->callMethod("setAge", arguments, result);

    ageObject->callMethod("getAge", arguments, result);

    cout << result << endl;

    delete ageObject;
}

int main(
        // int argc, const char* argv[]
        )
{

    test_02();
    return 0;
}


