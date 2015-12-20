#ifndef BINDING_H
#define BINDING_H

#include "variant.h"
#include "sobject.h"

class Binding : public SObject
{
    SOFTEN_OBJECT(Binding, SObject);

public:
    typedef std::vector<std::pair<SObject*, std::string> > SourceObjects;
    typedef std::function<void(SourceObjects&, Variant& result)> BindingExpression;

    Binding(SObject* target,
            const std::string& property,
            const BindingExpression& bindingExpression,
            SObject* parent = nullptr);

    ~Binding();

    void addSourceObject(SObject* source, const std::string& propertyName);

protected:
    Binding() = delete;
    Binding(const Binding&) = delete;

private:
    SObject* m_target;
    std::string m_property;
    BindingExpression m_expression;
    SourceObjects m_sources;
};


/**
  SObject {
      id: root
      SObject {
          id: object
      }

      SObject {
          id: item
      }

      Binding {
          target: object
          property: "height"
          value: 2 * item.heihgt + item.width
      }
  }
*/

#endif // BINDING_H
