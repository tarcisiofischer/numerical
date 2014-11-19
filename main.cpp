#include <complex>
#include <iostream>
#include <functional>

template<typename T>
T f(const T &x) { return cos(x) * sin(x) + log10(x); }

template<typename T1, typename T2>
T1 derivate(std::function<T2(T2)> f, const T1 &x, const T1 &h)
{
    return (f(x + h) - f(x)) / h;
}

typedef std::complex<float> complex_t;
typedef std::function<complex_t(complex_t)> complex_function;
template<typename T1>
T1 derivate(complex_function f, const T1 &x, const T1 &h)
{
    auto complex_h = h * complex_t(.0, 1.);
    auto result = f(x + complex_h) / complex_h;
    return result.real();
}

int main()
{
    {
        float x = 50.;
        for (float h = .1; h > 1e-10; h /= 10) {
            std::cout << "h=" << h << " -> " << derivate<float, float>(f<float>, x, h) << "\n"; 
        }
    }

    {
        float x = 50.;
        for (float h = .1; h > 1e-10; h /= 10) {
            std::cout << "h=" << h << " -> " << derivate<float>(f<complex_t>, x, h) << "\n"; 
        }
    }
}
