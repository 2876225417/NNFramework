#pragma once

#ifndef STLADDONS_HPP
#define STLADDONS_HPP

#include <iostream>
#include <vector>


namespace std{

template<typename T>
std::ostream& operator<<(ostream& os, const std::vector<T>& v){
    os << '{';
    auto it = v.begin();
    if(it != v.end()){
        os << *it;
        for(++it; it != v.end(); ++it)
            os << ',' << *it;
    }
    os << '}';
    return os;
}

}

#endif