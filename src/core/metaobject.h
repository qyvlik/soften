#ifndef METAOBJECT_H
#define METAOBJECT_H

#include <map>
#include <functional>

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

class Object;

template<typename T>
class MetaObject
{
public:
    typedef std::function<State(T*, void*, void*)> call;
    inline call findMethod(const std::string& method) {
        auto e = objectMethods.end();
        auto c = objectMethods.find(method);
        if(e != c) {
            return c->second;
        }
        return  [](T*, void*, void*)->State{ return State::MethodNotFound; };
    }

    template<typename Base>
    State callMethod(T* thiz, const std::string& methodName, void* args, void* r) {
        // MetaObject<T>
        auto c = T::metaObject.findMethod(methodName);
        auto end = T::metaObject.objectMethods.end();
        if(c != end) {
            return c(thiz, args, r);
        } else {
            return Base::metaObject.findMethod(thiz, methodName, args, r );
        }
    }

//    template<>
//    State callMethod<soften::Object>(T* thiz, const std::string& methodName, void* args, void* r) {
//        // MetaObject<T>
//        return T::metaObject.findMethod(methodName)(thiz, args, r);
//    }

    std::map<const std::string, call> objectMethods;

};




#define _TUPLE_GET_ONE_ARGUMENT(_NUMBER_)  \
    /*! arg0 or arg1 .. arg9 ..  */        \
    decltype(std::get<_NUMBER_>(*arguments)) arg##_NUMBER_ = std::get<_NUMBER_>(*arguments);

#define _TUPLE_GET_ARGUMENTS_1  _TUPLE_GET_ONE_ARGUMENT(0)
#define _TUPLE_GET_ARGUMENTS_2  _TUPLE_GET_ONE_ARGUMENT(1) _TUPLE_GET_ARGUMENTS_1
#define _TUPLE_GET_ARGUMENTS_3  _TUPLE_GET_ONE_ARGUMENT(2) _TUPLE_GET_ARGUMENTS_2
#define _TUPLE_GET_ARGUMENTS_4  _TUPLE_GET_ONE_ARGUMENT(3) _TUPLE_GET_ARGUMENTS_3
#define _TUPLE_GET_ARGUMENTS_5  _TUPLE_GET_ONE_ARGUMENT(4) _TUPLE_GET_ARGUMENTS_4
#define _TUPLE_GET_ARGUMENTS_6  _TUPLE_GET_ONE_ARGUMENT(5) _TUPLE_GET_ARGUMENTS_5
#define _TUPLE_GET_ARGUMENTS_7  _TUPLE_GET_ONE_ARGUMENT(6) _TUPLE_GET_ARGUMENTS_6
#define _TUPLE_GET_ARGUMENTS_8  _TUPLE_GET_ONE_ARGUMENT(7) _TUPLE_GET_ARGUMENTS_7
#define _TUPLE_GET_ARGUMENTS_9  _TUPLE_GET_ONE_ARGUMENT(8) _TUPLE_GET_ARGUMENTS_8
#define _TUPLE_GET_ARGUMENTS_10 _TUPLE_GET_ONE_ARGUMENT(9) _TUPLE_GET_ARGUMENTS_9

#define _TUPLE_GET_ARGUMENTS(_ARG_COUNT_)                    \
    /*! arg0 to arg##_ARG_COUNT_ */                          \
    _TUPLE_GET_ARGUMENTS_##_ARG_COUNT_



}

#endif // METAOBJECT_H
