


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
        //std::vector<intfe.hs> vi{3};
        std::vector<int> vi = std::vector<int>(4);

    };

//
//
//std::string cont = "cont12";
//std::mutex m_cont;
//
//
//void t1(){
//    std::unique_lock<std::mutex> lock(m_cont);
//    cont = "cont2";
//}
//
//void t2(){
//    std::unique_lock lock(m_cont);
//    cont = "cont3";
//    if(cont == "cont3") lock.unlock();
//    else std::cout << "unique_lock willed unlocked.";
//}



#include <thread>
#include <queue>
#include <chrono>
#include <deque>

std::deque<std::string> msg;
std::mutex m_msg;
std::condition_variable cv_msg;
std::condition_variable cv_;
std::queue<int> dataQueue;

bool ready = false;


using namespace std::chrono_literals;

void producer(){
    for(size_t i = 0; i < 5; ++i){
        std::this_thread::sleep_for(1s);

        std::lock_guard<std::mutex> lock(m_msg);
        dataQueue.push(i);
        ready = true;
        std::cout << "Produced " << i << '\n';
        /* 生产好了，唤醒用户线程 */
        cv_.notify_one();
    }
}

void consumer(){
    while(true){
        std::unique_lock<std::mutex> lock(m_msg);
        /* 等待线程被唤醒 未被唤醒 继续等待*/
        cv_.wait(lock, []{ return ready; });
        /* 唤醒后继续执行 */
        while(!dataQueue.empty()){
            int value = dataQueue.front();
            dataQueue.pop();
            std::cout << "Consumed: " << value << '\n';
        }
        ready = false;
    }
}



//void t1(){
//    std::this_thread::sleep_for(5s);
//    std::unique_lock lock(m_msg);
//    // std::this_thread::sleep_for(5s);
//    /* write */
//    msg = "Weather is perishing.\n";
//    cv_.notify_one();
//}
//
//void t2(){
//    std::this_thread::sleep_for(1s);
//    std::unique_lock lock(m_msg);
//    /* while(msg == ""){ // 直到接收到消息
//        lock.unlock();
//        lock.lock();
//    }*/
//    /* switch to other active threads */
//    // std::this_thread::yield();
//    std::cout << "wait: " << (cv_.wait_until(lock, std::chrono::steady_clock::now() + 6s, [](){ return msg != ""; }) ? "successful" : "failed");
//    std::cout << "Message received: " << msg;
//}




//void t1(){
//    std::this_thread::sleep_for(2s);
//    {
//        std::unique_lock lock(m_msg);
//        msg.push_front("好好学习!\n");
//        cv_msg.notify_one();
//    }/* 每次对 msg 进行写操作时都需要上锁，下同 */
//    std::this_thread::sleep_for(2s);
//    {
//        std::unique_lock lock(m_msg);
//        msg.push_front("天天向上!\n");
//        cv_msg.notify_one();
//    }
//    std::this_thread::sleep_for(2s);
//    {
//        std::unique_lock lock(m_msg);
//        msg.push_front("->我是游文飞!\n");
//        cv_msg.notify_one();
//    }
//    std::this_thread::sleep_for(2s);
//    {/* 特殊消息 */
//        std::unique_lock lock(m_msg);
//        msg.push_front("EXIT"); /* flag for exit */
//        cv_msg.notify_all();
//    }
//}

//void t1_1(){
//    std::unique_lock lock(m_msg);
//
//    msg.push_front("好好学习！\n");
//    msg.push_front("天天向上！\n");
//    msg.push_front("->我是游文飞！\n");
//    msg.push_front("EXIT");
//
//    cv_msg.notify_one();
//}

//void t2(){
//    while(1){ /* 一直循环，直到 */
//        std::unique_lock lock(m_msg);
//        while(msg.size() == 0)
//            cv_msg.wait(lock);
//
//        if (msg.back() == "EXIT") break;
//        std::cout << "收到消息(t2)：" << msg.back();
//        msg.pop_back();
//    }
//}

void t3(){
    while(1){
        std::unique_lock lock(m_msg);
        while(msg.size() == 0)
            cv_msg.wait(lock);
        if(msg.back() == "EXIT") break;
        std::cout << "收到消息(t3)：" << msg.back();
        msg.pop_back();
    }
}

template<class T>
struct mt_queue{
private:
    std::deque<T> queue;
    std::mutex m_queue;
    std::condition_variable cv_queue;

public:
    void push(T value){
        std::unique_lock lock(m_queue);
        queue.push_front(std::move(value));
        cv_queue.notify_one();
    }

