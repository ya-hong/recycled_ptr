#include <iostream>

#include "recycled_ptr/recycled_block.h"
#include "recycled_ptr/recycled_ptr.h"

int main() {
	using namespace recycled_ptr;
	auto ptr = make_object<int>(123);
	std::cout << *ptr << std::endl;
}