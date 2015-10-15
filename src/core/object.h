#ifndef OBJECT_H
#define OBJECT_H

#include <functional>
#include <map>
#include "../soften.h"
#include "metaobject.h"

namespace soften {


class Object
{
public:
    SOFTEN_HACK class MetaObject<Object>;
    typedef MetaObject<Object> Meta;
    typedef Meta::call call;
    static Meta metaObject;
    std::map<const std::string, call> objectMethodMap() const {
        return metaObject.objectMethods;
    }
    call findMethod(const std::string& method) {
        return metaObject.findMethod(method);
    }
    virtual State callMethod(const std::string &method, void *args, void *r) {
        return this->findMethod(method)(this, args, r);
    }
    virtual State callMethod(const std::string& method, Object* thiz, void* args, void* r) {
        return thiz->findMethod(method)(thiz, args, r);
    }

public:
    explicit Object();
    identity id;
public:
    SOFTEN_INVOKABLE virtual std::string toString() const;

};


#define SOFTEN_OBJECT(_CLASS_NAME)                                              \
    public:                                                                     \
    typedef soften::MetaObject<_CLASS_NAME> Meta;                               \
    typedef Meta::call call;                                                    \
    protected:                                                                  \
    SOFTEN_HACK class soften::MetaObject<_CLASS_NAME>;                          \
    static Meta metaObject;                                                     \
    public:                                                                     \
    std::map<const std::string, call> objectMethodMap() const {                 \
        return metaObject.objectMethods;                                        \
    }                                                                           \
    call findMethod(const std::string& method) {                                \
        return metaObject.findMethod(method);                                   \
    }                                                                           \
    virtual soften::State callMethod(const std::string &method, void *args, void *r) {  \
        return this->findMethod(method)(this, args, r);                         \
    }                                                                           \
    virtual soften::State callMethod( const std::string& method,                        \
                             Object* thiz, void* args, void* r) {               \
        _CLASS_NAME* thizz = dynamic_cast<_CLASS_NAME*>(thiz);                  \
        if(thizz) {                                                             \
            return thizz->findMethod(method)(thizz, args, r);                   \
        } else {                                                                \
            return soften::State::MethodNotFound;                                       \
        }                                                                       \
    }


}

#endif // OBJECT_H
