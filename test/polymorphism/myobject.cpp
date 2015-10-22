#include "myobject.h"

MyObject::Meta MyObject::metaCall = {
    {
        std::pair<const std::string, MyObject::Meta::Call>(
        "toString",
        [](MyObject* thiz, void*, void*) -> int {
            std::cout << thiz->toString();
            return 0;
        })
    }
};


std::string MyObject::toString() const {
    return "MyObject::toString";
}
