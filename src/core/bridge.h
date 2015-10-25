#ifndef BRIDGE_H
#define BRIDGE_H

#include <memory>
#include <map>
#include "object.h"

namespace soften {


class BridgeAbstract : virtual public Object
{
public:
    enum Type {

        /*! base type   */
        Boolean,
        Integer,
        Double,
        Float,
        Long,
        LongLong,

        /*! complex type */
        String,

        /*! object  type */
        Object,

        /*! Unknown type */
        Unknown
    };

    static bool isBaseType(Type type)
    {
        switch(type)
        {
        case Boolean:
        case Integer:
        case Double:
        case Float:
        case Long:
        case LongLong:
            return true;
        default:
            return false;
        }
    }

    static bool isComplexType(Type type)
    {
        switch(type)
        {
        case Type::String: return true;
            // ...
        default: return false;
        }
    }

    static bool isObjectType(Type type)
    { return type == Type::Object; }

    typedef std::pair<soften::State, std::shared_ptr<BridgeAbstract> > Return;

    virtual ~BridgeAbstract()
    { }

    virtual Type type() const = 0;

    bool isValid(BridgeAbstract* other)
    { return other->type() == this->type() && this->type() != Type::Unknown; }

    virtual Return ASSIGN(BridgeAbstract* other) = 0;                // T(ASSIGN, "=", 2)

    virtual Return ASSIGN_BIT_OR(BridgeAbstract* other) = 0;         // T(ASSIGN_BIT_OR, "|=", 2)
    virtual Return ASSIGN_BIT_XOR(BridgeAbstract* other) = 0;        // T(ASSIGN_BIT_XOR, "^=", 2)
    virtual Return ASSIGN_BIT_AND(BridgeAbstract* other) = 0;        // T(ASSIGN_BIT_AND, "&=", 2)
    virtual Return ASSIGN_SHL(BridgeAbstract* other) = 0;            // T(ASSIGN_SHL, "<<=", 2)
    virtual Return ASSIGN_SAR(BridgeAbstract* other) = 0;            // T(ASSIGN_SAR, ">>=", 2)

    virtual Return ASSIGN_ADD(BridgeAbstract* other) = 0;            // T(ASSIGN_ADD, "+=", 2)
    virtual Return ASSIGN_SUB(BridgeAbstract* other) = 0;            // T(ASSIGN_SUB, "-=", 2)
    virtual Return ASSIGN_MUL(BridgeAbstract* other) = 0;            // T(ASSIGN_MUL, "*=", 2)
    virtual Return ASSIGN_DIV(BridgeAbstract* other) = 0;            // T(ASSIGN_DIV, "/=", 2)
    virtual Return ASSIGN_MOD(BridgeAbstract* other) = 0;            // T(ASSIGN_MOD, "%=", 2)

    virtual Return COMMA(BridgeAbstract* other) = 0;                 // T(COMMA, ",", 1)
    virtual Return OR(BridgeAbstract* other) = 0;                    // T(OR, "||", 4)
    virtual Return AND(BridgeAbstract* other) = 0;                   // T(AND, "&&", 5)

    virtual Return BIT_OR(BridgeAbstract* other) = 0;                // T(BIT_OR, "|", 6)
    virtual Return BIT_XOR(BridgeAbstract* other) = 0;               // T(BIT_XOR, "^", 7)
    virtual Return BIT_AND(BridgeAbstract* other) = 0;               // T(BIT_AND, "&", 8)
    virtual Return SHL(BridgeAbstract* other) = 0;                   // T(SHL, "<<", 11)
    virtual Return SAR(BridgeAbstract* other) = 0;                   // T(SAR, ">>", 11)

    // virtual void SHR(BridgeAbstract* other) = 0;                   // T(SHR, ">>>", 11)

    virtual Return ADD(BridgeAbstract* other) = 0;                   // T(ADD, "+", 12)
    virtual Return SUB(BridgeAbstract* other) = 0;                   // T(SUB, "-", 12)
    virtual Return MUL(BridgeAbstract* other) = 0;                   // T(MUL, "*", 13)
    virtual Return DIV(BridgeAbstract* other) = 0;                   // T(DIV, "/", 13)
    virtual Return MOD(BridgeAbstract* other) = 0;                   // T(MOD, "%", 13)

    virtual Return EQ(BridgeAbstract* other) = 0;                    // T(EQ, "==", 9)
    virtual Return NE(BridgeAbstract* other) = 0;                    // T(NE, "!=", 9)

