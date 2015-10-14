#include "engine.h"
#include "context.h"

namespace soften {


Engine::Engine():
    m_rootContext(new Context(this))
{

}

Engine::~Engine()
{
    delete m_rootContext;
}

Context *Engine::rootContext() const
{
    return m_rootContext;
}


}
