#ifndef BRIDGE_H
#define BRIDGE_H

#include <memory>
#include <map>
#include "object.h"

namespace soften {


class BridgeAbstract
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
    /*
    //virtual void ASSIGN_SHR(BridgeAbstract& other) = 0;            // T(ASSIGN_SHR, ">>>=", 2)
    */

    virtual void ASSIGN_ADD(BridgeAbstract* other) = 0;            // T(ASSIGN_ADD, "+=", 2)
    virtual void ASSIGN_SUB(BridgeAbstract* other) = 0;            // T(ASSIGN_SUB, "-=", 2)
    virtual void ASSIGN_MUL(BridgeAbstract* other) = 0;            // T(ASSIGN_MUL, "*=", 2)
    virtual void ASSIGN_DIV(BridgeAbstract* other) = 0;            // T(ASSIGN_DIV, "/=", 2)
    virtual void ASSIGN_MOD(BridgeAbstract* other) = 0;            // T(ASSIGN_MOD, "%=", 2)

    /*

    // virtual void COMMA(BridgeAbstract& other) = 0;                 // T(COMMA, ",", 1)
    virtual void OR(BridgeAbstract& other) = 0;                    // T(OR, "||", 4)
    virtual void AND(BridgeAbstract& other) = 0;                   // T(AND, "&&", 5)

    virtual void BIT_OR(BridgeAbstract& other) = 0;                // T(BIT_OR, "|", 6)
    virtual void BIT_XOR(BridgeAbstract& other) = 0;               // T(BIT_XOR, "^", 7)
    virtual void BIT_AND(BridgeAbstract& other) = 0;               // T(BIT_AND, "&", 8)
    virtual void SHL(BridgeAbstract& other) = 0;                   // T(SHL, "<<", 11)
    virtual void SAR(BridgeAbstract& other) = 0;                   // T(SAR, ">>", 11)

    // virtual void SHR(BridgeAbstract& other) = 0;                   // T(SHR, ">>>", 11)

    virtual void ADD(BridgeAbstract& other) = 0;                   // T(ADD, "+", 12)
    virtual void SUB(BridgeAbstract& other) = 0;                   // T(SUB, "-", 12)
    virtual void MUL(BridgeAbstract& other) = 0;                   // T(MUL, "*", 13)
    virtual void DIV(BridgeAbstract& other) = 0;                   // T(DIV, "/", 13)
    virtual void MOD(BridgeAbstract& other) = 0;                   // T(MOD, "%", 13)
    */
    virtual bool EQ(BridgeAbstract* other) = 0;                    // T(EQ, "==", 9)
    virtual bool NE(BridgeAbstract* other) = 0;                    // T(NE, "!=", 9)

    /*

    // virtual bool EQ_STRICT(BridgeAbstract& other) = 0;             // T(EQ_STRICT, "===", 9)
    // virtual bool NE_STRICT(BridgeAbstract& other) = 0;             // T(NE_STRICT, "!==", 9)

    virtual bool LT(BridgeAbstract& other) = 0;                    // T(LT, "<", 10)
    virtual bool GT(BridgeAbstract& other) = 0;                    // T(GT, ">", 10)
    virtual bool LTE(BridgeAbstract& other) = 0;                   // T(LTE, "<=", 10)
    virtual bool GTE(BridgeAbstract& other) = 0;                   // T(GTE, ">=", 10)
    // virtual bool INSTANCEOF(BridgeAbstract& other) = 0;            // K(INSTANCEOF, "instanceof", 10)

    virtual bool IN(BridgeAbstract& other) = 0;                    // K(IN, "in", 10)
    virtual void NOT(BridgeAbstract& other) = 0;                   // T(NOT, "!", 0)
    virtual void DELETE(BridgeAbstract& other) = 0;                // K(DELETE, "delete", 0)
    virtual void TYPEOF(BridgeAbstract& other) = 0;                // K(TYPEOF, "typeof", 0)
    virtual void VOID(BridgeAbstract& other) = 0;                  // K(VOID, "void", 0)
    */

    /*!
        先产生一个新的对象，然后赋值，接着执行操作。。。。。
        再将数据写会
    */
};


template<typename T> BridgeAbstract::Type toType() { return BridgeAbstract::Unknown; }

