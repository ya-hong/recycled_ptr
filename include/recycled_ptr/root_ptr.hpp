#pragma once

#ifndef FUCKYOU
#define FUCKYOU

#include <utility>
#include <vector>

#include "recycled_ptr/recycled_ptr.hpp"
#include "recycled_ptr/tracked_ptr.hpp"
#include "recycled_ptr/types.hpp"

namespace recycled_ptr {

/// @brief 指向gc root内存块的指针
/// @tparam Type
template <typename Type>
class root_ptr : public recycled_ptr<Type>, tracked_ptr {
	using ptr_tp = recycled_ptr<Type>;

public:
	root_ptr() = default;
	root_ptr(const ptr_tp &);
	root_ptr(ptr_tp &&);
	using recycled_ptr<Type>::operator=;
	~root_ptr();
};

}  // namespace recycled_ptr

#include "recycled_ptr/tpp/root_ptr.tpp"

#endif
