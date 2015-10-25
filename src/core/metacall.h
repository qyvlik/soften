#ifndef METACALL
#define METACALL

#include <functional>
#include <map>
#include <list>

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


class Bridge;

template<typename T>
class MetaCall
{
public:
    typedef std::function<int (T*, std::list<Bridge*>, Bridge*)> Call;

    Call findMethod(const std::string& methodName) {
        auto c = methods.find(methodName);
        auto end = methods.end();
        if(c != end) {
            return (*c).second;
        } else {
            return [](T* , std::list<Bridge*>, Bridge*) -> int { return (int)State::MethodNotFound; };
        }
    }

    std::map<const std::string, Call> methods;
};


}

#endif // METACALL