template<> BridgeAbstract::Type toType<bool>() { return BridgeAbstract::Boolean; }
template<> BridgeAbstract::Type toType<int>() { return BridgeAbstract::Integer; }
template<> BridgeAbstract::Type toType<float>() { return BridgeAbstract::Float; }
template<> BridgeAbstract::Type toType<double>() { return BridgeAbstract::Double; }
template<> BridgeAbstract::Type toType<long>() { return BridgeAbstract::Long; }
template<> BridgeAbstract::Type toType<long long>() { return BridgeAbstract::LongLong; }

template<> BridgeAbstract::Type toType<std::string>() { return BridgeAbstract::String; }

template<> BridgeAbstract::Type toType<soften::Object>() { return BridgeAbstract::Object; }

// base type

template<typename T>
class BaseTypeBridge : public BridgeAbstract
{
public:
    friend std::ostream& operator << (std::ostream& os, const BaseTypeBridge& obj)
    { return os << "(" << obj.d.get() << ", " << *obj.d.get() << ")"; }

    T* operator->()
    { return d.get();}

protected:
    static std::pair<bool, std::shared_ptr<T> >
    getSharedPoint(BridgeAbstract *other)
    {
        BaseTypeBridge<T>* p = dynamic_cast<BaseTypeBridge<T>*>(other);
        return std::pair<bool, std::shared_ptr<T> >
                (p != nullptr,
                 p != nullptr ? p->d : Null);
    }
public:
    explicit BaseTypeBridge():
        d(new T)
    { }

    BaseTypeBridge(T* thiz ):
        d(thiz)
    { }

    BaseTypeBridge(const BaseTypeBridge& other)
        : d(other.d)
    { }

    BaseTypeBridge& operator=(const BaseTypeBridge& other) {
        this->d = other.d;
        return *this;
    }

    ~BaseTypeBridge()
    { }

    BaseTypeBridge(BaseTypeBridge&& other)
        : d(other.d)
    { }

    Type type() const
    { return toType<T>(); }

    virtual Return ASSIGN(BridgeAbstract* other)                 // T(ASSIGN, "=", 2)
    {
        if(isValid(other)) {
            if(isBaseType(this->type())) {
                *d = *(dynamic_cast<BaseTypeBridge<T>* >(other)->d);
                std::shared_ptr<BridgeAbstract> r_d((BridgeAbstract*)Null.get());
                return Return(State::NormalCall, r_d);
            } else {
                std::cout << "Unknown type" << std::endl;
                std::shared_ptr<BridgeAbstract> r_d((BridgeAbstract*)Null.get());
                return Return(State::NormalCall, r_d);
            }
        } else {
            std::shared_ptr<BridgeAbstract> r_d((BridgeAbstract*)Null.get());
            return Return(State::NormalCall, r_d);
        }
    }

    virtual Return ASSIGN_BIT_OR(BridgeAbstract* other)       // T(ASSIGN_BIT_OR, "|=", 2)
    {
        if(isValid(other)) {
            if(isBaseType(this->type())) {
                *d |= *(dynamic_cast<BaseTypeBridge<T>* >(other)->d);
                std::shared_ptr<BridgeAbstract> r_d((BridgeAbstract*)Null.get());
                return Return(State::NormalCall, r_d);
            } else {
                std::cout << "Unknown type" << std::endl;
                std::shared_ptr<BridgeAbstract> r_d((BridgeAbstract*)Null.get());
                return Return(State::NormalCall, r_d);
            }
        } else {
            std::cout << "Unknown type" << std::endl;
            std::shared_ptr<BridgeAbstract> r_d((BridgeAbstract*)Null.get());
            return Return(State::NormalCall, r_d);
        }
    }

    virtual Return ASSIGN_BIT_XOR(BridgeAbstract* other)         // T(ASSIGN_BIT_XOR, "^=", 2)
    {
        if(isValid(other)) {
            if(isBaseType(this->type())) {
                *d ^= *(dynamic_cast<BaseTypeBridge<T>* >(other)->d);
                std::shared_ptr<BridgeAbstract> r_d((BridgeAbstract*)Null.get());
                return Return(State::NormalCall, r_d);
            } else {
                std::cout << "Unknown type" << std::endl;
                std::shared_ptr<BridgeAbstract> r_d((BridgeAbstract*)Null.get());
                return Return(State::NormalCall, r_d);
            }
        } else {
            std::cout << "Unknown type" << std::endl;
            std::shared_ptr<BridgeAbstract> r_d((BridgeAbstract*)Null.get());
            return Return(State::NormalCall, r_d);
        }
    }

