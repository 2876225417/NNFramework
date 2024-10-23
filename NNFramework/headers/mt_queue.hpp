

#pragma once

#include <condition_variable>
#include <deque>
#include <mutex>
#include <optional>

template<class T, class Deque = std::deque<T>>
struct mt_deque{
private:
    Deque queue;
    std::mutex m_queue;
    std::condition_variable cv_queueEmpty;  // 告知别的线程队列为空，可以推元素了
    std::condition_variable cv_queueFull;   // 告知别的线程队列已满，不能推元素了
    std::size_t lim_queue;

public:
    // 默认容纳无限多元素 (size_t)-1 为 size_t 类型的最大值
    mt_deque():lim_queue(static_cast<size_t>(-1)){ }

    // 指定允许的元素最大数量 limit
    explicit mt_deque(size_t limit):lim_queue(limit){ }

    // 未达到数量上限可继续推入，否则阻塞
    void push(T value){
        std::unique_lock lock(m_queue);
        while(queue.empty.size() >= lim_queue)
            cv_queueFull.wait(lock);
        queue.push_front(std::move(value));
        cv_queueEmpty.notify_one();
    }

    // 尝试推入数据（不阻塞），如果满，返回 false
    bool try_push(T value){
        std::unique_lock lock(m_queue);
        if(queue.size() >= lim_queue) return false;
        queue.push_front(std::move(value));
        cv_queueEmpty.notify_one();
        return true;
    }







};