    T pop(){
        std::unique_lock lock(m_queue);
        while(queue.empty())
            cv_queue.wait(lock);
        T value = std::move(queue.back());
        queue.pop_back();
        return value;
    }

    std::optional<T> try_pop(){
        std::unique_lock lock(m_queue);
        if(queue.empty())
            return std::nullopt;
        T value = std::move(queue.back());
        queue.pop_back();
        return value;
    }

    std::optional<T> try_pop_for(std::chrono::steady_clock::duration timeout){
        std::unique_lock lock(m_queue);
        if(!cv_msg.wait_for(lock,
                            timeout, /* 超时时间 */
                            [&]{
                                return !queue.empty();
                            }))
            return std::nullopt;
        T value = std::move(queue.back());
        queue.pop_back();
        return value;
    }

    std::optional<T> try_pop_until(std::chrono::steady_clock::time_point timeout){
        std::unique_lock lock(m_queue);
        if(!cv_msg.wait_until(lock,
                              timeout, /* 超时时间点 */
                              [&]{
                                    return std::nullopt;
                                }))
            return std::nullopt;
        T value  = std::move(queue.back());
        queue.pop_back();
        return value;
    }

};

mt_queue<std::string> msg_q;

void t1(){

    msg_q.push("好好学习!\n");
    std::this_thread::sleep_for(1s);
    msg_q.push("天天向上!\n");
    std::this_thread::sleep_for(1s);
    msg_q.push("->我是游文飞!\n");
    std::this_thread::sleep_for(1s);
    msg_q.push("EXIT");
}


void t2Orig(){

}

void t2() {
    while (1) {
        if (auto msg_ = msg_q.try_pop_for(100ms)) {
            if (*msg_ == "EXIT") break;
            std::cout << "Received message: " << *msg_;
        } else {
            std::cout << "Not receive any messages!\n";
        }
    }
}

int main(){
    auto t1_ = std::chrono::steady_clock::now();
    std::vector<std::jthread> pool;
    pool.push_back(std::jthread(t1));
    pool.push_back(std::jthread(t2));
    // pool.push_back(std::jthread(t3));
    pool.clear();

    std::cout << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now().time_since_epoch()).count();

    auto t2_ = std::chrono::steady_clock::now();
    std::cout << "Time cost: " << t2_ - t1_;

    //for(auto&& t: pool) t.join();

    // std::cout << Tools::GenHelper::GetCurrentWorkingPath();
//    std::cout << Tools::GenHelper::GetCurrentWorkingPath();
//
//    C c;
//    std::cout <<  c.vi;
//    Py_Initialize();
//
//    PyObject* sysPath = PySys_GetObject("path");
//
//    PyList_Append(sysPath, PyUnicode_FromString("../NNFramework/py"));
//
//    PyObject* pName = PyUnicode_DecodeFSDefault("yolo_detect");
//    PyObject* pModule = PyImport_Import(pName);
//    Py_XDECREF(pName);
//
//    if(pModule == nullptr){
//        PyErr_Print();
//        std::cerr << "Not found py module";
//    }








//    std::vector<intfe.hs> data(1'000'000'000);
//    std::generate(data.begin(),
//                  data.end(),
//                  []() { return rand() % 100; } );
//
//    C c;

//
//    long long cnt = std::count_if(
//                            data.begin(),
//                            data.end(),
//                            [](intfe.hs n){ return std::sqrt(n) > 60; }
//    );
//
//    std::cout << cnt;




//    safeVec::safeVec<intfe.hs> svi{1, 2, 3};
//    intfe.hs* ptr_ = &svi[4];
//
//
//    std::vector<intfe.hs> vi(4);
//    std::cout << "size of vi: " << vi.size() << '\n';
//    intfe.hs* ptr = &vi[1000];


//    auto cnt = std::count_if(vi.begin(),
//                             vi.end(),
//                             deprecatedFunc::bind2nd(std::greater<intfe.hs>(), 4));
//
//    std::cout << cnt;

//    char str[11];
//    printf("input str: " );
//    scanf("%10s\n", str);
//    printf("str: %s", str);

//    char str[] = {'p','p', 'Q', 'w', 'Q', 'q', 'q', 0};
//    intfe.hs len = sizeof(str);
//    printf("%*s",len,  str);
//    printf("\n%s", str);


    //    intfe.hs a[6] = {1, 2, 3, 4, 5, 6};
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