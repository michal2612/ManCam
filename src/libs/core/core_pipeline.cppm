module;

#include <atomic>
#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>
#include <functional>

export module core_pipeline;

namespace pipeline
{
    export template<class T>
    concept Worker = requires(T task)
    {
        { task.run() };
        { task.onSuccess() };
        { task.onFailure() };
    };

    export template<Worker T>
    class core_pipeline
    {
        std::mutex tasksMutex;
        std::condition_variable_any tasksCv;
        std::queue<T> tasks;
        std::atomic<bool> stopRequested{false};

        std::jthread queueThread;
    public:
        explicit core_pipeline() {
            queueThread = std::jthread([this] { run(); });
        }

        void addTask(const T& task) {
            {
                std::lock_guard lock(tasksMutex);
                if (stopRequested) {
                    return;
                }
                tasks.push(task);
            }
            tasksCv.notify_one();
        }

        void stop() {
            {
                std::lock_guard lock(tasksMutex);
                stopRequested = true;
            }
            tasksCv.notify_all();  // stopping the program, notify is required

            if (queueThread.joinable())
                queueThread.join();
        }

        ~core_pipeline() {
            stop();
        }

        // don't allow copying
        core_pipeline(const core_pipeline&) = delete;
        core_pipeline& operator=(const core_pipeline&) = delete;

    private:
        void run() {
            while (true)
            {
                T* task = nullptr;
                {
                    std::unique_lock lock(tasksMutex);
                    tasksCv.wait(lock, [this]{ return stopRequested || !tasks.empty(); });
                    if (stopRequested && tasks.empty())
                    {
                        return;
                    }

                    task = &tasks.front();
                    tasks.pop();
                }
                try
                {
                    task->run();
                    task->onSuccess();
                }
                catch (...)
                {
                    task->onFailure();
                }
            }
        }
    };
}