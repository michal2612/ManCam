module;

#include <iostream>

export module core;

namespace core
{
    export class ello
    {
    public:
        ello();
        void hi();
    };

    ello::ello() = default;

    void ello::hi()
    {
        std::cout << "hi" << std::endl;
    }
}