// Coroutine.cpp: определяет точку входа для приложения.
//

#include "Coroutine.h"

Generator<std::string> test(std::string text) {
    for (int i = 0; i < 10; i++) {
        co_yield text + std::to_string(i);
    }
    co_return;
}

int main()
{
	std::cout << "Hello CMake." << std::endl;
    auto gen = test("testfunc");
    for (int i = 0; gen; ++i) {
        std::cout << gen() << std::endl;
    }
	return 0;
}
