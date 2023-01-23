#include "recycled_ptr/memory_pool.h"

namespace recycled_ptr {

memory_pool* memory_pool::memory_pool_instance_(nullptr);

bool memory_pool::is_address_in_pool(void* ptr) const {
	return true;
}

memory_pool& memory_pool::get_instance() {
	if (memory_pool_instance_ == nullptr) {
		memory_pool_instance_ = new memory_pool;
	}
	return *memory_pool_instance_;
}

}  // namespace recycled_ptr