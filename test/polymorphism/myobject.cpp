#include "myobject.h"
#include "../../src/core/basetypebridge.h"
#include "../../src/core/callhelper.h"

using namespace soften;


std::string MyObject::toString() const {
    return "MyObject::toString";
}

int MyObject::add(int a, int b)
{
    return a + b;
}


MyObject::Meta MyObject::metaCall = {
    {
        //        {
        //            std::pair<const std::string, MyObject::Meta::Call>(
        //            "toString",
        //            [](MyObject* thiz, std::vector<soften::Bridge*>, soften::Bridge*) -> int {
        //                std::cout << thiz->toString();
        //                return 0;
        //            })
        //        },
        {
            std::pair<const std::string, MyObject::Meta::Call>(
            "add",
            [](MyObject* thiz, std::vector<soften::Bridge*> args, soften::Bridge* r) -> int {
                // int(int, int);

                const int args_length = 2;

                if(args.size() <  args_length) {
                    return (int)soften::State::ArgumentsFail;
                }

                BaseTypeBridge<int>* arg0 = dynamic_cast<soften::BaseTypeBridge<int>*>(args[0]);
                BaseTypeBridge<int>* arg1 = dynamic_cast<soften::BaseTypeBridge<int>*>(args[1]);

                if(arg0 == nullptr || arg1 == nullptr) {
                    return (int)soften::State::ArgumentsFail;
                }

                int result = thiz->add(arg0->get(), arg1->get());

                soften::BaseTypeBridge<int> ret(result);

                if(r->ASSIGN(&ret) != soften::State::NormalCall) {
                    return (int)soften::State::ReturnFail;
                }
                return (int)soften::State::NormalCall;
            })
        }
    }
};


