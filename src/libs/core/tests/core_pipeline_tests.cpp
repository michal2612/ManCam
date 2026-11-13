#include <gtest/gtest.h>
#include <condition_variable>
#include <mutex>

import core_pipeline;

struct example
{
    explicit example(int& number, std::condition_variable& cv, bool& wait)
        : number(number), wait(wait), cv(cv) {
    }

    void run() const {
        number++;
    }

    void onSuccess() {
        if (number == 2)
        {
            wait = true;
            cv.notify_all();
        }
    }

    void onFailure() const {
        throw std::runtime_error("Failure!");
    }

    int& number;
    bool& wait;
    std::condition_variable& cv;
};

TEST(Pipeline, PipelineWithOneTask) {
    int number = 0;
    std::condition_variable cv;
    std::mutex mtx;
    bool flag = false;
    const example e1(number, cv, flag);
    const example e2(number, cv, flag);

    pipeline::core_pipeline<example> p{};
    p.addTask(e1);
    p.addTask(e2);

    std::unique_lock lk(mtx);

    cv.wait(lk, [&flag, &p]
    {
        if (flag)
        {
            p.stop();
        }
        return flag;
    });
    EXPECT_EQ(number, 2);
}