#include "newton_method.h"

namespace {
    const long int max_iteration = 100;
    const double tolerance = 1e-12;
    const bool show_intermediary_values = false;

    void test_function(
        const std::function<double(double)>& f,
        const std::function<double(double)>& f_,
        double initial_guess)
    {
        try {
            auto value = newton_raphson(
                f,
                f_,
                initial_guess,
                tolerance,
                max_iteration,
                show_intermediary_values
            );
            std::cout << "Results: x = " << value << "\n\n";
        } catch (const std::runtime_error& e) {
            std::cout << e.what() << "\n";
        }
    }

    double f(double x) { return x*x*x - x - 3; }
    double f_(double x) { return 3*x*x - 1; }

    double g(double x) { return sin(x * M_PI / 180) + .5; }
    double g_(double x) { return cos(x * M_PI / 180); }
};


int main()
{
    // Example of bad vs good initial guess for f(x).
    {
        auto x_0 = 0.0;
        std::cout << "Function1: f(x) = x^3 - x - 3 with x_0 = " << x_0 << "\n";
        test_function(f, f_, x_0);
    }

    {
        auto x_0 = 1.0;
        std::cout << "Function1: f(x) = x^3 - x - 3 with x_0 = " << x_0 << "\n";
        test_function(f, f_, x_0);
    }

    // For this example, try to increase max_iterations (to any value > 1000) and set
    // show_intermediary_values to true.
    {
        auto x_0 = 6;
        std::cout << "Function2: g(x) = sin(x) + .5 with x_0 = " << x_0 << "\n";
        test_function(g, g_, x_0);
    }

    return 0;
}