    virtual Return ASSIGN_BIT_AND(BridgeAbstract* other)         // T(ASSIGN_BIT_AND, "&=", 2)
    {
        if(isValid(other)) {
            if(isBaseType(this->type())) {
                *d &= *(dynamic_cast<BaseTypeBridge<T>* >(other)->d);
                std::shared_ptr<BridgeAbstract> r_d((BridgeAbstract*)Null.get());
                return Return(State::NormalCall, r_d);
            } else {
                std::cout << "Unknown type" << std::endl;
                std::shared_ptr<BridgeAbstract> r_d((BridgeAbstract*)Null.get());
                return Return(State::NormalCall, r_d);
            }
        } else {
            std::cout << "Unknown type" << std::endl;
            std::shared_ptr<BridgeAbstract> r_d((BridgeAbstract*)Null.get());
            return Return(State::NormalCall, r_d);
        }
    }

    virtual Return ASSIGN_SHL(BridgeAbstract* other)             // T(ASSIGN_SHL, "<<=", 2)
    {
        if(isValid(other)) {
            if(isBaseType(this->type())) {
                *d <<= *(dynamic_cast<BaseTypeBridge<T>* >(other)->d);
                std::shared_ptr<BridgeAbstract> r_d((BridgeAbstract*)Null.get());
                return Return(State::NormalCall, r_d);
            } else {
                std::cout << "Unknown type" << std::endl;
                std::shared_ptr<BridgeAbstract> r_d((BridgeAbstract*)Null.get());
                return Return(State::NormalCall, r_d);
            }
        } else {
            std::cout << "Unknown type" << std::endl;
            std::shared_ptr<BridgeAbstract> r_d((BridgeAbstract*)Null.get());
            return Return(State::NormalCall, r_d);
        }
    }

    virtual Return ASSIGN_SAR(BridgeAbstract* other)            // T(ASSIGN_SAR, ">>=", 2)
    {
        if(isValid(other)) {
            if(isBaseType(this->type())) {
                *d >>= *(dynamic_cast<BaseTypeBridge<T>* >(other)->d);
                std::shared_ptr<BridgeAbstract> r_d((BridgeAbstract*)Null.get());
                return Return(State::NormalCall, r_d);
            } else {
                std::cout << "Unknown type" << std::endl;
                std::shared_ptr<BridgeAbstract> r_d((BridgeAbstract*)Null.get());
                return Return(State::NormalCall, r_d);
            }
        } else {
            std::cout << "Unknown type" << std::endl;
            std::shared_ptr<BridgeAbstract> r_d((BridgeAbstract*)Null.get());
            return Return(State::NormalCall, r_d);
        }
    }

    /*
    //virtual void ASSIGN_SHR(BridgeAbstract& other) = 0;            // T(ASSIGN_SHR, ">>>=", 2)
   */

    virtual void ASSIGN_ADD(BridgeAbstract* other)           // T(ASSIGN_ADD, "+=", 2)
    {
        if(isValid(other)) {
            if(isBaseType(this->type())) {
                *d += *(dynamic_cast<BaseTypeBridge<T>* >(other)->d);
            } else if(isComplexType(this->type())) {
                *d += *(dynamic_cast<BaseTypeBridge<T>* >(other)->d);
            } else {
                std::cout << "OBJECT type" << std::endl;
            }
        }
    }

    virtual void ASSIGN_SUB(BridgeAbstract* other)             // T(ASSIGN_SUB, "-=", 2)
    {
        if(isValid(other)) {
            if(isBaseType(this->type())) {
                *d -= *(dynamic_cast<BaseTypeBridge<T>* >(other)->d);
            } else {
                std::cout << "Unkonwn type" << std::endl;
            }
        }
    }

    virtual void ASSIGN_MUL(BridgeAbstract* other)         // T(ASSIGN_MUL, "*=", 2)
    {
        if(isValid(other)) {
            if(isBaseType(this->type())) {
                *d *= *(dynamic_cast<BaseTypeBridge<T>* >(other)->d);
            } else {
                std::cout << "Unkonwn type" << std::endl;
            }
        }
    }

