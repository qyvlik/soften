#ifndef METACALL
#define METACALL

#include <functional>
#include <map>

namespace soften {

enum class State {
    NormalCall,
    ArgumentsFail,
    ReturnFail,
    MethodNotFound,
    CppException,
    CastFail,
    TypeFail,
    Unkonwn
};


template<typename T>
class MetaCall
{
public:
    typedef std::function<int (T*, void*, void*)> Call;

    Call findMethod(const std::string& methodName) {
        auto c = methods.find(methodName);
        auto end = methods.end();
        if(c != end) {
            return (*c).second;
        } else {
            return [](T* , void*, void*) -> int { return (int)State::MethodNotFound; };
        }
    }

    std::map<const std::string, Call> methods;
};


}

#endif // METACALL

