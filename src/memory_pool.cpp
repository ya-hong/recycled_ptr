#include "recycled_ptr/memory_pool.h"

namespace recycled_ptr {

memory_pool* memory_pool::memory_pool_instance(nullptr);

bool memory_pool::is_address_in_pool(void* ptr) const {
	return true;
}

memory_pool& memory_pool::get_instance() {
	if (memory_pool_instance == nullptr) {
		memory_pool_instance = new memory_pool;
	}
	return *memory_pool_instance;
}

}  // namespace recycled_ptr