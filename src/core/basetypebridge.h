#ifndef BASETYPEBRIDGE_H
#define BASETYPEBRIDGE_H

#include "bridge.h"

namespace soften {

// base type

template<typename T>
class BaseTypeBridge : public Bridge
{
    //! static check
    static_assert(std::is_integral<T>::value, "type is not baseType");
    static_assert(!std::is_class<T>::value, "type is not baseType");
    static_assert(!std::is_union<T>::value, "type is not baseType");

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

private:
    std::shared_ptr<T> d;
    static std::shared_ptr<T> Null;
};

template<typename T> std::shared_ptr<T> BaseTypeBridge<T>::Null;


}

#endif // BASETYPEBRIDGE_H
