#ifndef OBJECT_H
#define OBJECT_H

#include <functional>
#include <map>
#include "metaobject.h"

namespace soften {

#define SOFTEN_INVOKABLE

class Object
{
public:
    friend class MetaObject<Object>;
    typedef MetaObject<Object> Meta;
    typedef Meta::call call;
    static Meta metaObject;
    std::map<const std::string, call> objectMethodMap() const {
        return metaObject.objectMethods;
    }
    call findMethod(const std::string& method) {
        return metaObject.findMethod(method);
    }
    virtual void callMethod(const std::string& method, Object* thiz, void* args, void* r) {
        thiz->findMethod(method)(thiz, args, r);
    }

public:
    explicit Object();

public:
    SOFTEN_INVOKABLE virtual std::string toString() const;

};


#define SOFTEN_OBJECT(_CLASS_NAME)                                              \
    protected:                                                                  \
    friend class soften::MetaObject<_CLASS_NAME>;                               \
    typedef soften::MetaObject<_CLASS_NAME> Meta;                               \
    typedef Meta::call call;                                                    \
    static Meta metaObject;                                                     \
    public:                                                                     \
    std::map<const std::string, call> objectMethodMap() const {                 \
        return metaObject.objectMethods;                                        \
    }                                                                           \
    call findMethod(const std::string& method) {                                \
        return metaObject.findMethod(method);                                   \
    }                                                                           \
    virtual void callMethod( const std::string& method,                         \
                             Object* thiz, void* args, void* r) {               \
        _CLASS_NAME* thizz = reinterpret_cast<_CLASS_NAME*>(thiz);              \
        thizz->findMethod(method)(thizz, args, r);                              \
    }                                                                           \


}

#endif // OBJECT_H
