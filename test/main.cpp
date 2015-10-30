#include <iostream>
#include <fstream>
#include <set>
#include <map>

#include <typeinfo>

#include "polymorphism/myobject.h"
#include "polymorphism/myobjectchild.h"
#include "../src/core/basetypebridge.h"
#include "../src/core/bridge.h"
#include "../src/engine/assembler.h"
#include "../src/core/functionmeta.h"

using namespace std;
using namespace soften;

void test_bridge();
void test_assembler_DECLARA();
void test_assembler_ASSIGN();
void test_assembler_cache();
void test_assmbler_sample_run();
void test_assembler_compiler();
void test_assembler_label();
void test_assembler_sample_GOTO();
void test_assembler_GOTO_LABEL();
void test_assembler_PUSH_ARGUEMNTS();
void test_assembler_CALL();
void test_function_meta();
void test_file_stream();
void test_set_insert();

int main(
        // int argc, const char* argv[]
        )
{
    test_assembler_CALL();
    return 0;
}


void test_bridge()
{
    BaseTypeBridge<int> i(10);
    Bridge* r = &i;

    BaseTypeBridge<int> arg0(20);
    BaseTypeBridge<int> arg1(20);

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


void test_assembler_DECLARA()
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
    assmbler.test_print_object_map();
}


void test_assembler_ASSIGN()
{
    Assembler assmbler;

    //! DECLARA @name 123

    if(assmbler.DECLARA("@name", "123") != soften::State::NormalCall) {
        cout << "DECLARA error !" << endl;
    } else {
        cout << "DECLARA success !" << endl;
    }

    //! DECLARA @name1 456
    if(assmbler.DECLARA("@name1", "456") != soften::State::NormalCall) {
        cout << "error !" << endl;
    } else {
        cout << "DECLARA success !" << endl;
    }

    assmbler.test_print_object_map();

    //! ASSIGN @name1 @name
    if(assmbler.ASSIGN("@name1", "@name") != soften::State::NormalCall) {
        cout << "ASSIGN error !" << endl;
        cout << assmbler.lastErrorString() << endl;
    } else {
        cout << "ASSIGN success !" << endl;
    }

    assmbler.test_print_object_map();
}


void test_assembler_cache()
{
    Assembler assmbler;

    //! DECLARA @name 123

    if(assmbler.DECLARA("@name", "123") != soften::State::NormalCall) {
        cout << "DECLARA error !" << endl;
    } else {
        cout << "DECLARA success !" << endl;
    }

    assmbler.test_print_cache();

    //! DECLARA @name1 456
    if(assmbler.DECLARA("@name1", "456") != soften::State::NormalCall) {
        cout << "error !" << endl;
    } else {
        cout << "DECLARA success !" << endl;
    }

    assmbler.test_print_cache();

    //! ASSIGN @name1 @notdefine
    //! NotDefine Error
    if(assmbler.ASSIGN("@name1", "@notdefine") != soften::State::NormalCall) {
        cout << "ASSIGN error !" << endl;
        cout << assmbler.lastErrorString() << endl;
    } else {
        cout << "ASSIGN success !" << endl;
    }

    assmbler.test_print_cache();
}


void test_assembler_label()
{
    Assembler assmbler;
    assmbler.compile("K://ass-lable.txt");
    assmbler.run();
    cout << "error:" << assmbler.lastErrorString() << endl;
    assmbler.test_print_object_map();
}


void test_assembler_sample_GOTO()
{
    Assembler assmbler;
    assmbler.GOTO("TRUE", "10000:10");
    cout << "error:" << assmbler.lastErrorString() << endl;
}


void test_assembler_GOTO_LABEL()
{
    Assembler assmbler;
    assmbler.compile("K://ass-goto-label.txt");
    if(assmbler.run() != State::NormalCall) {
        cout << "--------------" << endl
             << "assmbler run has error" << endl;
    }
    assmbler.test_print_labels();
    cout << "error:" << assmbler.lastErrorString() << endl;
    assmbler.test_print_object_map();
}


void test_assembler_PUSH_ARGUEMNTS()
{
    Assembler assmbler;
    assmbler.compile("K://ass-push-arguments.txt");
    if(assmbler.run() != State::NormalCall) {
        cout << "--------------" << endl
             << "assmbler run has error" << endl;
    }
    assmbler.test_print_arguments();
    cout << "error:" << assmbler.lastErrorString() << endl;
}


void test_assembler_CALL()
{
    Assembler assmbler;
    assmbler.compile("K://ass-call-object-method.txt");
    if(assmbler.run() != State::NormalCall) {
        cout << "--------------" << endl
             << "assmbler run has error" << endl;
        cout << "error:" << assmbler.lastErrorString() << endl;
        return ;
    }
    assmbler.test_print_arguments();
    cout << "error:" << assmbler.lastErrorString() << endl;
}


void test_assmbler_sample_run()
{
    Assembler assmbler;
    assmbler.compile("K://ass.txt");
    assmbler.run();
    cout << "error:" << assmbler.lastErrorString() << endl;
    assmbler.test_print_object_map();
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


void test_set_insert()
{
    set<int> int_set;
    auto insert_result = int_set.insert(10);
    insert_result = int_set.insert(10);
    cout << insert_result.second << endl;
    // 0 ==> false
}


void z1(int, int){}
typedef void(*z2)(int, int);
typedef void(*z3)();
typedef void(*z4)(void);

void test_function_meta()
{
    cout << FunctionMeta<decltype (z1)>::value << endl;             // 2
    cout << FunctionMeta<z2>::value << endl;                        // 2
    cout << FunctionMeta<z3>::value << endl;                        // 0
    cout << FunctionMeta<z4>::value <<  endl;                       // 0
    cout << FunctionMeta<decltype(Bridge::ADD)>::value << endl;     // 1

    typedef std::tuple_element<0, FunctionMeta<decltype (z1)>::ArgsTypeTuple >::type Type_Int;
    Type_Int i = 0;
    cout << i << endl;
}

