#include <blitz/TinyVec.h>
#include <blitz/TinyMath.>

using namespace blitz;

template<class T>
void optimizationSink(T&);

void foo()
{
    TinyMatrix<float,3,3> A;
    TinyVector<float,3> b, c;

    optimizationSink(A);
    optimizationSink(b);

    c = product(A,b);

    optimizationSink(c);
}
