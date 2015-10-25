#include <iostream>
#include <fstream>
#include "polymorphism/myobject.h"
#include "polymorphism/myobjectchild.h"
#include "../src/core/basetypebridge.h"
#include "../src/core/bridge.h"
#include "../src/engine/assembler.h"

using namespace std;
using namespace soften;

void test_bridge();
void test_assembler();
void test_file_stream();
void test_assembler_compiler();

int main()
{
    test_assembler_compiler();
    return 0;
}


void test_bridge()
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


void test_file_stream()
{
    ifstream file;
    file.open("K://ass.txt");

    string single_instruction;
    string lhs;
    string operation;
    string rhs;
    int length;

    while(std::getline(file, single_instruction)) {
        length = single_instruction.length();
        if(length == 0) {
            continue;
        }
        int pos0 = 0;
        pos0 = single_instruction.find(' ', pos0);
        operation.assign(single_instruction, 0, pos0);

        int pos1 = single_instruction.find(' ', pos0+1);
        lhs.assign(single_instruction, pos0+1, pos1-pos0-1);

        rhs.assign(single_instruction, pos1+1, length-pos1-1);

        cout << operation << endl
             << lhs << endl
             << rhs << endl;
    }

    file.close();
}

void test_assembler_compiler()
{
    Assembler assmbler;
    assmbler.compile("K://ass.txt");
    assmbler.test_print_instrctions();
}
