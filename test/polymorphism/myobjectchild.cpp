#include "myobjectchild.h"
#include "../../src/core/bridge.h"

using namespace std;

MyObjectChild::Meta MyObjectChild::metaCall = {
    {
        {
            pair<const string, MyObjectChild::Meta::Call> (
            "toString",
            [](MyObjectChild* thiz, std::list<soften::Bridge*>, soften::Bridge*) -> int {
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
