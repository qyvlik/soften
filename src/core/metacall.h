#ifndef METACALL
#define METACALL

#include <functional>
#include <map>
#include <list>
#include <vector>

namespace soften {

enum class State {
    NormalCall = 0,
    MethodNotFound,
    LabelFail,
    ArgumentsFail,
    ReturnFail,
    CppException,
    NameError,
    CastFail,
    TypeFail,
    CallFail,
    MutilDefine,
    NotDefine,
    FileError,
    CacheEmpty,
    Unkonwn
};


class Bridge;

template<typename T>
class MetaCall
{
public:
    typedef std::function<int (T*, std::vector<Bridge*>, Bridge*)> Call;

    Call findMethod(const std::string& methodName) {
        auto c = methods.find(methodName);
        auto end = methods.end();
        if(c != end) {
            return (*c).second;
        } else {
            return [](T* , std::vector<Bridge*>, Bridge*) -> int
            { return (int)State::MethodNotFound; };
        }
    }

    std::map<const std::string, Call> methods;
};


}

#endif // METACALL

