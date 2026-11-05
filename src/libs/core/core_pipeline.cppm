module;

#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>

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
        std::jthread queueThread;
    public:
        explicit core_pipeline() {
            queueThread = std::jthread([this] { run(); });
        }

        void addTask(const T& task) {
            std::lock_guard lock(tasksMutex);
            tasks.push(task);
            tasksCv.notify_one();
        }

        void pause() const {
            // TO DO
        }

        void destroy() {
            queueThread.join();
            delete this;
        }

        ~core_pipeline() = default;

    private:
        void run() {
            while (true)
            {
                T task;
                {
                    std::unique_lock lock(tasksMutex);
                    tasksCv.wait(lock, [this]{ return !tasks.empty(); });
                    if (tasks.empty())
                    {
                        return;
                    }

                    task = std::move(tasks.front());
                    tasks.pop();
                }
                try
                {
                    task.run();
                    task.onSuccess();
                }
                catch (...)
                {
                    task.onFailure();
                }
            }
        }
    };
}