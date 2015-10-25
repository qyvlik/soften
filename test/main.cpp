#include <iostream>

#include "polymorphism/myobject.h"
#include "polymorphism/myobjectchild.h"
#include "../src/core/basetypebridge.h"
#include "../src/core/bridge.h"

using namespace std;
using namespace soften;

int main()
{
    BaseTypeBridge<int> i(new int(10));

    Object object;
    list<Bridge*> args;
    Bridge* r = nullptr;
    object.callMethod("toString", args, r);

    cout << endl;

    MyObject myObject;
    myObject.callMethod("toString", args, r);

    cout << endl;

    Object* p = &myObject;
    p->callMethod("toString", args, r);

    cout << endl;

    MyObjectChild myObjectChild;
    myObjectChild.callMethod("toString", args, r);

    cout << endl;

    MyObject* p1 = &myObjectChild;
    p1->callMethod("toString", args, r);

    cout << endl;

    p = &myObjectChild;
    p->callMethod("toString", args, r);

    cout << endl;

    return 0;
}

