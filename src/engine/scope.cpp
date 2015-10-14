#include "scope.h"
#include "context.h"

using namespace std;

namespace soften {

class ScopePrivate
{
public:
    typedef Scope::Handle Handle;
    static Handle createHandle(Context* context) {
        return Handle(new ScopePrivate(context));
    }

    friend bool operator==(const Handle& left, const Handle& right) {
        return left->m_context == right->m_context;
    }

    Context* context() {
        return m_context;
    }

protected:
    ScopePrivate(Context* context) :
        m_context(context)
    {
    }

private:
    Context* m_context;
    int m_scopeId;
};

Scope Scope::createScope(Context *context)
{
    return Scope(context);
}

Scope::Scope(Context *context):
    d_ptr(ScopePrivate::createHandle(context))
{

}

Scope::Scope(Scope &&other):
    d_ptr(other.d_ptr)
{

}

Scope::Scope(const Scope &other):
    d_ptr(other.d_ptr)
{

}

Scope &Scope::operator=(const Scope &other)
{
    this->d_ptr = other.d_ptr;
    return *this;
}

bool Scope::operator==(const Scope &other)
{
    return this->d_ptr == other.d_ptr;
}

bool Scope::isEqual(const Scope &left, const Scope &right)
{
    return left.d_ptr == right.d_ptr;
}

const Context *Scope::context() const
{
    return this->d_ptr->context();
}




}
