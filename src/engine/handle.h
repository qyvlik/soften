#ifndef HANDLE_H
#define HANDLE_H

#include <memory>
#include "scope.h"

namespace soften {




template<typename T>
class Handle
{
public:

    enum ObjectOwnership {
        CppOwnership,
        EngineOwnership
    }

    explicit Handle();

private:
    std::pair<Scope, std::shared_ptr<T> > d_pair;
};


}

#endif // HANDLE_H
