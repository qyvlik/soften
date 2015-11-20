#ifndef CALLHELPER
#define CALLHELPER

#include "bridge.h"
#include "functionmeta.h"
#include "metacall.h"

template<typename T>
struct RemoveRefenrence;


template<typename T>
struct RemoveRefenrence{
    typedef T type;
};


template<typename T>
struct RemoveRefenrence<T&>{
    typedef T type;
};


//---------------------------------------------------------------------------------------

//! [0] 定义展开元式

#define GET_ARGUMENT_TYPE_INDEX(_INDEX_, _FUNCTION_TYPE_) \
    typedef std::tuple_element< _INDEX_, \
                                FunctionMeta<_FUNCTION_TYPE_>::ArgsTypeTuple >::type \
    arg_type_##_INDEX_;

//! [0] 定义展开元式

//! [1] 递归展开

#define DEFINE_ARGUMENTS_TYPE_COUNT_0(_FUNCTION_TYPE_) \
    ;

#define DEFINE_ARGUMENTS_TYPE_COUNT_1(_FUNCTION_TYPE_) \
    DEFINE_ARGUMENTS_TYPE_COUNT_0(_FUNCTION_TYPE_) \
    GET_ARGUMENT_TYPE_INDEX(0, _FUNCTION_TYPE_)

#define DEFINE_ARGUMENTS_TYPE_COUNT_2(_FUNCTION_TYPE_) \
    DEFINE_ARGUMENTS_TYPE_COUNT_1(_FUNCTION_TYPE_) \
    GET_ARGUMENT_TYPE_INDEX(1, _FUNCTION_TYPE_)

#define DEFINE_ARGUMENTS_TYPE_COUNT_3(_FUNCTION_TYPE_) \
    DEFINE_ARGUMENTS_TYPE_COUNT_2(_FUNCTION_TYPE_) \
    GET_ARGUMENT_TYPE_INDEX(2, _FUNCTION_TYPE_)

#define DEFINE_ARGUMENTS_TYPE_COUNT_4(_FUNCTION_TYPE_) \
    DEFINE_ARGUMENTS_TYPE_COUNT_3(_FUNCTION_TYPE_) \
    GET_ARGUMENT_TYPE_INDEX(3, _FUNCTION_TYPE_)

#define DEFINE_ARGUMENTS_TYPE_COUNT_5(_FUNCTION_TYPE_) \
    DEFINE_ARGUMENTS_TYPE_COUNT_4(_FUNCTION_TYPE_) \
    GET_ARGUMENT_TYPE_INDEX(4, _FUNCTION_TYPE_)

#define DEFINE_ARGUMENTS_TYPE_COUNT_6(_FUNCTION_TYPE_) \
    DEFINE_ARGUMENTS_TYPE_COUNT_5(_FUNCTION_TYPE_) \
    GET_ARGUMENT_TYPE_INDEX(5, _FUNCTION_TYPE_)

#define DEFINE_ARGUMENTS_TYPE_COUNT_7(_FUNCTION_TYPE_) \
    DEFINE_ARGUMENTS_TYPE_COUNT_6(_FUNCTION_TYPE_) \
    GET_ARGUMENT_TYPE_INDEX(6, _FUNCTION_TYPE_)

#define DEFINE_ARGUMENTS_TYPE_COUNT_8(_FUNCTION_TYPE_) \
    DEFINE_ARGUMENTS_TYPE_COUNT_7(_FUNCTION_TYPE_) \
    GET_ARGUMENT_TYPE_INDEX(7, _FUNCTION_TYPE_)

#define DEFINE_ARGUMENTS_TYPE_COUNT_9(_FUNCTION_TYPE_) \
    DEFINE_ARGUMENTS_TYPE_COUNT_8(_FUNCTION_TYPE_) \
    GET_ARGUMENT_TYPE_INDEX(8, _FUNCTION_TYPE_)

#define DEFINE_ARGUMENTS_TYPE_COUNT_10(_FUNCTION_TYPE_) \
    DEFINE_ARGUMENTS_TYPE_COUNT_9(_FUNCTION_TYPE_) \
    GET_ARGUMENT_TYPE_INDEX(9, _FUNCTION_TYPE_)

//! [1] 递归展开

//! [2] 自动展开

#define DEFINE_ARGUMENTS_TYPE(_COUNT_, _FUNCTION_TYPE_) \
    DEFINE_ARGUMENTS_TYPE_COUNT_##_COUNT_(_FUNCTION_TYPE_)

//! [2] 自动展开

//---------------------------------------------------------------------------------------

