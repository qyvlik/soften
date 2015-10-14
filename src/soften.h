#ifndef SOFTEN_H
#define SOFTEN_H

#include <iostream>
#include <sstream>

#define SOFTEN_HACK friend

#define SOFTEN_INVOKABLE

namespace soften {


template<typename T>
std::string getObjectAddress(const T* thiz) {
    std::stringstream s;
    s << thiz;
    std::string address;
    s >> address;
    return address;
}

struct identity {
    identity(const std::string& previous):
        id(previous+ "." +getObjectAddress<identity>(this))
    {}

    operator std::string () { return id; }

    std::string id;
};

// compiled-time
//template<typename _Base, typename _Derived>
//bool isDerived(_Base* b, _Derived* )
//{
//    return dynamic_cast<_Derived>(b) != nullptr ;
//}


}

#endif // SOFTEN_H

