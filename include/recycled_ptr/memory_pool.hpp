#pragma once

#include <stddef.h>

#include <utility>

#include "recycled_ptr/types.h"

#define POINTER_SIZE (sizeof(void*))
#define POOL_ALIGNAS 4

namespace recycled_ptr {

class memory_pool {
public:
	template <typename Type, typename... Args>
	recycled_block<Type>* new_object(Args&&... args);

	bool is_address_in_pool(void* ptr) const;

	static memory_pool& get_instance();

private:
	memory_pool()
		: memory_pool_ptr_(nullptr),
		  memory_pool_size_(0),
		  used_memory_(0),
		  reserved_memory_(0) {}

	template <typename Type, typename... Args>
	recycled_block<Type>* construct(Args&&... args);

	void* reserve(size_t size);

	void* memory_pool_ptr_;
	size_t memory_pool_size_;
	size_t used_memory_;
	size_t reserved_memory_;
	static memory_pool* memory_pool_instance_;
};

}  // namespace recycled_ptr

#include "recycled_ptr/tpp/memory_pool.tpp"