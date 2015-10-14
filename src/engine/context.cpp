#include "context.h"

#include "engine.h"
#include "scope.h"

using namespace std;

namespace soften {


class ContextPrivate
{
public:
    ContextPrivate(Engine* engine)
        : m_engine(engine)
    { }
    Engine *engine() const
    {
        return m_engine;
    }

    std::map<int, Scope> scopeMap() const
    {
        return m_scopeMap;
    }
    void setScopeMap(const std::map<int, Scope> &scopeMap)
    {
        m_scopeMap = scopeMap;
    }

private:
    Engine* m_engine;
    std::map<int, Scope> m_scopeMap;

};


Context::Context(Engine *engine):
    d_ptr(new ContextPrivate(engine))
{
}

Context::~Context()
{
    delete d_ptr;
}


Engine *Context::engine() const
{
    return d_ptr->engine();
}


std::map<int, Scope> Context::scopeMap() const
{
    return d_ptr->scopeMap();
}


}
