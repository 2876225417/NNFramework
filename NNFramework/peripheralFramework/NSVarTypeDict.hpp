

#pragma once

namespace NSVarTypeDict{

struct NullParameter;

template<size_t N, template<typename...> class TCont, typename... T>
    struct Create_{
        /* recursion case */
        using type = typename Create_<N - 1,TCont, NullParameter, T...>::type;
    };

template<template<typename...> class TCont, typename...T>
    struct Create_<0, TCont, T...> { /* base case */
        using type = TCont<T...>;
    };
}

