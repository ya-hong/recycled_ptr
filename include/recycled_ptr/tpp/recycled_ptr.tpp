#include "recycled_ptr/recycled_ptr.hpp"
#include "recycled_ptr/tracked_allocator_traits.hpp"

namespace recycled_ptr {

template <typename Type, typename... Args>
recycled_ptr<Type> make_object(Args&&... args) {
	static std::allocator<Type> alloc;

	Type* ptr = tracked_allocator_traits<Type>::allocate(alloc, 1);
	tracked_allocator_traits<Type>::construct(alloc, ptr,
											  std::forward<Args>(args)...);

	recycled_ptr<Type> result;
	result.set((void*)ptr);

	return result;
}

template <typename Type>
recycled_ptr<Type>& recycled_ptr<Type>::operator=(const ptr_tp& other) {
	basic_ptr::operator=(other);
	return *this;
}

template <typename Type>
recycled_ptr<Type>& recycled_ptr<Type>::operator=(ptr_tp&& other) {
	basic_ptr::operator=(std::move(other));
	return *this;
}

template <typename Type>
recycled_ptr<Type>::~recycled_ptr() {}

template <typename Type>
void recycled_ptr<Type>::swap(ptr_tp& other) {
	auto p = basic_ptr::get();
	set(other.basic_ptr::get());
	other.set(p);
}

template <typename Type>
Type& recycled_ptr<Type>::operator*() const {
	return *get();
}

template <typename Type>
Type* recycled_ptr<Type>::operator->() const {
	return get();
}

template <typename Type>
Type* recycled_ptr<Type>::get() const {
	return (Type*)basic_ptr::get();
}

template <typename Type>
void swap(recycled_ptr<Type>& lhs, recycled_ptr<Type>& rhs) {
	lhs.swap(rhs);
}

}  // namespace recycled_ptr
