#include <iostream>

#include "test-object-call/myobject.h"

#include "../src/core/bridge.h"

using namespace std;
using namespace soften;


int main(int , char** )
{
    Bridge<int> i0;
    Bridge<int> i1(new int(10));
    i0.ASSIGN(&i1);
    cout << i0 << endl;
    cout << i0.EQ(&i1) << endl;

    //return MyObject::main(argc, argv);
    return 0;
}
