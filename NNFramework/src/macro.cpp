


#include <iostream>
#include <type_traits>
#include <vector>
#include <functional>
#include <string>
#include <algorithm>


template<class T, T N>
std::string get_int_name(){
    std::string s = __PRETTY_FUNCTION__;
    //std::cout << "Length: " << s.length() << '\n';
    //std::cout << "Original __PRETTY_FUNCTION__: " << s << '\n';
    auto pos = s.find("N = ");
    pos += 4;
    auto pos2 = s.find_first_of(']', pos);
    return s.substr(pos, pos2 - pos);
}

enum Color{
    RED = 1,
    GREEN = 2,
    BLUE = 3,
    YELLOW = 4,
};

/* template<class T>
std::string get_int_name_dynamic(T n){
    if(n == (T)1) return get_int_name<T, (T)1>();
    if(n == (T)2) return get_int_name<T, (T)2>();
    if(n == (T)3) return get_int_name<T, (T)3>();
}*/


template<int N>
struct integral_constant{
    static constexpr int value = N;
};

template<int Beg, int End, class F>
void static_for(const F& func){
    if constexpr (Beg == End) return;
    else{
        func(integral_constant<Beg>());
        static_for<Beg + 1, End>(func);
    }
}


template<class T>
std::string get_int_name_dynamic(T n){
    std::string ret;
    static_for<0, 10>([&](auto ic){
        constexpr auto i = ic.value;
        if(n == (T)i.value) ret =  get_int_name<T, (T)i.value>();
    });
    return ret;
}

int assign_ptr(int& ptr){
    ptr = 23;
    return 1;
}

void func(int* a, int size){
    printf("%d", sizeof(a) / sizeof(a[0]));
}


#include "../headers/deprecated.h"
#include "../headers/safeVec.hpp"
#include <execution>
#include "../headers/STLAddons.hpp"
#include <Python.h>
#include <atomic>
#include "../headers/tools.h"


struct C{
        //std::vector<int> vi{3};
        std::vector<int> vi = std::vector<int>(4);




    };


int main(){

    std::cout << Tools::DirectoryHelper::GetCurrentWorkingPath();


    C c;
    std::cout <<  c.vi;
    Py_Initialize();

    PyObject* sysPath = PySys_GetObject("path");

    PyList_Append(sysPath, PyUnicode_FromString("../NNFramework/py"));

    PyObject* pName = PyUnicode_DecodeFSDefault("yolo_detect.py");
    PyObject* pModule = PyImport_Import(pName);
    Py_XDECREF(pName);

    if(pModule == nullptr){
        PyErr_Print();
        std::cerr << "Not found py module";
    }







//    std::vector<int> data(1'000'000'000);
//    std::generate(data.begin(),
//                  data.end(),
//                  []() { return rand() % 100; } );
//
//    C c;

//
//    long long cnt = std::count_if(
//                            data.begin(),
//                            data.end(),
//                            [](int n){ return std::sqrt(n) > 60; }
//    );
//
//    std::cout << cnt;




//    safeVec::safeVec<int> svi{1, 2, 3};
//    int* ptr_ = &svi[4];
//
//
//    std::vector<int> vi(4);
//    std::cout << "size of vi: " << vi.size() << '\n';
//    int* ptr = &vi[1000];


//    auto cnt = std::count_if(vi.begin(),
//                             vi.end(),
//                             deprecatedFunc::bind2nd(std::greater<int>(), 4));
//
//    std::cout << cnt;

//    char str[11];
//    printf("input str: " );
//    scanf("%10s\n", str);
//    printf("str: %s", str);

//    char str[] = {'p','p', 'Q', 'w', 'Q', 'q', 'q', 0};
//    int len = sizeof(str);
//    printf("%*s",len,  str);
//    printf("\n%s", str);


    //    int a[6] = {1, 2, 3, 4, 5, 6};
//    func(a, 6);
//



//    int32_t i = 32;
//    printf("%d", i);
//    assign_ptr(i);
//    printf("%d", i);


//    float f = 1.32f;
//    printf("%.2f\n", f);
//    void* p = &f;
//    *(float* )p = 3.14f;
//    printf("%.2f", f);


//    float f = -1.2f;
//    printf("%f", std::abs(f));
//
//    std::cout << "intptr_t: " << sizeof(intptr_t) << "int64_t: " << sizeof(int64_t)
//    << "uintptr: " << sizeof(uintptr_t) << "uint64_t: " << sizeof(uint64_t);

    //constexpr Color c = YELLOW;
    //std::cout << get_int_name_dynamic(c);
}