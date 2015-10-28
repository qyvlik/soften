#include "bridge.h"

using namespace std;

namespace soften {


Bridge::Meta Bridge::metaCall =
{
    {
        pair<const string, Bridge::Meta::Call>(
        "log",
        [](Bridge* thiz, std::vector<Bridge*> args, Bridge*)->int{

            // void(Bridge*)
            if(args.empty()) return (int)State::ArgumentsFail;

            thiz->log(args[0]);
            return (int)soften::State::NormalCall;
        })
    }
};


Bridge::Bridge()
{
}


Bridge::~Bridge()
{
}


BridgeAbstract::Type Bridge::type() const
{
    return BridgeAbstract::Unknown;
}


BridgeAbstract::Return Bridge::ASSIGN(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::ASSIGN_BIT_OR(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::ASSIGN_BIT_XOR(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::ASSIGN_BIT_AND(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::ASSIGN_SHL(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::ASSIGN_SAR(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::ASSIGN_ADD(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::ASSIGN_SUB(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::ASSIGN_MUL(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::ASSIGN_DIV(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::ASSIGN_MOD(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::COMMA(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::OR(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::AND(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::BIT_OR(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::BIT_XOR(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::BIT_AND(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::SHL(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::SAR(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::ADD(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::SUB(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::MUL(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::DIV(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::MOD(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::EQ(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::NE(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::LT(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::GT(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::LTE(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::GTE(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::IN(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::NOT(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::DELETE(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::TYPEOF(BridgeAbstract *)
{
    return soften::State::CastFail;
}


BridgeAbstract::Return Bridge::VOID(BridgeAbstract *)
{
    return soften::State::CastFail;
}


string Bridge::toString() const
{
    return "Bridge: " + this->Object::toString();
}

void Bridge::log(Bridge * bridge)
{
    cout << "--------------------" << endl;
    cout << "here is the log method" << endl;
    cout << bridge->toString() << endl;
    cout << "--------------------" << endl;
}



}


