#ifndef SCOPE_H
#define SCOPE_H

#include <memory>
#include "../soften.h"

namespace soften {


class Context;
class ScopePrivate;

class Scope
{

public:

    static Scope createScope(Context* context);

    Scope(Scope&& other);
    Scope(const Scope& other);
    Scope& operator=(const Scope& other);

    bool operator== (const Scope& other);
    static bool isEqual(const Scope& left, const Scope& right);

    const Context* context() const;

protected:
    explicit Scope(Context* context);

private:
    SOFTEN_HACK class ScopePrivate;
    typedef std::shared_ptr<ScopePrivate> Handle;
    Handle d_ptr;
};


}

#endif // SCOPE_H
