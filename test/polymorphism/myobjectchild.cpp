#include "myobjectchild.h"

using namespace std;

MyObjectChild::Meta MyObjectChild::metaCall = {
    {
        {
            pair<const string, MyObjectChild::Meta::Call> (
            "toString",
            [](MyObjectChild* thiz, void*, void*) -> int {
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
