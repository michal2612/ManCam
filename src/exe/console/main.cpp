import core_pipeline;

#include <iostream>

struct example
{
    explicit example(bool shouldFail = false)
        : shouldFail(shouldFail) {
    }

    void run() const {
        std::cout << "I am running!" << std::endl;
        if (shouldFail)
        {
            throw;
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

    pipeline::core_pipeline<example> p{};
    p.addTask(e1);
    p.addTask(e2);

    p.destroy();

    return 0;
}
