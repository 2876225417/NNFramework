



#ifndef DEPRECATED_H
#define DEPRECATED_H


namespace deprecatedFunc{

#if __cplusplus > 201703L

/* std::bind2nd is deprecated in C++11 and removed in C++17 */
template<class Fn, class Ty>
auto bind2nd(Fn fn, Ty value){
    return [fn, value](auto x){
        return fn(x, value);
    };
}

#endif  // __cplusplus < 201703L

}

#endif