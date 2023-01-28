#include <chrono>
#include <iostream>
#include <memory>

#include "recycled_ptr/recycled_ptr.hpp"

struct timer {
	timer() {
		t_ = std::chrono::high_resolution_clock::now();
	}
	~timer() {
		auto diff = std::chrono::high_resolution_clock::now() - t_;
		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(diff)
							 .count() /
						 1000.0
				  << std::endl;
	}

	std::chrono::time_point<std::chrono::system_clock> t_;
};

struct snode {
	int A[100000];
	std::shared_ptr<snode> ptr;
};

struct rnode {
	int A[100000];
	gc::recycled_ptr<rnode> ptr;
};

int main() {
	{
		timer t;
		for (int i = 0; i < 10000; i++) {
			gc::root_ptr<rnode> a, b;
			a = gc::make_object<rnode>();
			b = gc::make_object<rnode>();
			a->ptr = b;
			b->ptr = a;
			if (i % 1000 == 0) gc::static_mem_tracker::garbage_collect();
		}
	}
	{
		timer t;
		for (int i = 0; i < 10000; i++) {
			std::shared_ptr<snode> a, b;
			a = std::make_shared<snode>();
			b = std::make_shared<snode>();
			a->ptr = b;
			b->ptr = a;
		}
	}
}
