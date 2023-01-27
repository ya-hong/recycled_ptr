#include <vector>

#include "recycled_ptr/root_ptr.hpp"
// #include "recycled_ptr/ptr_tracker.hpp"

namespace gc {

template <typename Type>
root_ptr<Type>::root_ptr(const ptr_tp& other)
	: basic_ptr(other), recycled_ptr<Type>(other), tracked_ptr(other) {}

template <typename Type>
root_ptr<Type>::root_ptr(ptr_tp&& other)
	: basic_ptr(std::move(other)),
	  recycled_ptr<Type>(std::move(other)),
	  tracked_ptr(std::move(other)) {}

template <typename Type>
root_ptr<Type>::~root_ptr() {}

}  // namespace gc
