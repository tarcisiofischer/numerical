#include "derive.h"

#include <iostream>
#include <vector>

template<typename T>
class Vars
{
public:
    virtual T& operator[](unsigned int i) = 0;
    virtual const T& operator[](unsigned int i) const = 0;
};

template<typename T>
class VarsImpl : Vars<T>
{
public:
    VarsImpl() {}
    VarsImpl(const std::vector<T> &values) : _values(values) {}

    T& operator[](unsigned int i)
    {
        return _values[i];
    }

    const T& operator[](unsigned int i) const
    {
        return _values[i];
    }

private:
    std::vector<T> _values;
};

template<typename T>
T f(const T &x) { return cos(x) * sin(x) + log10(x); }

int main()
{
    function_wrapper fw(f<function_t>);
    VarsImpl<float> params({50.});
    auto returnValues = derive(fw, params);
    std::cout << returnValues[0];
}
