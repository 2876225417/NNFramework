

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
            // cv_queueFull通知其他线程:元素数量超过上限啦，等有空位再推吧(阻塞ing)。
            cv_queueFull.wait(lock);
        queue.push_front(std::move(value));
        // cv_queueEmpty通知其他线程:现在 queue 中有元素哦，快来取出去。
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

    // 尝试推入数据（不阻塞），如果满，等待一段时间，超时返回 false
    bool try_push_for(T value){
        std::unique_lock lock(m_queue);
        if(queue.size() >= lim_queue) return false;
        queue.push_front(std::move(value));
        cv_queueEmpty.notify_one();
        return true;
    }

    // 尝试推入数据（不阻塞），如果满，等待直到时间点，超时返回 false
    bool try_push_until(T value){
        std::unique_lock lock(m_queue);
        if(queue.size() >= lim_queue) return false;
        queue.push_front(std::move(value));
        cv_queueEmpty.notify_one();
        return true;
    }

    // 取元素，一直阻塞，直到 queue 中没有元素
    T pop(){
        std::unique_lock lock(m_queue);
        while(queue.empty())
            // cv_queueEmpty: queue 空啦，快点往里面推元素，不然我就一直阻塞。
            cv_queueEmpty.wait(lock);
        T value = std::move(queue.back());
        queue.pop_back();
        // cv_queueFull: queue 现在不为空，赶紧从里面 pop 元素啊。
        cv_queueFull.notify_one();
        return value;
    }

    // 尝试取元素，不阻塞，如果队列为空，返回 nullopt
    std::optional<T> try_pop(){
        std::unique_lock lock(m_queue);
        if(queue.size() == 0) return std::nullopt;
        T value = std::move(queue.back());
        queue.pop_back();
        cv_queueFull.notify_one();
        return value;
    }

    // 尝试取元素，不阻塞，等待一段时间，超时返回 nullopt
    std::optional<T> try_pop_for(std::chrono::steady_clock::duration timeout){
        std::unique_lock lock(m_queue);
        if(!cv_queueEmpty.wait_for(lock,
                                  timeout,
                                  [&](){ return !(queue.size() == 0); }))
            return std::nullopt;
        T value = std::move(queue.back());
        queue.pop_back();
        cv_queueFull.notify_one();
        return value;
    }

    // 尝试取元素，不阻塞，等待直到时间点，超时返回 nullopt
    std::optional<T> try_pop_until(std::chrono::steady_clock::time_point timeout){
        std::unique_lock lock(m_queue);
        if(!cv_queueEmpty.wait_until(lock,
                                     timeout,
                                     [&](){ return !(queue.size() == 0); }))
            return std::nullopt;
        T value = queue.back();
        queue.pop_back();
        cv_queueFull.notify_one();
        return value;
    }
};





