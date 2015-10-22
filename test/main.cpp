#include <iostream>

#include "polymorphism/myobject.h"
#include "polymorphism/myobjectchild.h"

#include "../src/core/bridge.h"

using namespace std;
using namespace soften;

int main()
{
    Object object;
    object.callMethod("toString", (void*)0x1, (void*)0x1);

    cout << endl;

    MyObject myObject;
    myObject.callMethod("toString", (void*)0x1, (void*)0x1);

    cout << endl;

    Object* p = &myObject;
    p->callMethod("toString", (void*)0x1, (void*)0x1);

    cout << endl;

    MyObjectChild myObjectChild;
    myObjectChild.callMethod("toString", (void*)0, (void*)0);

    cout << endl;

    MyObject* p1 = &myObjectChild;
    p1->callMethod("toString", (void*)0, (void*)0);

    cout << endl;

    p = &myObjectChild;
    p->callMethod("toString", (void*)0x1, (void*)0x1);

    cout << endl;

    return 0;
}

