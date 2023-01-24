#include "recycled_ptr/memory_pool.hpp"
#include "recycled_ptr/recycled_block.hpp"
#include "recycled_ptr/recycled_ptr.hpp"

namespace recycled_ptr {

template <typename Type>
template <typename... Args>
recycled_block<Type>::recycled_block(Args&&... args) : value_(std::forward<Args>(args)...), outside_reference_count_(0) {
	proxy_ptr_ = new block_proxy<Type>(this);
}

template <typename Type>
Type& recycled_block<Type>::value() {
	return value_;
}

template <typename Type>
const Type& recycled_block<Type>::value() const {
	return value_;
}

template <typename Type>
bool recycled_block<Type>::is_gc_root() const {
	return outside_reference_count_ > 0;
}

template <typename Type>
void recycled_block<Type>::outside_reference_increase() {
	outside_reference_count_++;
}

template <typename Type>
void recycled_block<Type>::outside_reference_decrease() {
	outside_reference_count_--;
}

}  // namespace recycled_ptr