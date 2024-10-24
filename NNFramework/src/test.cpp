


#include <iostream>

/* template<size_t Input>
constexpr size_t onesCount = (Input % 2) + onesCount<(Input / 2)>;

template<> constexpr size_t onesCount<0> = 0; */

/* template<size_t A>
struct Wrap_{
    template<size_t ID, typename TDummy = void>
    struct imp{
        constexpr static size_t value = ID + imp<ID - 1>::value;
    };

    template<typename TDummy>
    struct imp<0, TDummy>{
        constexpr static size_t value = 0;
    };

    template<size_t ID>
    constexpr static size_t value = imp<A + ID>::value;
};*/

/* template<size_t ID>
struct imp{ constexpr static size_t value = ID + imp<ID - 1>::value; };

template<>
struct imp<0> { constexpr static size_t value = 0; };

template<size_t A>
struct Wrap_{
    template<size_t ID>
    constexpr static size_t value = imp<A + ID>::value;
};*/

/* template<size_t N>
constexpr bool is_odd = ((N % 2) == 1);

template<size_t N>
struct AllOdd_{
    constexpr static bool is_cur_odd = is_odd<N>;
    constexpr static bool is_pre_odd = AllOdd_<N - 1>::value;
    constexpr static bool value = is_cur_odd && is_pre_odd;
};

template<>
struct AllOdd_<0>{
    constexpr static bool value = is_odd<0>;
};*/


/* template<size_t N>
constexpr static size_t is_odd = ((N % 2) == 1);

template<bool cur, typename TNext>
constexpr static bool AndValue = false;

template<typename TNext>
constexpr static bool AndValue<true, TNext> = TNext::value;

template<size_t N>
struct AllOdd_{
    constexpr static bool is_cur_odd = is_odd<N>;
    constexpr static bool value = AndValue<is_cur_odd, AllOdd_<N - 1>>;
};*/

/* template<typename D>class Base { };

class Derived: public Base<Derived>{ }; */

/* template<typename D>
struct Base{
    template<typename T1>
    void Fun(const T1& input){
        D* ptr = static_cast<D*>(this);
        ptr->Imp(input);
    }
};

struct Derived:public Base<Derived>{
    template<typename T1>
    void Imp(const T1& input){
        std::cout << input << '\n';
    }
};*/

template<typename D>
struct Base{
    static void Fun(){
        D::Imp();
    }
};

struct Derive:public Base<Derive>{
    static void Imp(){
        std::cout << "Static function from Derived class\n";
    }
};


float fun(float a, float b, float weight){
    return weight * a + (1 - weight) * b;
}

#include <map>

/* float fun(const std::map<std::string, float>& params){
    auto a_it = params.find("a");
    auto b_it = params.find("b");
    auto weight_id = params.find("weight");

    return (a_it->second * (weight_id->second) +
            b_it->second * (1 - weight_id->second));
}*/

/* template<const char* info>
struct Temp;

constexpr char a[] = "Hello";
using Res = Temp<a>;

struct FParams: public VarTypeDict<A, B, Weight> { };

template<typename TIn>
float fun(const TIn& in){
    auto a = in.template Get<A>();
    auto b = in.template Get<B<();
    auto weight = in.template Get<Weight>();

    return a * weight + (1 - weight) * b;
}*/

/* template<typename... TParameters>
struct VarTypeDict{
    template<typename...TTypes>
    struct Values{
    public:
        template<typename TTag, typename TVal>
        auto Set(TVal&& val)&&;

        template<typename TTag>
        const auto& Get() const;
    };
public:
    static auto Create(){
        using namespace NSVarTypeDict;
        using type = typename Create_<sizeof...(TParameters),Values>::type;
        return type{ };
    }
};*/


#include "NSVarTypeDict.hpp"

template<typename...TParameters>
struct VarTypeDict{
    template<typename... TTypes>
    struct Values{
    public:
        template<typename TTag, typename TVal>
        auto Set(TVal&& val)&&;

        template<typename TTag>
        const auto Get() const;
    };

    static auto Create(){
        using namespace NSVarTypeDict;
        using type = typename Create_<sizeof...(TParameters), Values>::type;
    }
};


struct A;
struct B;
struct C;


int main(){
    VarTypeDict<A, B, C>::Create() ;
//    std::map<std::string, float> params;
//    params["a"] = 1.3f;
//    params["b"] = 2.4f;
//    params["weight"] = 0.1f;

    // std::cerr << fun(params);
   // Derive::Fun();

    //    Derived d;
//    d.Fun("Implementation here");

    // std::cerr << Wrap_<3>::value<2>;
    // std::cerr << Wrap_<10>::value<2>;
}

