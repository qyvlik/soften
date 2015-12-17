#include "myobject.h"

using namespace std;

const ObjectMetaCall<MyObject> MyObject::StaticMetaCall = {
    {

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

const ObjectMetaCall<MyMyObject> MyMyObject::StaticMetaCall = {
    {
        std::pair<std::string, MyMyObject::CallableMethod>
        ( "toString",
        [](MyMyObject* thiz, std::vector<Variant>&, Variant& result)->int{
            result = thiz->toString();
            return 0;
        })
    }
};

string MyMyObject::toString() const
{
    std::stringstream sstream;
    sstream << this;
    std::string address;
    sstream >> address;
    return "MyMyObject(" + address + ")";
}
