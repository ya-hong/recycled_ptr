#include "recycled_ptr/tracked_allocator_traits.hpp"

namespace recycled_ptr {

template <typename Type>
template <class T, class... Args>
void tracked_allocator_traits<Type>::construct(std::allocator<Type>& alloc,
											   T* p, Args&&... args) {
	base_class::construct(alloc, p, std::forward<Args>(args)...);

	// 需要alloc在内存回收前保持可用
	collect_fn fn = [&alloc](void* ptr) {
		// std::allocator<Type> alloc;
		tracked_allocator_traits<Type>::destroy(alloc, (Type*)ptr);
		tracked_allocator_traits<Type>::deallocate(alloc, (Type*)ptr, 1);
	};

	tracker_.emplace_back(p, sizeof(Type), fn);
}

}  // namespace recycled_ptr
