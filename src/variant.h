#ifndef VARIANT_H
#define VARIANT_H

#include "bridge.h"
#include <assert.h>
#include <map>
#include <list>
#include <vector>

class Variant;

typedef std::map<std::string, Variant> VariantMap;

typedef std::list<Variant> VariantList;

typedef std::vector<Variant> VariantVector;

class Variant
{
public:
    explicit Variant():
        d_ptr(
            new Bridge<int>(0)
            // nullptr
            )
    {

#if QBS_DEBUG
        std::cout << "explicit Variant() this:" << this << std::endl;
#endif
    }

    // 去掉 explicit 方便
    // explicit
    Variant(const char* data)
        :d_ptr(new Bridge<std::string>(data))
    {}

    // explicit 就不能用于返回值了
    Variant(const Variant& other)
    {
#if QBS_DEBUG
        std::cout << "explicit Variant(const Variant& other) "
                  << "this:"
                  << this
                  << " other:" << &other
                  << std::endl;
#endif
        if(other.d_ptr) {
            d_ptr = other.d_ptr->clone();
        }
    }

    explicit Variant(Variant&& other):
        d_ptr(other.d_ptr)
    {
#if QBS_DEBUG
        std::cout << "explicit Variant(Variant&& other)"
                  << "this:" << this
                  << " other: " << &other
                  << std::endl;
#endif
        other.d_ptr = nullptr;
    }

    template<typename T>
    // 去掉 explicit 方便一点
    // explicit
    Variant(const T& data):
        d_ptr(new Bridge<T>(data))
    {
#if QBS_DEBUG
        std::cout << "explicit Variant(const T& data)" << std::endl;
#endif
    }

    //! 不知道问什么不能为虚析构函数
    //! 会奔溃
    // virtual
    ~Variant()
    {
#ifdef QBS_DEBUG
        std::cout << " ~Variant() this: " << this << std::endl;
#endif
        delete d_ptr;
    }

    template<typename T>
    Variant& operator = (const T& value) {
#if QBS_DEBUG
        std::cout << "Variant& operator = (const T& value)"
                  << "this: " << this
                  << std::endl;
#endif
        if(this->canConvert<T>()) {
            dynamic_cast< Bridge<T> *> (d_ptr)->set(value);
        } else {
            delete d_ptr ;
            d_ptr = new Bridge<T>(value);
        }
        return *this;
    }

    Variant& operator = (const Variant& other) {
#if QBS_DEBUG
        std::cout << "Variant& operator = (const Variant& other)" << std::endl;
#endif
        if(this->d_ptr && !this->d_ptr->assign(other.d_ptr)) {
            delete this->d_ptr;
            this->d_ptr = other.d_ptr->clone();
        }
        return *this;
    }

    template<typename T>
    bool canConvert() const
    { return dynamic_cast< Bridge<T> *>(d_ptr) ; }

    bool canConvert(const std::string& typeName) const
    { return d_ptr ? d_ptr->typeString() == typeName : false; }

    template<typename T>
    const T& value() const {
#if QBS_DEBUG
        std::cout << "user this method must check object can convert"
                  << std::endl;
#endif
        Bridge<T>* d_convert_ptr = dynamic_cast< Bridge<T> *> (d_ptr);
        assert(d_convert_ptr);
        return d_convert_ptr->get();
    }

    template<typename T>
    T& value() {
#if QBS_DEBUG
        std::cout << "user this method must check object can convert"
                  << std::endl;
#endif
        Bridge<T>* d_convert_ptr = dynamic_cast< Bridge<T> *> (d_ptr);
        assert(d_convert_ptr);
        return d_convert_ptr->get();
    }

    template<typename T>
    bool get(T& g) const {
        // T not a class or struct or union
        // or T register.

        return this->canConvert<T>()
                ? (g = dynamic_cast< Bridge<T> *> (d_ptr)->get(), true)
                : false;
    }

    std::string typeString() const
    { return d_ptr ? d_ptr->typeString() : ::typeString(); }

    friend std::ostream& operator << (std::ostream& outs, const Variant& var)
    { return outs << (var.d_ptr ? var.d_ptr->toString() : ""); }

private:
    AbstractBridge* d_ptr;
};


STATIC_REGISTER_TYPE(VariantMap, "VariantMap");

template<>
class Bridge<VariantMap> : public AbstractBridge
{
public:
    explicit Bridge(const VariantMap& data):
        data(data)
    { }

    inline std::string typeString() const
    { return ::typeString<VariantMap>(); }

    inline void set(const VariantMap& value)
    { data = value; }

    inline VariantMap& get()
    { return data; }

    inline const VariantMap& get() const
    { return data; }

    bool assign(const AbstractBridge* other) {
        Bridge<VariantMap> * other_ =
                dynamic_cast<Bridge<VariantMap> *>
                (const_cast<AbstractBridge*>(other));
        return other_
                ? (data = other_->data, true)
                : false;
    }

    AbstractBridge* clone() const
    { return new Bridge<VariantMap>(data); }

private:
    VariantMap data;
};


STATIC_REGISTER_TYPE(VariantList, "VariantList");

template<>
class Bridge<VariantList> : public AbstractBridge
{
public:
    explicit Bridge(const VariantList& data):
        data(data)
    { }

    inline std::string typeString() const
    { return ::typeString<VariantList>(); }

    inline void set(const VariantList& value)
    { data = value; }

    inline VariantList& get()
    { return data; }

    inline const VariantList& get() const
    { return data; }

    bool assign(const AbstractBridge* other) {
        Bridge<VariantList> * other_ =
                dynamic_cast<Bridge<VariantList> *>
                (const_cast<AbstractBridge*>(other));
        return other_
                ? (data = other_->data, true)
                : false;
    }

    AbstractBridge* clone() const
    { return new Bridge<VariantList>(data); }

private:
    VariantList data;
};

STATIC_REGISTER_TYPE(VariantVector, "VariantVector");

template<>
class Bridge<VariantVector> : public AbstractBridge
{
public:
    explicit Bridge(const VariantVector& data):
        data(data)
    { }

    inline std::string typeString() const
    { return ::typeString<VariantVector>(); }

    inline void set(const VariantVector& value)
    { data = value; }

    inline VariantVector& get()
    { return data; }

    inline const VariantVector& get() const
    { return data; }

    bool assign(const AbstractBridge* other) {
        Bridge<VariantVector> * other_ =
                dynamic_cast<Bridge<VariantVector> *>
                (const_cast<AbstractBridge*>(other));
        return other_
                ? (data = other_->data, true)
                : false;
    }

    AbstractBridge* clone() const
    { return new Bridge<VariantVector>(data); }

private:
    VariantVector data;
};


#endif // VARIANT_H