    virtual void ASSIGN_DIV(BridgeAbstract* other)           // T(ASSIGN_DIV, "/=", 2)
    {
        if(isValid(other)) {
            if(isBaseType(this->type())) {
                *d /= *(dynamic_cast<BaseTypeBridge<T>* >(other)->d);
            } else {
                std::cout << "Unkonwn type" << std::endl;
            }
        }
    }

    virtual void ASSIGN_MOD(BridgeAbstract* other)            // T(ASSIGN_MOD, "%=", 2)
    {
        if(isValid(other)) {
            if(isBaseType(this->type())) {
                *d %= *(dynamic_cast<BaseTypeBridge<T>* >(other)->d);
            } else {
                std::cout << "Unkonwn type" << std::endl;
            }
        }
    }

    /*
    // virtual void COMMA(BridgeAbstract& other) = 0;                 // T(COMMA, ",", 1)
    virtual void OR(BridgeAbstract& other) = 0;                    // T(OR, "||", 4)
    virtual void AND(BridgeAbstract& other) = 0;                   // T(AND, "&&", 5)
    virtual void BIT_OR(BridgeAbstract& other) = 0;                // T(BIT_OR, "|", 6)
    virtual void BIT_XOR(BridgeAbstract& other) = 0;               // T(BIT_XOR, "^", 7)
    virtual void BIT_AND(BridgeAbstract& other) = 0;               // T(BIT_AND, "&", 8)
    virtual void SHL(BridgeAbstract& other) = 0;                   // T(SHL, "<<", 11)
    virtual void SAR(BridgeAbstract& other) = 0;                   // T(SAR, ">>", 11)
    //virtual void SHR(BridgeAbstract& other) = 0;                   // T(SHR, ">>>", 11)
    virtual void ADD(BridgeAbstract& other) = 0;                   // T(ADD, "+", 12)
    virtual void SUB(BridgeAbstract& other) = 0;                   // T(SUB, "-", 12)
    virtual void MUL(BridgeAbstract& other) = 0;                   // T(MUL, "*", 13)
    virtual void DIV(BridgeAbstract& other) = 0;                   // T(DIV, "/", 13)
    virtual void MOD(BridgeAbstract& other) = 0;                   // T(MOD, "%", 13)
*/

    virtual bool EQ(BridgeAbstract* other)                    // T(EQ, "==", 9)
    {
        if(this == other) return true;

        if(isValid(other)) {
            return *d == *(dynamic_cast<BaseTypeBridge<T>* >(other)->d);
        } else {
            return false;
        }
    }

    virtual bool NE(BridgeAbstract* other)                   // T(NE, "!=", 9)
    {
        return !this->EQ(other);
    }

    /*

    // virtual bool EQ_STRICT(BridgeAbstract& other) = 0;             // T(EQ_STRICT, "===", 9)
    // virtual bool NE_STRICT(BridgeAbstract& other) = 0;             // T(NE_STRICT, "!==", 9)

    virtual bool LT(BridgeAbstract& other) = 0;                    // T(LT, "<", 10)
    virtual bool GT(BridgeAbstract& other) = 0;                    // T(GT, ">", 10)
    virtual bool LTE(BridgeAbstract& other) = 0;                   // T(LTE, "<=", 10)
    virtual bool GTE(BridgeAbstract& other) = 0;                   // T(GTE, ">=", 10)
    // virtual bool INSTANCEOF(BridgeAbstract& other) = 0;            // K(INSTANCEOF, "instanceof", 10)

    virtual bool IN(BridgeAbstract& other) = 0;                    // K(IN, "in", 10)
    virtual void NOT(BridgeAbstract& other) = 0;                   // T(NOT, "!", 0)
    virtual void DELETE(BridgeAbstract& other) = 0;                // K(DELETE, "delete", 0)
    virtual void TYPEOF(BridgeAbstract& other) = 0;                // K(TYPEOF, "typeof", 0)
    virtual void VOID(BridgeAbstract& other) = 0;                  // K(VOID, "void", 0)
*/

private:
    std::shared_ptr<T> d;
    static std::shared_ptr<T> Null;
};

template<typename T> std::shared_ptr<T> BaseTypeBridge<T>::Null;

}

#endif // BRIDGE_H
