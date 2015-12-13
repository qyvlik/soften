#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <memory>
#include "../src/sobject.h"

class Utility
{
public:
    static int tryToUseBindArg(SObject* thiz, VariantVector& , Variant&) {
        //! thiz is nullptr
        std::cout << "tryToUseBindArg:" << thiz << std::endl;
        return 0;
    }

    static int doSomething(SObject* thiz, VariantVector& , Variant&) {
        std::cout << "doSomething: " << thiz->toString() << std::endl;
        return 0;
    }
};

template<typename ObjectClass>
class ObjectFactory
{
public:
    ~ObjectFactory();

    typedef std::shared_ptr<ObjectClass> shared;

    static shared create() {
        shared object(new ObjectClass);
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

        object->addMethod("doSomething", Utility::doSomething);

        object->addMethod("tryToUseBingArg",
                          bind(Utility::tryToUseBindArg,
                               nullptr, std::placeholders::_2, std::placeholders::_3));
        return object;
    }
private:
    ObjectFactory();
};

#endif // OBJECTFACTORY_H
