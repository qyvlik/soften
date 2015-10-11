#ifndef METAOBJECT_H
#define METAOBJECT_H

#include <map>
#include <functional>

namespace soften {

template<typename T>
class MetaObject
{
public:
    typedef std::function<void(T*, void*, void*)> call;
    inline call findMethod(const std::string& method) {
        auto e = objectMethods.end();
        auto c = objectMethods.find(method);
        if(e != c) {
            return c->second;
        }
        return  [](T*, void*, void*){ };
    }

    std::map<const std::string, call> objectMethods;

};

enum class CallState {
    NormalCall,
    ArgumentsFail,
    ReturnFail,
    Method404,
    CppException,
    Unkonwn
};

}

#endif // METAOBJECT_H
