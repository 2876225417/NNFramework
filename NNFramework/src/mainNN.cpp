

#include <iostream>
#include <type_traits>
#include <vector>


template<bool AddOrRemoveRef> struct Fun_;

template<>
struct Fun_<true>{
    template<typename T>
    using type = std::add_lvalue_reference_t<T>;
};

template<>
struct Fun_<false>{
    template<typename T>
    using type = std::remove_reference_t<T>;
};

template<bool AddOrRemove, typename T>
using Fun = typename Fun_<AddOrRemove>::template type<T>;

template<typename T>
using Res_ = Fun<false, T>;


template<int... Vals> struct IntContainer;

template<bool... Vals> struct BoolContainer;

template<typename... Types> struct TypeContainer;

template<template<typename> class... T> struct TemplateCont;
template<template<typename...> class... T> struct TemplateCont2;

template<int... Vals> struct IntContainer{ };

template<int First, int... Rest>
struct IntContainer<First, Rest...>{
    static void print(){
        std::cout << First << ' ';
        IntContainer<Rest...>::print();
    }
};

template<>
struct IntContainer<>{
    static void print(){
        std::cout << std::endl;
    }
};

template<bool... Vals> struct BoolContainer{ };

template<bool First, bool... Rest>
struct BoolContainer<First, Rest...>{
    static void print(){
        std::cout << (First ? "true" : "false") << ' ';
        BoolContainer<Rest...>::print();
    }
};

template<>
struct BoolContainer<>{
    static void print(){
        std::cout << std::endl;
    }
};

template<typename... Types> struct TypeContainer{ };

template<typename First, typename... Rest>
struct TypeContainer<First, Rest...>{
    static void print(){
        std::cout << typeid(First).name() << ' ';
        TypeContainer<Rest...>::print();
    }
};

template<>
struct TypeContainer<>{
    static void print(){
        std::cout << std::endl;
    }
};

template<template<typename> class... T> struct TemplateCont{ };

template<typename T>
struct Ex{
    static void print(){
        std::cout << "Example<" << typeid(T).name() << ">\n";
    }
};

template<template<typename> class First, template<typename> class... Rest>
struct TemplateCont<First, Rest...>{
    template<typename T>
    static void invoke(){
        First<T>::print();
        TemplateCont<Rest...>::template invoke<T>();
    }
};

template<>
struct TemplateCont<>{
    template<typename T>
    static void invoke() { }
};

template<template<typename...> class... T> struct TemplateCont2{ };

template<typename... Ts>
struct Ex_{
    static void print(){
        std::cout << "Ex_\n";
    }
};


template<template<typename...> class First, template<typename...> class... Rest>
struct TemplateCont2<First, Rest...>{
    static void invoke(){
        First<>::print();
        TemplateCont2<Rest...>::invoke();
    }
};

template<>
struct TemplateCont2<>{
    static void invoke(){ }
};

template<typename T>
struct RemoveReferenceConst_{
private: using inter_type = typename std::remove_reference<T>::type;
public: using type = typename std::remove_const<inter_type>::type;
};

template<typename T>
using RemoveReferenceConst = typename RemoveReferenceConst_<T>::type;

/*
template<typename T>
struct _RemoveReferenceConst_{
using type = typename std::remove_const<inter_type>::type;
using inter_type = typename std::remove_reference<T>::type;
};
*/

struct A; struct B;

template<typename T> struct C{ };

template<>
struct C<int>{
    C(){ std::cout << "PS: int\n"; }
};


template<typename T>
struct Fun1_{
    constexpr static size_t value = 0;
    Fun1_(){ std::cout << typeid(T).name() << '\n'; }
};

template<>
struct Fun1_<A>{
    constexpr static size_t value = 1;
};

template<>
struct Fun1_<B>{
    constexpr static size_t value = 2;
};

template<typename T>
struct Fun1_<C<T>>{

};

struct A_; struct B_;

template<typename T>
constexpr size_t Fun2_ = 0;

template<>
constexpr size_t Fun2_<A> = 1;

template<>
constexpr size_t Fun2_<B> = 2;


template<typename TW>
struct Wrapper{
    template<typename T, typename TDummy = void>
    struct Fun3_{
        constexpr static size_t value = 0;
    };

    template<typename TDummy>
    struct Fun3_<int, TDummy>{
        constexpr static size_t value = 1;
    };
};

