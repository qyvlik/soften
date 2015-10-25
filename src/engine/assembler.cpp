#include "assembler.h"

#include "../core/bridge.h"
#include "../core/basetypebridge.h"

#include <fstream>

using namespace std;

namespace soften {


Assembler::Assembler()
{

}


Assembler::~Assembler()
{
    auto b = m_objectMap.begin();
    auto e = m_objectMap.end();
    while( b != e) {

        cout << "delete " << (*b).second << endl;

        delete (*b).second;
        b++;
    }
    m_objectMap.clear();
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
        Bridge * bridge = new BaseTypeBridge<int>();

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

State Assembler::run(const string &assemblerFile)
{

    return State::Unkonwn;
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
    if(m_objectMap.find(lhs) != m_objectMap.end()) {
        setLastErrorString("MutilDefine");
        return State::MutilDefine;
    } else {
        Bridge* bridge = createBridgeFromStringValue(this, rhs);
        if(bridge == nullptr) {
            return State::Unkonwn;
        }
        m_objectMap.insert(Variant(lhs, bridge));
        return State::NormalCall;
    }
}


}
