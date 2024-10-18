

#ifndef SAFEVEC_HPP
#define SAFEVEC_HPP

#include <initializer_list>
#include <stdexcept>
#include <vector>

namespace safeVec{

template<typename T>
class safeVec{
private: std::vector<T> elems;
public:
    safeVec() = default;

    safeVec(std::initializer_list<T> init_list): elems(init_list){ }

    /* handle vector subscript out of range */
    T& operator[](std::size_t _idx){
        /* 使用错误日志进行输出 */
        if(_idx > elems.size()) throw std::out_of_range("Index of range!");
        return elems[_idx];
    }

    const T& operator[](std::size_t _idx) const {
        if(_idx > elems.size()) throw std::out_of_range("Index of range!");
        return elems[_idx];
    }

    /* todo: Other interfaces
     */
    void push(const T& _val){
        elems.emplace_back(_val);
    }

    bool empty() const{
        return elems.empty();
    };

    size_t size() const{
        return elems.size();
    }
};
}


#endif

