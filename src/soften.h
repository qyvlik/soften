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



template<typename T>
T toNumber(const std::string& number_string ){
    T number;
    std::stringstream stream;
    stream << number_string;
    stream >> number;
    return number;
}

}

#endif // SOFTEN_H

