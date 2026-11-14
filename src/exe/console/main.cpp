import corePipeline;

#include <iostream>
#include <thread>

struct example
{
    explicit example(bool shouldFail = false)
        : shouldFail(shouldFail) {
    }

    void run() const {
        std::cout << "I am running!" << std::endl;
        if (shouldFail)
        {
            throw std::runtime_error("Task failed!");
        }
    }

    void onSuccess() const {
        std::cout << "Success!" << std::endl;
    }

    void onFailure() const {
        std::cout << "Failure!" << std::endl;
    }

private:
    bool shouldFail;
};

int main() {
    example e1;
    example e2(true);

    pipeline::Pipeline<example> p{};
    p.addTask(e1);
    p.addTask(e2);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    return 0;
}
