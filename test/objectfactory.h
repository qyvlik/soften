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


// SObjectFactory is friend class of SObject
class ObjectFactory : public SObjectFactory
{
    static SObject parent;
public:

    SObject* create()
    {
        SObject* globalObject = new SObject(&parent);

        SObject* console = new SObject(globalObject);

        console->addMethod("log",
                           [](SObject* , VariantVector& args, Variant& result)->int{
            auto iter = args.begin();
            auto end = args.end();
            while(iter != end) {
                std::cout << (*iter).toStdString();
                iter++;
            }
            result = args.size();
            return 0;
        });

        globalObject->setProperty("age", Variant(12));

        // int getAge();
        globalObject->addMethod("getAge",
                          [](SObject* thiz, VariantVector&, Variant& result)->int{
            result = thiz->property("age");
            return 0;
        });

        // void setAge(int age);
        globalObject->addMethod("setAge",
                          [](SObject* thiz, VariantVector& args, Variant&)->int{
            if(args.size() == 1) {
                // 这里可以做类型判断
                if(thiz->property("age").typeString()
                        == args.at(0).typeString()) {
                    thiz->setProperty("age", args.at(0));
                    return ObjectMetaCallState::CallSuccess;
                } else {
                    return ObjectMetaCallState::ArgumentsTypeError;
                }
            } else {
                return ObjectMetaCallState::ArgumentsLengthError;
            }
        });

        globalObject->addMethod("doSomething", Utility::doSomething);

        globalObject->addMethod("tryToUseBingArg",
                          bind(Utility::tryToUseBindArg,
                               nullptr, std::placeholders::_2, std::placeholders::_3));

        globalObject->addMethod("print",
                                [console](SObject*, VariantVector& args, Variant&result)->int{
            return console->callMethod("log", args, result);
        });
        return globalObject;
    }
};

SObject ObjectFactory::parent;

#endif // OBJECTFACTORY_H
