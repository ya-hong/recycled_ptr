#include "recycled_ptr/memory_pool.h"

namespace recycled_ptr {

template <typename Type, typename... Args>
block_proxy<Type> memory_pool::construct(Args&&... args) {
	auto p = new recycled_block<Type>(std::forward<Args>(args)...);
	return *(p->proxy_ptr_);
}

}  // namespace recycled_ptr