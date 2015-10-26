#include "assembler.h"

#include "../soften.h"
#include "../core/bridge.h"
#include "../core/basetypebridge.h"

#include <fstream>
#include <set>

using namespace std;

namespace soften {


Assembler::Assembler():
    m_cache(nullptr)
{

}


Assembler::~Assembler()
{
    set<Bridge*> delete_set;

    auto b = m_objectMap.begin();
    auto e = m_objectMap.end();
    while( b != e) {

        auto delete_result = delete_set.insert((*b).second);

        if(delete_result.second) {                              // 插入成功，既这个指针并未删除。
            cout << "delete " << (*b).second << endl;
            delete (*b).second;
        } else {
            cout << "mutil delte point" << (*b).second << endl;
        }

        b++;
    }
    m_objectMap.clear();
    m_cache = nullptr;
}


Bridge *Assembler::createBridgeFromStringValue(Assembler* thiz,const string &value)
{
    if(isalnum( value.at(0)) ) {
        int n = toNumber<int>(value);
        return new BaseTypeBridge<int>(new int(n));
    } else if(value.at(0) == '@') {
        string rhs_t = value;
        rhs_t.erase(0, 1);              // remove @
        auto find = thiz->m_objectMap.find(rhs_t);
        if(find == thiz->m_objectMap.end()) {
            thiz->setLastErrorString("NotDefine error");
            return nullptr;
        }
        Bridge* bridge = new BaseTypeBridge<int>();

        State s = bridge->ASSIGN((*find).second);
        if( s != State::NormalCall) {
            thiz->setLastErrorString("ASSIGN error");
            delete bridge;
            return nullptr;
        }
        return bridge;

        //! string
    } else if(value.at(0) == '"') {
        //! TODO
        return nullptr;

    } else {
        return nullptr;
    }
}

Assembler::Instruction Assembler::createInstruction(const string &operation,
                                                    const string &lhs,
                                                    const string &rhs)
{

    if(operation == "ASSIGN") {
        return Instruction(OP_ASSIGN, lhs, rhs);
    } else if(operation == "ASSIGN_BIT_OR") {
        return Instruction(OP_ASSIGN_BIT_OR, lhs, rhs);
    } else if(operation == "ASSIGN_BIT_XOR") {
        return Instruction(OP_ASSIGN_BIT_XOR, lhs, rhs);
    } else if(operation == "ASSIGN_BIT_AND") {
        return Instruction(OP_ASSIGN_BIT_AND, lhs, rhs);
    } else if(operation == "ASSIGN_SHL") {
        return Instruction(OP_ASSIGN_SHL, lhs, rhs);
    } else if(operation == "ASSIGN_SAR") {
        return Instruction(OP_ASSIGN_SAR, lhs, rhs);
    } else if(operation == "ASSIGN_ADD") {
        return Instruction(OP_ASSIGN_ADD, lhs, rhs);
    } else if(operation == "ASSIGN_SUB") {
        return Instruction(OP_ASSIGN_SUB, lhs, rhs);
    } else if(operation == "ASSIGN_MUL") {
        return Instruction(OP_ASSIGN_MUL, lhs, rhs);
    } else if(operation == "ASSIGN_DIV") {
        return Instruction(OP_ASSIGN_DIV, lhs, rhs);
    } else if(operation == "ASSIGN_MOD") {
        return Instruction(OP_ASSIGN_MOD, lhs, rhs);
    } else if(operation == "COMMA") {
        return Instruction(OP_COMMA, lhs, rhs);
    } else if(operation == "OR") {
        return Instruction(OP_OR, lhs, rhs);
    } else if(operation == "AND") {
        return Instruction(OP_AND, lhs, rhs);
    } else if(operation == "BIT_OR") {
        return Instruction(OP_BIT_OR, lhs, rhs);
    } else if(operation == "BIT_XOR") {
        return Instruction(OP_BIT_XOR, lhs, rhs);
    } else if(operation == "BIT_AND") {
        return Instruction(OP_BIT_AND, lhs, rhs);
    } else if(operation == "SHL") {
        return Instruction(OP_SHL, lhs, rhs);
    } else if(operation == "SAR") {
        return Instruction(OP_SAR, lhs, rhs);
    } else if(operation == "ADD") {
        return Instruction(OP_ADD, lhs, rhs);
    } else if(operation == "SUB") {
        return Instruction(OP_SUB, lhs, rhs);
    } else if(operation == "MUL") {
        return Instruction(OP_MUL, lhs, rhs);
    } else if(operation == "DIV") {
        return Instruction(OP_DIV, lhs, rhs);
    } else if(operation == "MOD") {
        return Instruction(OP_MOD, lhs, rhs);
    } else if(operation == "EQ") {
        return Instruction(OP_EQ, lhs, rhs);
    } else if(operation == "NE") {
        return Instruction(OP_NE, lhs, rhs);
    } else if(operation == "LT") {
        return Instruction(OP_LT, lhs, rhs);
    } else if(operation == "GT") {
        return Instruction(OP_GT, lhs, rhs);
    } else if(operation == "LTE") {
        return Instruction(OP_LTE, lhs, rhs);
    } else if(operation == "GTE") {
        return Instruction(OP_GTE, lhs, rhs);
    } else if(operation == "NOT") {
        return Instruction(OP_NOT, lhs, rhs);
    } else if(operation == "TYPEOF") {
        return Instruction(OP_TYPEOF, lhs, rhs);
    } else if(operation == "DECLARA") {
        return Instruction(OP_DECLARA, lhs, rhs);
    } else if(operation == "GOTO") {
        return Instruction(OP_GOTO, lhs, rhs);
    } else if(operation == "NEW") {
        return Instruction(OP_NEW, lhs, rhs);
    } else if(operation == "PUSH") {
        return Instruction(OP_PUSH, lhs, rhs);

    } else {
        return Instruction(OP_UNKNOWN, lhs, rhs);
    }
}


std::string Assembler::lastErrorString() const
{
    return m_lastErrorString;
}


/*
 * assemblerFile
 *
 * DECLARA @a 0
 * DECLARA @b 0
 *
*/

State Assembler::compile(const string &assemblerFile)
{
    ifstream file;
    file.open(assemblerFile);

    if(!file.is_open()) {
        return State::FileError;
    }

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

        m_instructions.push_back(Assembler::createInstruction(operation, lhs,rhs));
    }

