#ifndef SOFTEN_H
#define SOFTEN_H

#include <iostream>
#include <sstream>

#define SOFTEN_HACK friend

#define SOFTEN_INVOKABLE

// #define SOFTEN_EXTENDS : virtual public

namespace soften {


template<typename T>
std::string getObjectAddress(const T* thiz) {
    std::stringstream s;
    s << thiz;
    std::string address;
    s >> address;
    return address;
}


}

#endif // SOFTEN_H

