#include "myobjectchild.h"
#include "../../src/core/bridge.h"

using namespace std;

MyObjectChild::Meta MyObjectChild::metaCall = {
    {
        // 可以在这里直接注册 MyObjectChild::toString
        // 但是由于 MyObjectChild::toString 的 virtual 特性
        // 可以不注册
        {
            pair<const string, MyObjectChild::Meta::Call> (
            "toString",
            [](MyObjectChild* thiz, std::vector<soften::Bridge*>, soften::Bridge*) -> int {
                cout << thiz->toString();
                return 0;
            })
        }
    }
};

std::string MyObjectChild::toString() const
{
    return "MyObjectChild::toString";
}
