#include <iostream>

#include "polymorphism/myobject.h"
#include "polymorphism/myobjectchild.h"
#include "../src/core/basetypebridge.h"
#include "../src/core/bridge.h"
#include "../src/engine/assembler.h"

using namespace std;
using namespace soften;

void test_assembler();

int main()
{
    BaseTypeBridge<int> i(new int(10));
    Bridge* r = &i;

    BaseTypeBridge<int> arg0(new int(20));
    BaseTypeBridge<int> arg1(new int(20));

    vector<Bridge*> args;
    args.push_back(&arg0);
    args.push_back(&arg1);


    Object object;
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

    p->callMethod("add", args, r);
    cout << i.get() << endl;

    // assembler test
    test_assembler();



    return 0;
}


void test_assembler()
{
    Assembler assmbler;
    if(assmbler.DECLARA("name", "123") != soften::State::NormalCall) {
        cout << "error !" << endl;
    } else {
        cout << "success !" << endl;
    }

    if(assmbler.DECLARA("name1", "@name") != soften::State::NormalCall) {
        cout << "error !" << endl;
        cout << assmbler.lastErrorString() << endl;
    } else {
        cout << "success !" << endl;
    }

}
