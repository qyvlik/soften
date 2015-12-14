#ifndef TEST_CALLMETHOD_TIME
#define TEST_CALLMETHOD_TIME

#include <sys/time.h>

double test_function_time(void (*f)())
{
    timeval start,end;
    gettimeofday(&start,NULL);
    f();
    gettimeofday(&end,NULL);
    return (1000000*(end.tv_sec-start.tv_sec) + end.tv_usec-start.tv_usec)/1000000.0;
}

#endif // TEST_CALLMETHOD_TIME

