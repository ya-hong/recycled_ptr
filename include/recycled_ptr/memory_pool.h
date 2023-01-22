#pragma once

#include <utility>

#include "recycled_ptr/types.h"

namespace recycled_ptr {

class memory_pool {
public:
	template <typename Type, typename... Args>
	recycled_block<Type>* construct(Args&&... args);

	bool is_address_in_pool(void* ptr) const;

	static memory_pool& get_instance();

private:
	memory_pool() {}
	static memory_pool* memory_pool_instance;
};

}  // namespace recycled_ptr

#include "recycled_ptr/tpp/memory_pool.tpp"