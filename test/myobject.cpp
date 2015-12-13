#include "myobject.h"

using namespace std;

const ObjectMetaCall<MyObject> MyObject::StaticMetaCall = {
    {

    }
};

const ObjectMetaCall<MyMyObject> MyMyObject::StaticMetaCall = {
    {
        std::pair<const std::string, MyMyObject::CallableMethod >
        ( "toString",
        [](MyMyObject* thiz, std::vector<Variant>&, Variant& result)->int{
            result = thiz->toString();
            return 0;
        })
    }
};

MyObject::MyObject()
{

}

std::string MyObject::toString() const
{
    std::stringstream sstream;
    sstream << this;
    std::string address;
    sstream >> address;
    return "MyObject(" + address + ")";
}

