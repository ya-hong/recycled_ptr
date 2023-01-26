#include <iostream>

#include "recycled_ptr/recycled_ptr.hpp"
#include "recycled_ptr/root_ptr.hpp"
// using namespace recycled_ptr;

class node {
public:
	int v;
	recycled_ptr::recycled_ptr<node> ptr;
};

int main() {
	using namespace recycled_ptr;
	{
		auto p1 = make_object<node>();
		auto p2 = make_object<node>();
		auto p3 = make_object<node>();
		p1->v = 1, p2->v = 2, p3->v = 3;
		p1->ptr = p2;
		p2->ptr = p3;
		p3->ptr = p1;

		int* p = &(p3->v);

		std::cout << *p << std::endl;

		static_mem_tracker::garbage_collect();

		std::cout << *p << std::endl;
	}
	{
		auto p1 = make_object<node>();
		auto p2 = make_object<node>();
		auto p3 = make_object<node>();
		p1->v = 1, p2->v = 2, p3->v = 3;
		p1->ptr = p2;
		p2->ptr = p3;
		p3->ptr = p1;
		root_ptr<node> pp = p1;

		int* p = &(p3->v);

		std::cout << *p << std::endl;

		static_mem_tracker::garbage_collect();

		std::cout << *p << std::endl;
	}
}
