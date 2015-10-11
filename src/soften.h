#ifndef SOFTEN_H
#define SOFTEN_H

#include <iostream>
#include <strstream>

namespace soften {


template<typename T>
std::string getObjectAddress(const T* thiz) {
    std::strstream s;
    s << thiz;
    std::string address;
    s >> address;
    return address;
}


}

#endif // SOFTEN_H

