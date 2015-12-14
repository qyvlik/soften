#ifndef TEST_VECTOR2D
#define TEST_VECTOR2D

#include "vector2d.h"
#include "../src/variant.h"
#include "../src/sobject.h"

STATIC_REGISTER_TYPE(vector2d, "vector2d");

template<>
class Bridge<vector2d> : public AbstractBridge
{
public:
    explicit Bridge(const vector2d& data):
        data(data)
    { }

    inline std::string typeString() const
    { return ::typeString<vector2d>(); }

    inline void set(const vector2d& value)
    { data = value; }

    inline vector2d& get()
    { return data; }

    inline const vector2d& get() const
    { return data; }

    bool assign(const AbstractBridge* other) {
        Bridge<vector2d> * other_ =
                dynamic_cast<Bridge<vector2d> *>
                (const_cast<AbstractBridge*>(other));
        return other_
                ? (data = other_->data, true)
                : false;
    }

    AbstractBridge* clone() const
    { return new Bridge<vector2d>(data); }

    std::string toString()const {
        return this->typeString() + "("
                + std::to_string(this->data.x())
                + ","
                + std::to_string(this->data.y()) + ")";
    }

private:
    vector2d data;
};

class TestVector2d
{
public:
    static void Test() {
        SObject object;
        object.setProperty("vector2d", vector2d(10, 20));
        std::cout << object.property("vector2d") << std::endl;
    }
};


#endif // TEST_VECTOR2D

