#ifndef ENGINE_H
#define ENGINE_H

namespace soften {

class Context;
class Scope;
class Engine
{
public:
    explicit Engine();
    ~Engine();
    Context* rootContext() const;

private:
    Context* m_rootContext;
};


}

#endif // ENGINE_H
