#ifndef FUNCTION_META
#define FUNCTION_META

/**

#include <iostream>
#include <type_traits>
#include <tuple>

void fun(int, int) {}

struct A{};

template< typename T >
struct GetParam1Type;

template< typename T, typename U, typename V >
struct GetParam1Type< T( U, V ) >
{
    typedef U Result;
};

template< typename T, typename U, typename V , typename R>
struct GetParam1Type< T( U, V ,R) >
{
    typedef U Result;
};

template< typename T >
struct GetParam1Type< T( void ) >
{
    typedef void Result;
};

template< typename T, typename U, typename V >
struct GetParam1Type< T( * )( U, V) >
{
    typedef U Result;
};

template< typename T, typename U, typename V , typename R>
struct GetParam1Type< T( * )( U, V ,R) >
{
    typedef U Result;
};

template< typename T >
struct GetParam1Type< T( * )( void ) >
{
    typedef void Result;
};

template< typename T, typename U, typename V, typename R >
struct GetParam1Type< T ( V::* )( U, R ) >
{
    typedef U Result;
};

template< typename T, typename U, typename V, typename R , typename A>
struct GetParam1Type< T ( V::* )( U, R ,A) >
{
    typedef U Result;
};

template< typename T, typename V >
struct GetParam1Type< T ( V::* )( void ) >
{
    typedef void Result;
};



typedef void ( A::*fun1 )( int, long, double );
typedef void ( A::*fun2 )(  );
typedef long fun3( int, long, double );
typedef long fun4(  );
typedef long ( *fun5 )( int, long, double );
typedef long ( *fun6 )(  );

int test_function_meta( void )
{
    std::cout << std::is_same< GetParam1Type< fun1 >::Result, int >::value << std::endl;
    std::cout << std::is_same< GetParam1Type< fun2 >::Result, void >::value << std::endl;
    std::cout << std::is_same< GetParam1Type< fun3 >::Result, int >::value << std::endl;
    std::cout << std::is_same< GetParam1Type< fun4 >::Result, void >::value << std::endl;
    std::cout << std::is_same< GetParam1Type< fun5 >::Result, int >::value << std::endl;
    std::cout << std::is_same< GetParam1Type< fun6 >::Result, void >::value << std::endl;
    getchar();
    return 0;
}
*/

#endif // FUNCTION_META

