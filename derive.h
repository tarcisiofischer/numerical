#include "traits.h"

#include <complex>
#include <functional>
#include <type_traits>

namespace
{
    typedef std::complex<double> complex_t;
    typedef std::function<complex_t(const complex_t&)> complex_function;
    typedef std::conditional<traits::derive_using_complex, complex_t, double>::type function_t;
    typedef std::function<function_t(const function_t&)> function_wrapper;
}

template<typename T1, typename T2>
T2 derive(std::function<T1(const T1&)> f, const T2 &x, const T2 &h=traits::h())
{
    return (f(x + h) - f(x)) / h;
}

template<typename T1>
T1 derive(complex_function f, const T1 &x, const T1 &h=traits::h())
{
    auto complex_h = complex_t(.0, h);
    auto result = f(x + complex_h) / complex_h;
    return result.real();
}

