#include "derive.h"

#include <iostream>

template<typename T>
T f(const T &x) { return cos(x) * sin(x) + log10(x); }

int main()
{
    function_wrapper fw(f<function_t>);
    std::cout << "h=" << traits::h() << " -> " << derive(fw, 50.) << "\n"; 
}

