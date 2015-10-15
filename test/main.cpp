#include <iostream>

#include "test-object-call/myobject.h"

#include "../src/core/bridge.h"

using namespace std;
using namespace soften;


int main(int argc, char** argv)
{
    BaseTypeBridge<int> i0;
    BaseTypeBridge<int> i1(new int(10));

    i0.ASSIGN(&i1) ;

    BaseTypeBridge<int> ui1(new int(10));
    BaseTypeBridge<int> ui2(new int(1));
    ui1.ASSIGN_BIT_OR(&ui2);

    cout << ui1 << endl;

//    cout << i0 << endl;
//    cout << i0.EQ(&i1) << endl;

    return MyObject::main(argc, argv);
    return 0;
}
