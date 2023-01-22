#pragma once

#include <utility>

#include "recycled_ptr/types.h"

namespace recycled_ptr {

template <typename Type>
class recycled_block {
private:
	template <typename... Args>
	recycled_block(Args &&...args);

	Type &value();
	const Type &value() const;

	bool is_gc_root() const;

	void outside_reference_increase();
	void outside_reference_decrease();

	Type value_;
	long outside_reference_count_;
	block_proxy_ptr<Type> proxy_ptr_;

	friend class recycled_ptr<Type>;
	friend class memory_pool;

	template <typename Type_, typename... Args>
	friend recycled_ptr<Type_> make_object(Args &&...args);
};

}  // namespace recycled_ptr

#include "recycled_ptr/tpp/recycled_block.tpp"