    virtual Return LT(BridgeAbstract* other) = 0;                    // T(LT, "<", 10)
    virtual Return GT(BridgeAbstract* other) = 0;                    // T(GT, ">", 10)
    virtual Return LTE(BridgeAbstract* other) = 0;                   // T(LTE, "<=", 10)
    virtual Return GTE(BridgeAbstract* other) = 0;                   // T(GTE, ">=", 10)
    // virtual Return INSTANCEOF(BridgeAbstract* other) = 0;            // K(INSTANCEOF, "instanceof", 10)

    virtual Return IN(BridgeAbstract* other) = 0;                    // K(IN, "in", 10)
    virtual Return NOT(BridgeAbstract* other) = 0;                   // T(NOT, "!", 0)
    virtual Return DELETE(BridgeAbstract* other) = 0;                // K(DELETE, "delete", 0)
    virtual Return TYPEOF(BridgeAbstract* other) = 0;                // K(TYPEOF, "typeof", 0)
    virtual Return VOID(BridgeAbstract* other) = 0;                  // K(VOID, "void", 0)

    /*!
        先产生一个新的对象，然后赋值，接着执行操作。。。。。
        再将数据写会
    */
};


class Bridge : virtual public BridgeAbstract
{
public:
    explicit Bridge()
    {}
    virtual ~Bridge()
    {}

    virtual Type type() const
    {  return BridgeAbstract::Unknown; }

    // T(ASSIGN, "=", 2)
    virtual Return ASSIGN(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(ASSIGN_BIT_OR, "|=", 2)
    virtual Return ASSIGN_BIT_OR(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(ASSIGN_BIT_XOR, "^=", 2)
    virtual Return ASSIGN_BIT_XOR(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }
    // T(ASSIGN_BIT_AND, "&=", 2)
    virtual Return ASSIGN_BIT_AND(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(ASSIGN_SHL, "<<=", 2)
    virtual Return ASSIGN_SHL(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(ASSIGN_SAR, ">>=", 2)
    virtual Return ASSIGN_SAR(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(ASSIGN_ADD, "+=", 2)
    virtual Return ASSIGN_ADD(BridgeAbstract* ){
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(ASSIGN_SUB, "-=", 2)
    virtual Return ASSIGN_SUB(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(ASSIGN_MUL, "*=", 2)
    virtual Return ASSIGN_MUL(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(ASSIGN_DIV, "/=", 2)
    virtual Return ASSIGN_DIV(BridgeAbstract* ){
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(ASSIGN_MOD, "%=", 2)
    virtual Return ASSIGN_MOD(BridgeAbstract* ){
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(COMMA, ",", 1)
    virtual Return COMMA(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(OR, "||", 4)
    virtual Return OR(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(AND, "&&", 5)
    virtual Return AND(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(BIT_OR, "|", 6)
    virtual Return BIT_OR(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(BIT_XOR, "^", 7)
    virtual Return BIT_XOR(BridgeAbstract* ){
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(BIT_AND, "&", 8)
    virtual Return BIT_AND(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(SHL, "<<", 11)
    virtual Return SHL(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(SAR, ">>", 11)
    virtual Return SAR(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(ADD, "+", 12)
    virtual Return ADD(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(SUB, "-", 12)
    virtual Return SUB(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(MUL, "*", 13)
    virtual Return MUL(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(DIV, "/", 13)
    virtual Return DIV(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(MOD, "%", 13)
    virtual Return MOD(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(EQ, "==", 9)
    virtual Return EQ(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(NE, "!=", 9)
    virtual Return NE(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(LT, "<", 10)
    virtual Return LT(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(GT, ">", 10)
    virtual Return GT(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(LTE, "<=", 10)
    virtual Return LTE(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(GTE, ">=", 10)
    virtual Return GTE(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // virtual Return INSTANCEOF(BridgeAbstract* other) = 0;            // K(INSTANCEOF, "instanceof", 10)

    // K(IN, "in", 10)
    virtual Return IN(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // T(NOT, "!", 0)
    virtual Return NOT(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // K(DELETE, "delete", 0)
    virtual Return DELETE(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // K(TYPEOF, "typeof", 0)
    virtual Return TYPEOF(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }

    // K(VOID, "void", 0)
    virtual Return VOID(BridgeAbstract* ) {
        return Return(soften::State::CastFail,
                      std::shared_ptr<BridgeAbstract>(new Bridge()));
    }
};




}

#endif // BRIDGE_H