//! [3] 定义展开元式

#define CAST_ARGUMETN_IN_META_CALL(_INDEX_) \
    auto* args_##_INDEX_ = dynamic_cast< \
                              RemoveRefenrence<arg_type_##_INDEX_>::type>(args[_INDEX_]);

//! [3] 定义展开元式

//! [4] 递归展开

#define DECLARA_AUTO_CAST_ARGUMENT_COUNT_0 \
    ;

#define DECLARA_AUTO_CAST_ARGUMENT_COUNT_1 \
    DECLARA_AUTO_CAST_ARGUMENT_COUNT_0 \
    CAST_ARGUMETN_IN_META_CALL(0)

#define DECLARA_AUTO_CAST_ARGUMENT_COUNT_2 \
    DECLARA_AUTO_CAST_ARGUMENT_COUNT_1 \
    CAST_ARGUMETN_IN_META_CALL(1)

#define DECLARA_AUTO_CAST_ARGUMENT_COUNT_3 \
    DECLARA_AUTO_CAST_ARGUMENT_COUNT_2 \
    CAST_ARGUMETN_IN_META_CALL(2)

#define DECLARA_AUTO_CAST_ARGUMENT_COUNT_4 \
    DECLARA_AUTO_CAST_ARGUMENT_COUNT_3 \
    CAST_ARGUMETN_IN_META_CALL(3)

#define DECLARA_AUTO_CAST_ARGUMENT_COUNT_5 \
    DECLARA_AUTO_CAST_ARGUMENT_COUNT_4 \
    CAST_ARGUMETN_IN_META_CALL(4)

#define DECLARA_AUTO_CAST_ARGUMENT_COUNT_6 \
    DECLARA_AUTO_CAST_ARGUMENT_COUNT_5 \
    CAST_ARGUMETN_IN_META_CALL(5)

#define DECLARA_AUTO_CAST_ARGUMENT_COUNT_7 \
    DECLARA_AUTO_CAST_ARGUMENT_COUNT_6 \
    CAST_ARGUMETN_IN_META_CALL(6)

#define DECLARA_AUTO_CAST_ARGUMENT_COUNT_8 \
    DECLARA_AUTO_CAST_ARGUMENT_COUNT_7 \
    CAST_ARGUMETN_IN_META_CALL(7)

#define DECLARA_AUTO_CAST_ARGUMENT_COUNT_9 \
    DECLARA_AUTO_CAST_ARGUMENT_COUNT_8 \
    CAST_ARGUMETN_IN_META_CALL(8)

#define DECLARA_AUTO_CAST_ARGUMENT_COUNT_10 \
    DECLARA_AUTO_CAST_ARGUMENT_COUNT_9 \
    CAST_ARGUMETN_IN_META_CALL(9)

//! [4] 递归展开

//! [5] 使用展开

#define DECLARA_AUTO_CAST_ARGUMENTS(_COUNT_) \
    DECLARA_AUTO_CAST_ARGUMENT_COUNT_##_COUNT_

//! [5] 使用展开


//---------------------------------------------------------------------------------------

#define CHECK_ARGUMENTS_LENGTH(_ARGUMENTS_, _FUNCTION_TYPE_) \
    if()

/*!
Object::Meta Object::metaCall = {
    {
        pair<const string, Object::Meta::Call>(
        "add",
        // int(int, int)
        [](Object* thiz, std::vector<Bridge*> args, Bridge* result)->int{

            if(args.size() < FunctionMeta<Object::add>::value) return (int)State::ArgumentsError;

            // FunctionMeta<Object::add>::value 2
            DEFINE_ARGUMENTS_TYPE(2, Object::add);

            //! arg_type_##_INDEX_;
            // arg_type_0;
            // arg_type_1;


            // args参数的向上转换
            // auto args_0 = dynamic_cast<RemoveRefenrence<arg_type_0>::type>(args[0]);
            // auto args_1 = dynamic_cast<RemoveRefenrence<arg_type_1>::type>(args[1]);

            // FunctionMeta<Object::add>::value 2
            DECLARA_AUTO_CAST_ARGUMENTS(2);

            if( (
                    args_0
                    && args_1
            )) {
                return soften::State::CastError;
            }

            // 这一句斟酌
            auto result_ref = dynamic_cast<RemoveRefenrence<FunctionMeta<Object::add>::Return> >(result);
            result_ref->set(thiz->add(args_0->get(), args_1->get()));


            return (int)soften::State::NormalCall;
        })
    }
};
*/

#endif // CALLHELPER

