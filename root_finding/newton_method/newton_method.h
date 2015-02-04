#ifndef NEWTON_METHOD_H_
#define NEWTON_METHOD_H_

#include <functional>
#include <iostream>
#include <cmath>
#include <stdexcept>

/**
 * Try to find the root of the function f using the newton-raphson method.
 */
double newton_raphson(
    const std::function<double(double)> &f,
    const std::function<double(double)> &f_,
    double initial_guess,
    double tolerance=1e-12,
    long int max_iterations=-1,
    bool show_intermediary_values=false
)
{
    auto x = initial_guess;
    auto iterations = 0;
    while (std::abs(f(x)) > tolerance) {
        x = x - f(x) / f_(x);
        iterations++;
        if (iterations > max_iterations) {
            throw std::runtime_error("Couldn't find the root within max_iterations.\n");
        }
        if (show_intermediary_values) {
            std::cout << "x=" << x << "\n";
        }
    }

    return x;
}

#endif