    file.close();

    return State::NormalCall;
}


State Assembler::run()
{
    return State::NormalCall;
}


void Assembler::setLastErrorString(const std::string &lastErrorString)
{
    m_lastErrorString = lastErrorString;
}


/*
 * DECLARA @name @name2
 * DECLARA @name 1
 * DECLARA @name "string and string"
*/

State Assembler::DECLARA(const string lhs, const string &rhs)
{
    if(lhs.at(0) != '@') return State::NameError;   // haven't @

    string lhs_ = lhs;
    lhs_.erase(0, 1);                               // remove @

    if(m_objectMap.find(lhs_) != m_objectMap.end()) {
        setLastErrorString("MutilDefine");
        m_cache = nullptr;
        return State::MutilDefine;
    } else {
        Bridge* bridge = Assembler::createBridgeFromStringValue(this, rhs);
        if(bridge == nullptr) {
            m_cache = nullptr;
            return State::Unkonwn;
        }
        m_objectMap.insert(Variant(lhs_, bridge));

        // 指令执行后有状态值和返回值
        m_cache = bridge;

        return State::NormalCall;
    }
}


/*
// int a  = 10;
// int b;
// b = a;

DECLARA @a 10
DECLARA @b 0
ASSIGN @b @a
*/

State Assembler::ASSIGN(const string lhs, const string &rhs)
{
    string lhs_ = lhs;
    lhs_.erase(0, 1);
    string rhs_ = rhs;
    rhs_.erase(0, 1);
    auto targer = m_objectMap.find(lhs_);
    auto source = m_objectMap.find(rhs_);
    auto end = m_objectMap.end();

    if(targer != end && source != end) {

        // 指令执行后有状态值和返回值
        m_cache = (*targer).second;
        return (*targer).second->ASSIGN((*source).second);
    } else {
        setLastErrorString(lhs_ + " or "+ rhs_ +" NotDefine");

        // 指令执行后有状态值和返回值
        m_cache = nullptr;

        return State::NotDefine;
    }
}


}
