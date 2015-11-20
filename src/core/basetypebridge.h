#ifndef BASETYPEBRIDGE_H
#define BASETYPEBRIDGE_H

#include "bridge.h"

namespace soften {


//! [C++ 函数模板特化导致的多重定义链接错误](http://blog.csdn.net/ztz0223/article/details/9699295)

template<typename T> BridgeAbstract::Type toType() { return BridgeAbstract::Unknown; }

template<> BridgeAbstract::Type inline toType<bool>() { return BridgeAbstract::Boolean; }
template<> BridgeAbstract::Type inline toType<int>() { return BridgeAbstract::Integer; }
template<> BridgeAbstract::Type inline toType<float>() { return BridgeAbstract::Float; }
template<> BridgeAbstract::Type inline toType<double>() { return BridgeAbstract::Double; }
template<> BridgeAbstract::Type inline toType<long>() { return BridgeAbstract::Long; }
template<> BridgeAbstract::Type inline toType<long long>() { return BridgeAbstract::LongLong; }

template<> BridgeAbstract::Type inline toType<std::string>() { return BridgeAbstract::String; }


// base type

template<typename T>
class BaseTypeBridge : public Bridge
{
    //! static check
    // static_assert(std::is_integral<T>::value, "type is not baseType");
    static_assert(!std::is_class<T>::value, "type is not baseType");
    static_assert(!std::is_union<T>::value, "type is not baseType");
    static_assert(!std::is_pointer<T>::value, "Type Error");
    static_assert(!std::is_reference<T>::value, "Type Error");

public:

    T get() {
        return this->data;
    }

    const T get() const {
        return this->data;
    }

public:
    explicit BaseTypeBridge()
    { }

    explicit BaseTypeBridge(const T& data):
        data(data)
    { }

    BaseTypeBridge(const BaseTypeBridge& other)
        : data(other.data)
    { }

    BaseTypeBridge& operator=(const BaseTypeBridge& other) {
        this->data = other.data;
        return *this;
    }

    ~BaseTypeBridge()
    { }

    BaseTypeBridge(BaseTypeBridge&& other)
        : data(other.data)
    { }

    Type type() const
    { return toType<T>(); }

    // ASSIGN @a @b
    // 将 b 赋值给 a
    // 指令执行后有执行状态

    SOFTEN_INVOKABLE virtual Return ASSIGN(BridgeAbstract* other)                 // T(ASSIGN, "=", 2)
    {
        if(isValid(other)) {
            if(isBaseType(this->type())) {
                this->data = dynamic_cast<BaseTypeBridge<T>* >(other)->data;
                return State::NormalCall;
            } else {
                std::cout << "Unknown type" << std::endl;
                return State::CallFail;
            }
        } else {
            return State::CallFail;
        }
    }

    SOFTEN_INVOKABLE virtual Return ASSIGN_BIT_OR(BridgeAbstract* other)       // T(ASSIGN_BIT_OR, "|=", 2)
    {
        if(isValid(other)) {
            if(isBaseType(this->type())) {
                this->data |= dynamic_cast<BaseTypeBridge<T>* >(other)->data;
                return State::NormalCall;
            } else {
                std::cout << "Unknown type" << std::endl;
                return State::CallFail;
            }
        } else {
            return State::CallFail;
        }
    }

    SOFTEN_INVOKABLE virtual Return ASSIGN_BIT_XOR(BridgeAbstract* other)         // T(ASSIGN_BIT_XOR, "^=", 2)
    {
        if(isValid(other)) {
            if(isBaseType(this->type())) {
                this->data ^= dynamic_cast<BaseTypeBridge<T>* >(other)->data;
                return State::NormalCall;
            } else {
                std::cout << "Unknown type" << std::endl;
                return State::CallFail;
            }
        } else {
            return State::CallFail;
        }
    }

    SOFTEN_INVOKABLE virtual Return ASSIGN_BIT_AND(BridgeAbstract* other)         // T(ASSIGN_BIT_AND, "&=", 2)
    {
        if(isValid(other)) {
            if(isBaseType(this->type())) {
                this->data &= dynamic_cast<BaseTypeBridge<T>* >(other)->data;
                return State::NormalCall;
            } else {
                std::cout << "Unknown type" << std::endl;
                return State::CallFail;
            }
        } else {
            return State::CallFail;
        }
    }

    SOFTEN_INVOKABLE virtual Return ASSIGN_SHL(BridgeAbstract* other)             // T(ASSIGN_SHL, "<<=", 2)
    {
        if(isValid(other)) {
            if(isBaseType(this->type())) {
                this->data <<= dynamic_cast<BaseTypeBridge<T>* >(other)->data;
                return State::NormalCall;
            } else {
                std::cout << "Unknown type" << std::endl;
                return State::CallFail;
            }
        } else {
            return State::CallFail;
        }
    }

