#include <chrono>
#include <cstring>
#include <iostream>
#include <memory>

#include "recycled_ptr.hpp"

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

int node_counts = 10000;

struct snode {
	int A[100000];
	std::vector<std::shared_ptr<snode>> v;
	snode() {
		memset(A, -1, sizeof(A));
		for (int i = 0; i < 10 && node_counts; i++, node_counts--) {
			v.push_back(std::shared_ptr<snode>());
		}
		for (auto &p : v) {
			p = std::make_shared<snode>();
		}
	}
};

struct rnode {
	int A[100000];
	gc::recycled_ptr<rnode> v[10];
	int count;
	inline static gc::recycled_ptr<rnode> pp = gc::recycled_ptr<rnode>();
	rnode() {
		memset(A, -1, sizeof(A));
		for (int i = 0; i < 10 && node_counts; i++, node_counts--) {
			v[i] = gc::recycled_ptr<rnode>();
			count = i;
		}
		for (int i = 0; i < count; ++i) {
			auto &p = v[i];
			p = gc::make_object<rnode>();
			pp = p;
		}
	}
};

int main() {
	{
		timer t;
		node_counts = 10000;
		std::shared_ptr<snode> p = std::make_shared<snode>();
	}
	{
		timer t;
		node_counts = 10000;
		gc::root_ptr<rnode> p = gc::make_object<rnode>();
		gc::static_mem_tracker::garbage_collect();
		std::cout << rnode::pp->A[0] << std::endl;
		std::cout << p->A[0] << std::endl;
	}
}
