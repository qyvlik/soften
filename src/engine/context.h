#ifndef CONTEXT_H
#define CONTEXT_H

#include <map>

namespace soften {

class Scope;
class Engine;
class ContextPrivate;
class Context
{
public:
    explicit Context(Engine* engine);
    ~Context();
    Engine* engine()const;

    std::map<int, Scope> scopeMap()const;


private:
    ContextPrivate* d_ptr;
};


}

#endif // CONTEXT_H
