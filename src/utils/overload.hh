#pragma once

namespace utils
{
    // Allows to create overloaded functor using lambdas
    template <class... Ts>
    struct overload : Ts...
    {
        using Ts::operator()...;
    };
    template <class... Ts>
    overload(Ts...) -> overload<Ts...>;
} // namespace utils