template<bool IsFeedbackOut, typename T, std::enable_if_t<IsFeedbackOut>* = nullptr>
auto FeedbackOut_(T&& input){
    std::cout << "Type: " << typeid(T).name() << ", value: " << input << '\n';
}

template<bool IsFeedbackOut, typename T, std::enable_if_t<!IsFeedbackOut>* = nullptr>
auto FeedbackOut_(T&& input){
    std::cout << "Type: " << typeid(T).name() << ", value: " << input << '\n';
}

/* auto res(bool check){
    if(check) return (int)0;
    else return (double)0;
}*/

template<bool Check, std::enable_if_t<Check>* = nullptr>
auto fun(){ return (int)0; }

template<bool Check, std::enable_if_t<!Check>* = nullptr>
auto fun(){ return (double)0; }

template<bool Check>
auto wrap(){ return fun<Check>; }

template<bool Check>
auto fun(){
    if constexpr(Check){ return (int)0; }
    else return (double)0;
}



using UI = unsigned int;

UI countOnes(UI n){
    if(n == 0) return 0;
    return (n & 1) + countOnes(n >> 1);
}


template<size_t Input>
constexpr size_t OnesCount = (Input % 2) + OnesCount<(Input >> 1)>;

template<>
constexpr size_t OnesCount<0> = 0;

size_t CountOnes(size_t Input){
    size_t cnt = 0;
    while(Input){
        cnt += Input % 2;
        Input /= 2;
        // std::cout << "Input: " << Input << '\n';
    }
    return cnt;
}

template<size_t Input>
constexpr size_t OnesCount1_(){
    if constexpr(Input == 0) return 0;
    else return (Input % 2) + OnesCount1_<Input / 2>();
}


template<size_t... Inputs>
constexpr size_t Accumulate = 0;

template<size_t CurInput, size_t... Inputs>
constexpr size_t Accumulate<CurInput, Inputs...>
        = CurInput + Accumulate<Inputs...>;

template<size_t... Inputs>
constexpr size_t Accumulate_(){
    if constexpr(sizeof...(Inputs) == 0) return 0;
    else return (0 + ... + Inputs);
}


template<typename... TypeInputs> struct Ins;

template<typename CurInput_Tp, typename... Inputs_Tp>
struct Ins<CurInput_Tp, Inputs_Tp...>{
    static void print(){
        std::cout << typeid(CurInput_Tp).name() << '\n';
        Ins<Inputs_Tp...>::print();
    }
};

template<>
struct Ins<>{
    static void print(){
        std::cout << '\n';
    }
};

template<size_t... Values>
constexpr size_t fun(){ return (0 + ... + Values); }

std::vector<int> fibonaci(int n){
    std::vector<int> fib(n);
    fib[0] = 0;
    fib[1] = 1;

    for(int i = 2; i < n; ++i) fib[i] = fib[i - 1] + fib[i - 2];
    return fib;
}

template<typename... Args>
auto getSum(Args... args){
    return (... + (args + 5));
}

template<size_t Input>
constexpr size_t OnesCnt = (Input % 2) + OnesCnt<(Input) / 2>;

template<> constexpr size_t OnesCnt<0> = 0;

constexpr size_t x1 = OnesCnt<9>;
constexpr size_t x2 = OnesCnt<1>;




int main(){
    std::cout << "less arguments: " <<  getSum<>(1, 2, 3);

    std::cout << "cpp std: " << __cplusplus;
    Ins<int, float, int, double>::print();

    std::cout << "Fold expression: " << fun<1, 2, 3, 4, 5>() << '\n';

    std::cout << "Accumulate: " << Accumulate<1, 2, 3, 4, 5> << '\n';

    std::cout << countOnes(9);

    std::cout << "if constexpr(9): " << OnesCount1_<9>();

    std::cout << "Meta Function: " << OnesCount<9>;
    // std::cerr << wrap<true>();
    std::cout << "Runtime Function: " << CountOnes(9);
    FeedbackOut_<true>(123);

    /* std::cout << Wrapper<int>::Fun3_<int>::value;

    Fun1_<int> fun1Int;
    std::cout << Fun1_<int>::value << "\n\n";

    IntContainer<1, 2, 3, 4, 5, 5>::print();
    BoolContainer<true, false, false>::print();
    TypeContainer<int, int, float, bool>::print();
    TemplateCont<Ex, Ex>::invoke<int>();
    TemplateCont2<Ex_, Ex_>::invoke();
    RemoveReferenceConst<const int&> h = 3;
    std::cout << "h: " <<  typeid(h).name();
    */
}



