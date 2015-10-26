#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include "../core/metacall.h"
#include "../core/bridge.h"

namespace soften {


class Bridge;
class Assembler
{
public:
    enum OP {
        OP_ASSIGN,                      // T(ASSIGN, "=", 2)

        OP_ASSIGN_BIT_OR,               // T(ASSIGN_BIT_OR, "|=", 2)
        OP_ASSIGN_BIT_XOR,              // T(ASSIGN_BIT_XOR, "^=", 2)
        OP_ASSIGN_BIT_AND,              // T(ASSIGN_BIT_AND, "&=", 2)
        OP_ASSIGN_SHL,                  // T(ASSIGN_SHL, "<<=", 2)
        OP_ASSIGN_SAR,                  // T(ASSIGN_SAR, ">>=", 2)

        OP_ASSIGN_ADD,                  // T(ASSIGN_ADD, "+=", 2)
        OP_ASSIGN_SUB,                  // T(ASSIGN_SUB, "-=", 2)
        OP_ASSIGN_MUL,                  // T(ASSIGN_MUL, "*=", 2)
        OP_ASSIGN_DIV,                  // T(ASSIGN_DIV, "/=", 2)
        OP_ASSIGN_MOD,                  // T(ASSIGN_MOD, "%=", 2)

        OP_COMMA,                       // T(COMMA, ",", 1)
        OP_OR,                          // T(OR, "||", 4)
        OP_AND,                         // T(AND, "&&", 5)

        OP_BIT_OR,                      // T(BIT_OR, "|", 6)
        OP_BIT_XOR,                     // T(BIT_XOR, "^", 7)
        OP_BIT_AND,                     // T(BIT_AND, "&", 8)
        OP_SHL,                         // T(SHL, "<<", 11)
        OP_SAR,                         // T(SAR, ">>", 11)

        OP_ADD,                         // T(ADD, "+", 12)
        OP_SUB,                         // T(SUB, "-", 12)
        OP_MUL,                         // T(MUL, "*", 13)
        OP_DIV,                         // T(DIV, "/", 13)
        OP_MOD,                         // T(MOD, "%", 13)

        OP_EQ,                          // T(EQ, "==", 9)
        OP_NE,                          // T(NE, "!=", 9)

        OP_LT,                          // T(LT, "<", 10)
        OP_GT,                          // T(GT, ">", 10)
        OP_LTE,                         // T(LTE, "<=", 10)
        OP_GTE,                         // T(GTE, ">=", 10)

        OP_NOT,                         // T(NOT, "!", 0)
        OP_TYPEOF,                      // K(TYPEOF, "typeof", 0)

        OP_DECLARA,
        OP_GOTO,
        OP_NEW,
        OP_PUSH,
        OP_LABEL,                       // 标签
        OP_UNKNOWN
    };

    struct Instruction {
        OP operation;
        std::string lhs;
        std::string rhs;
        Instruction(OP operation, const std::string& lhs, const std::string& rhs) :
            operation(operation),
            lhs(lhs),
            rhs(rhs)
        { }

    };

    explicit Assembler();

    virtual ~Assembler();

    std::string lastErrorString() const;

    State compile(const std::string& assemblerFile);

    State run();

    //! run instrctions ASSIGN

    State DECLARA(const std::string lhs,const std::string& rhs);

    State ASSIGN(const std::string lhs,const std::string& rhs);



    //@ TEST
    void test_print_instrctions() {
        for(unsigned int i=0; i< m_instructions.size(); i++) {
            std::cout << m_instructions.at(i).operation << std::endl
                      << m_instructions.at(i).lhs << std::endl
                      << m_instructions.at(i).rhs << std::endl
                      << std::endl;
        }
    }

    //@ TEST
    void test_print_object_map() {
        auto iter = m_objectMap.begin();
        auto end = m_objectMap.end();
        while(iter != end) {
            std::cout <<  (*iter).first << " " << (*iter).second->toString() << std::endl;
            iter++;
        }
    }

    //@ TEST
    void test_print_cache() {
        if(m_cache) {
            std::cout << m_cache->toString() << std::endl;
        } else {
            std::cout << "error: " << std::endl;
            std::cout << this->lastErrorString() << std::endl;
        }
    }

protected:

    void setLastErrorString(const std::string &lastErrorString);

    static Bridge* createBridgeFromStringValue(Assembler *thiz, const std::string& value);

    static Assembler::Instruction createInstruction(const std::string& operation,
                                                    const std::string& lhs,
                                                    const std::string& rhs);

private:

    typedef std::pair<std::string, Bridge*> Variant;

    std::vector<Instruction> m_instructions;
    int process_count;
    std::map<std::string, Bridge*> m_objectMap;

    std::string m_lastErrorString;

    std::vector<Bridge*> m_arguments;
    Bridge* m_cache;

};


}

#endif // ASSEMBLER_H
