#ifndef SOFTEN_H
#define SOFTEN_H

#include <iostream>
#include <sstream>

namespace soften {

#define SOFTEN_HACK friend

#define SOFTEN_INVOKABLE

template<typename T>
std::string getObjectAddress(const T* thiz) {
    std::stringstream s;
    s << thiz;
    std::string address;
    s >> address;
    return address;
}

// run-time

//template<typename _Base, typename _Derived>
//bool isDerived(_Base* b, _Derived* )
//{
//    return dynamic_cast<_Derived>(b) != nullptr ;
//}

#endif // SOFTEN_H

