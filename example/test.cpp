#include <iostream>

#include "recycled_ptr.hpp"
class node {
public:
	int v;
	gc::recycled_ptr<node> ptr;
};

int main() {
	{
		auto p1 = gc::make_object<node>();
		auto p2 = gc::make_object<node>();
		auto p3 = gc::make_object<node>();
		p1->v = 1, p2->v = 2, p3->v = 3;
		p1->ptr = p2;
		p2->ptr = p3;
		p3->ptr = p1;

		int* p = &(p3->v);

		std::cout << *p << std::endl;

		gc::static_mem_tracker::garbage_collect();

		std::cout << *p << std::endl;  // 应该被删除
	}
	{
		auto p1 = gc::make_object<node>();
		auto p2 = gc::make_object<node>();
		auto p3 = gc::make_object<node>();
		p1->v = 1, p2->v = 2, p3->v = 3;
		p1->ptr = p2;
		p2->ptr = p3;
		p3->ptr = p1;
		gc::root_ptr<node> pp = p1;

		int* p = &(p3->v);

		std::cout << *p << std::endl;

		gc::static_mem_tracker::garbage_collect();

		std::cout << *p << std::endl;
	}
}
