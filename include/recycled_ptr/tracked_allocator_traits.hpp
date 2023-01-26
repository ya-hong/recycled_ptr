#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "recycled_ptr/types.hpp"

namespace recycled_ptr {

class static_mem_tracker {
public:
	static void garbage_collect();

protected:
	static mem_tracker tracker_;
};

template <typename Type>
class tracked_allocator_traits
	: public std::allocator_traits<std::allocator<Type>>,
	  static_mem_tracker {
	using base_class = std::allocator_traits<std::allocator<Type>>;

public:
	/// @brief 构造并追踪内存
	/// @tparam T
	/// @tparam ...Args
	/// @param alloc 需要在内存被回收前保持可用
	/// @param p
	/// @param ...args
	template <class T, class... Args>
	static void construct(std::allocator<Type>& alloc, T* p, Args&&... args);
};

}  // namespace recycled_ptr

#include "recycled_ptr/tpp/tracked_allocator_traits.tpp"
