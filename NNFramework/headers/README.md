


# 关于 `mt_queue.hpp` 的结构介绍

这是一个基于消息的多线程同步(不共享，易处理)。

> `mt_queue`的特点：
> 
> * 线程之间统一用队列通信，无显式锁。
> * 唯一的锁只出现在封装的队列内部，用户无法直接操作，没有死锁的可能。
> * 线程之间除了队列外，没有任何共享的可写变量，使得线程安全。


`mt_queue`的成员变量:
* `queue`：基于`std::deque`实现的可`push_back()`和`push_fron()`队列。
* `m_queue`：针对同一资源访问的唯一互斥锁。
* `cv_queueEmpty`：用于处理`queue`元素为空时不能继续取出导致阻塞的条件变量。
* `cv_queueFull`：用于处理`queue`元素满时不能继续推导致阻塞的条件变量。
* `lim_queue`：`queue`的元素数量上限。

`push`实现：
* 一般实现：
  * 当元素数量达到`lim_queue`时阻塞。
* `try`实现：
  * `_pop`：非阻塞式，达到上限，返回 `false`。
  * `_pop_for`：非阻塞式，达到上限，并等待一段时间，超时返回 `false`。
  * `_pop_until`：非阻塞式，达到上限，顶等待至时间点，超时返回 `false`。

`pop`实现：
* 一般实现：
  * 当元素数量为**0**时(队列为空)阻塞。
* `try`实现：
  * `_pop`：非阻塞式，队列为空时，返回`nullopt`。
  * `_pop_for`：非阻塞式，队列为空时，等待一段时间，超时返回`nullopt`。
  * `_pop_until`：非阻塞式，队列为空时，等待至时间点，超时返回`nullopt`。

