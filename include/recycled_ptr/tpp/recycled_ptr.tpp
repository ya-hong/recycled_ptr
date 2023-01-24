#include "recycled_ptr/memory_pool.hpp"
#include "recycled_ptr/recycled_block.hpp"
#include "recycled_ptr/recycled_ptr.hpp"

namespace recycled_ptr {

template <typename Type>
recycled_ptr<Type>::recycled_ptr(const recycled_ptr<Type> &ptr) {
	auto proxy = *ptr.proxy_ptr_;

	if (memory_pool::get_instance().is_address_in_pool(this)) {
		proxy->outside_reference_increase();
		(**proxy_ptr_).outside_reference_decrease();
	}

	proxy_ptr_ = &proxy;
}

template <typename Type>
recycled_ptr<Type>::~recycled_ptr() {
	(**proxy_ptr_).outside_reference_decrease();
}

template <typename Type>
void recycled_ptr<Type>::swap(recycled_ptr<Type> &ptr) {
	swap(proxy_ptr_, ptr.proxy_ptr_);
	int d = (int)memory_pool::get_instance().is_address_in_pool(this) - (int)memory_pool::get_instance().is_address_in_pool(&ptr);
	if (d == 1) {
		**proxy_ptr_.out_side_reference_increase();
		**(ptr.proxy_ptr_).out_side_reference_decrease();
	}
	if (d == -1) {
		**proxy_ptr_.out_side_reference_decrease();
		**(ptr.proxy_ptr_).out_side_reference_increase();
	}
}

template <typename Type>
Type &recycled_ptr<Type>::operator*() const {
	recycled_block<Type> &blk = **proxy_ptr_;
	return blk.value();
}

template <typename Type>
Type *recycled_ptr<Type>::operator->() const {
	recycled_block<Type> &blk = **proxy_ptr_;
	return &blk.value();
}

template <typename Type>
recycled_ptr<Type>::operator bool() const noexcept {
	return proxy_ptr_ != nullptr;
}

template <typename Type, typename... Args>
recycled_ptr<Type> make_object(Args &&...args) {
	recycled_ptr<Type> ptr;
	block_proxy<Type> proxy = memory_pool::get_instance().construct<Type>(std::forward<Args>(args)...);
	proxy->outside_reference_increase();
	ptr.proxy_ptr_ = &proxy;
	return ptr;
}

}  // namespace recycled_ptr