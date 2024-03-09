#pragma once

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>

namespace Picasso::Engine::Core
{
    class ThreadPool
    {
    public:
        ThreadPool(size_t threads) : m_Stop(false)
        {
            for (size_t i = 0; i < threads; ++i)
            {
                m_Workers.emplace_back([this]
                                       {
                while(true) {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(m_Queuemutex);
                        m_Condition.wait(lock, [this] { return m_Stop || !m_Tasks.empty(); });
                        if(m_Stop && m_Tasks.empty())
                            return;
                        task = std::move(m_Tasks.front());
                        m_Tasks.pop();
                    }

                    task();
                } });
            }
        }

        ~ThreadPool()
        {
            {
                std::unique_lock<std::mutex> lock(m_Queuemutex);
                m_Stop = true;
            }
            m_Condition.notify_all();
            for (std::thread &worker : m_Workers)
                worker.join();
        }

        template <class F, class... Args>
        auto Enqueue(F &&f, Args &&...args)
            -> std::future<typename std::result_of<F(Args...)>::type>
        {
            using return_type = typename std::result_of<F(Args...)>::type;

            auto task = std::make_shared<std::packaged_task<return_type()>>(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...));

            std::future<return_type> res = task->get_future();
            {
                std::unique_lock<std::mutex> lock(m_Queuemutex);

                // Don't allow enqueueing after stopping the pool
                if (m_Stop)
                    throw std::runtime_error("enqueue on stopped ThreadPool");

                m_Tasks.emplace([task]()
                                { (*task)(); });
            }
            m_Condition.notify_one();
            return res;
        }

    private:
        std::vector<std::thread> m_Workers;
        std::queue<std::function<void()>> m_Tasks;
        std::mutex m_Queuemutex;
        std::condition_variable m_Condition;
        bool m_Stop;
    };
}

#endif // THREAD_POOL_H