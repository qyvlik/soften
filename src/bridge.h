#ifndef ABSTRACTBRIDGE_H
#define ABSTRACTBRIDGE_H

#include <iostream>
#include <sstream>

inline std::string typeString()
{ return "Unknow"; }

template<typename T>
inline std::string typeString()
{ return "Unknow"; }

class AbstractBridge
{
public:
    AbstractBridge()
    {}

    virtual ~AbstractBridge()
    {}

    virtual std::string typeString() const
    {
        return ::typeString();
    }

    virtual bool assign(const AbstractBridge* other) = 0;

    virtual AbstractBridge* clone() const = 0;

    virtual std::string toString() const {
        std::stringstream sstream;
        sstream << this;
        std::string address;
        sstream >> address;
        return typeString() + "(" + address + ")";
    }
};

template<typename T>
class Bridge : public AbstractBridge
{
    static_assert(!std::is_class<T>::value,             "NOT SUPPORT CLASS");
    static_assert(!std::is_union<T>::value,             "NOT SUPPORT UNION");
    static_assert(!std::is_reference<T>::value ,        "NOT SUPPORT REFERENCE");
    static_assert(!std::is_const<T>::value ,            "NOT SUPPORT CONSTANT");
    static_assert(!std::is_pointer<T>::value,           "NOT SUPPORT POINTER");
    static_assert(!std::is_void<T>::value,              "NOT SUPPORT VOID");
    static_assert(!std::is_volatile<T>::value,          "NOT SUPPORT VOLATILE");

public:
    explicit Bridge(const T& value):
        data(value)
    { }

    ~Bridge()
    {
    }

    inline std::string typeString() const
    { return ::typeString<T>(); }

    inline void set(const T& value)
    { data = value; }

    inline T& get()
    { return data; }

    inline const T& get() const
    { return data; }

    bool assign(const AbstractBridge* other) {
        Bridge<T> * other_ =
                dynamic_cast<Bridge<T> *>
                (const_cast<AbstractBridge*>(other));
        if(other_) {
            data = other_->data;
            return true;
        } else {
            return false;
        }
    }

    AbstractBridge* clone() const
    { return new Bridge<T>(data); }

    std::string toString()const {
        std::stringstream sstream;
        sstream << data;
        std::string data_to_string;
        sstream >> data_to_string;
        return data_to_string;
    }

private:
    T data;
};

#define STATIC_REGISTER_TYPE(_TYPE_, _TYPE_NAME) \
     template<> inline std::string typeString< _TYPE_ >() { return _TYPE_NAME ; }

//! complex type
#define COMPLEX_TYPE_BRIDGE(_CLASS_) \
template<>                                                                       \
class Bridge<_CLASS_> : public AbstractBridge                                    \
{                                                                                \
    static_assert( std::is_class<_CLASS_>::value, "MUST A CLASS");               \
    static_assert(!std::is_union<_CLASS_>::value, "NOT SUPPORT UNION");          \
    static_assert(!std::is_reference<_CLASS_>::value ,"NOT SUPPORT REFERENCE");  \
    static_assert(!std::is_const<_CLASS_>::value ,"NOT SUPPORT CONSTANT");       \
    static_assert(!std::is_pointer<_CLASS_>::value, "NOT SUPPORT POINTER");      \
    static_assert(!std::is_void<_CLASS_>::value, "NOT SUPPORT VOID");            \
    static_assert(!std::is_volatile<_CLASS_>::value, "NOT SUPPORT VOLATILE");    \
public:                                                                          \
    explicit Bridge(const _CLASS_& data):                                        \
        data(data)                                                               \
    { }                                                                          \
    inline std::string typeString() const                                        \
    { return ::typeString<_CLASS_>(); }                                          \
    inline void set(const _CLASS_& value)                                        \
    { data = value; }                                                            \
    inline _CLASS_& get()                                                        \
    { return data; }                                                             \
    inline const _CLASS_& get() const                                            \
    { return data; }                                                             \
    bool assign(const AbstractBridge* other) {                                   \
        Bridge<_CLASS_> * other_ =                                               \
                dynamic_cast<Bridge<_CLASS_> *>                                  \
                (const_cast<AbstractBridge*>(other));                            \
        return other_                                                            \
                ? (data = other_->data, true)                                    \
                : false;                                                         \
    }                                                                            \
    AbstractBridge* clone() const                                                \
    { return new Bridge<_CLASS_>(data); }                                        \
private:                                                                         \
    _CLASS_ data;                                                                \
};

STATIC_REGISTER_TYPE(bool, "bool");

STATIC_REGISTER_TYPE(char, "char");

STATIC_REGISTER_TYPE(short, "short");

STATIC_REGISTER_TYPE(int, "int");

STATIC_REGISTER_TYPE(long, "long");

STATIC_REGISTER_TYPE(long long, "long long");

STATIC_REGISTER_TYPE(float, "float");

STATIC_REGISTER_TYPE(double, "double");

STATIC_REGISTER_TYPE(std::string, "String");

template<>
class Bridge<std::string> : public AbstractBridge
{
public:
    explicit Bridge(const char* data):
        data(data)
    {}

    explicit Bridge(const std::string& data):
        data(data)
    { }

    inline std::string typeString()
    { return ::typeString<std::string>(); }

    inline void set(const std::string& value)
    { data = value; }

    inline std::string& get()
    { return data; }

    inline const std::string& get() const
    { return data; }

    bool assign(const AbstractBridge* other) {
        Bridge<std::string> * other_ =
                dynamic_cast<Bridge<std::string> *>
                (const_cast<AbstractBridge*>(other));

        return other_
                ? (data = other_->data, true)
                : false;
    }

    AbstractBridge* clone() const
    { return new Bridge<std::string>(data); }

    std::string toString()const
    { return data; }

private:
    std::string data;
};


#define STATIC_REGISTER_COMPLEX_TYPE(_CLASS_, _CLASS_NAME_) \
    STATIC_REGISTER_TYPE(_CLASS_, _CLASS_NAME_) \
    COMPLEX_TYPE_BRIDGE(_CLASS_)

#endif // ABSTRACTBRIDGE_H
