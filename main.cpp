#include "traits.h"

#include <complex>
#include <iostream>
#include <functional>
#include <type_traits>

namespace
{
    typedef std::complex<float> complex_t;
    typedef std::function<complex_t(const complex_t&)> complex_function;
    typedef std::conditional<traits::derive_using_complex, complex_t, float>::type function_t;
    typedef std::function<function_t(const function_t&)> function_wrapper;
}

template<typename T>
T f(const T &x) { return cos(x) * sin(x) + log10(x); }

template<typename T1, typename T2>
T2 derive(std::function<T1(const T1&)> f, const T2 &x, const T2 &h)
{
    return (f(x + h) - f(x)) / h;
}

template<typename T1>
T1 derive(complex_function f, const T1 &x, const T1 &h)
{
    auto complex_h = h * complex_t(.0, 1.);
    auto result = f(x + complex_h) / complex_h;
    return result.real();
}

int main()
{
    function_wrapper fw(f<function_t>);
    float x = 50.;
    for (float h = .1; h > 1e-10; h /= 10) {
        std::cout << "h=" << h << " -> " << derive(fw, x, h) << "\n"; 
    }
}

