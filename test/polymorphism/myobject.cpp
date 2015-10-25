#include "myobject.h"
#include "../../src/core/bridge.h"

MyObject::Meta MyObject::metaCall = {
    {
        std::pair<const std::string, MyObject::Meta::Call>(
        "toString",
        [](MyObject* thiz, std::list<soften::Bridge*>, soften::Bridge*) -> int {
            std::cout << thiz->toString();
            return 0;
        })
    }
};


std::string MyObject::toString() const {
    return "MyObject::toString";
}