    SOFTEN_INVOKABLE virtual Return ASSIGN_SAR(BridgeAbstract* other)            // T(ASSIGN_SAR, ">>=", 2)
    {
        if(isValid(other)) {
            if(isBaseType(this->type())) {
                this->data >>= dynamic_cast<BaseTypeBridge<T>* >(other)->data;
                return State::NormalCall;
            } else {
                std::cout << "Unknown type" << std::endl;
                return State::CallFail;
            }
        } else {
            return State::CallFail;
        }
    }

    SOFTEN_INVOKABLE virtual Return ASSIGN_ADD(BridgeAbstract* other)           // T(ASSIGN_ADD, "+=", 2)
    {
        if(isValid(other)) {
            if(isBaseType(this->type())) {
                this->data += dynamic_cast<BaseTypeBridge<T>* >(other)->data;
                return State::NormalCall;
            } else {
                std::cout << "Unknown type" << std::endl;
                return State::CallFail;
            }
        } else {
            return State::CallFail;
        }
    }

    SOFTEN_INVOKABLE virtual Return ASSIGN_SUB(BridgeAbstract* other)             // T(ASSIGN_SUB, "-=", 2)
    {
        if(isValid(other)) {
            if(isBaseType(this->type())) {
                this->data -= dynamic_cast<BaseTypeBridge<T>* >(other)->data;
                return State::NormalCall;
            } else {
                std::cout << "Unknown type" << std::endl;
                return State::CallFail;
            }
        } else {
            return State::CallFail;
        }
    }

    SOFTEN_INVOKABLE virtual Return ASSIGN_MUL(BridgeAbstract* other)         // T(ASSIGN_MUL, "*=", 2)
    {
        if(isValid(other)) {
            if(isBaseType(this->type())) {
                this->data *= dynamic_cast<BaseTypeBridge<T>* >(other)->data;
                return State::NormalCall;
            } else {
                std::cout << "Unknown type" << std::endl;
                return State::CallFail;
            }
        } else {
            return State::CallFail;
        }
    }

    SOFTEN_INVOKABLE virtual Return ASSIGN_DIV(BridgeAbstract* other)           // T(ASSIGN_DIV, "/=", 2)
    {
        if(isValid(other)) {
            if(isBaseType(this->type())) {
                this->data /= dynamic_cast<BaseTypeBridge<T>* >(other)->data;
                return State::NormalCall;
            } else {
                std::cout << "Unknown type" << std::endl;
                return State::CallFail;
            }
        } else {
            return State::CallFail;
        }
    }

    SOFTEN_INVOKABLE virtual Return ASSIGN_MOD(BridgeAbstract* other)            // T(ASSIGN_MOD, "%=", 2)
    {
        if(isValid(other)) {
            if(isBaseType(this->type())) {

                // TODO: NullPointException
                this->data %= dynamic_cast<BaseTypeBridge<T>* >(other)->data;
                return State::NormalCall;
            } else {
                std::cout << "Unknown type" << std::endl;
                return State::CallFail;
            }
        } else {
            return State::CallFail;
        }
    }

    //    SOFTEN_INVOKABLE virtual Return EQ(BridgeAbstract* other)                    // T(EQ, "==", 9)
    //    {
    //        if(this == other) {
    //            std::shared_ptr<BridgeAbstract> r_d(new BaseTypeBridge<bool>(new bool(true)));
    //            return Return(State::NormalCall, r_d);
    //        }

    //        if(isValid(other)) {
    //            bool r = *d == *(dynamic_cast<BaseTypeBridge<T>* >(other)->d);
    //            std::shared_ptr<BridgeAbstract> r_d(new BaseTypeBridge<bool>(new bool(r)));
    //            return Return(State::NormalCall, r_d);
    //        } else {
    //            std::shared_ptr<BridgeAbstract> r_d(new BaseTypeBridge<bool>(new bool(false)));
    //            return Return(State::NormalCall, r_d);
    //        }
    //    }

    //    SOFTEN_INVOKABLE virtual Return NE(BridgeAbstract* other)                   // T(NE, "!=", 9)
    //    {
    //        if(this == other) {
    //            std::shared_ptr<BridgeAbstract> r_d(new BaseTypeBridge<bool>(new bool(false)));
    //            return Return(State::NormalCall, r_d);
    //        }

    //        if(isValid(other)) {
    //            bool r = *d != *(dynamic_cast<BaseTypeBridge<T>* >(other)->d);
    //            std::shared_ptr<BridgeAbstract> r_d(new BaseTypeBridge<bool>(new bool(r)));
    //            return Return(State::NormalCall, r_d);
    //        } else {
    //            std::shared_ptr<BridgeAbstract> r_d(new BaseTypeBridge<bool>(new bool(true)));
    //            return Return(State::NormalCall, r_d);
    //        }
    //    }

    SOFTEN_INVOKABLE std::string toString() const {
        return std::to_string(this->get());
    }

private:
    T data;
};


}

#endif // BASETYPEBRIDGE_H
