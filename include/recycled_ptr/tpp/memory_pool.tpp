#include "recycled_ptr/memory_pool.hpp"
#include "recycled_ptr/recycled_block.hpp"

namespace recycled_ptr {

template <typename Type, typename... Args>
block_proxy<Type> memory_pool::construct(Args&&... args) {
	using Block = recycled_block<Type>;
	using Proxy = block_proxy<Type>;

	void* start = memory_pool_ptr_ + reserved_memory_;
	size_t position = (start + POINTER_SIZE + sizeof(Block) - 1) / sizeof(Block) * sizeof(Block);
	void* block_start = position;

	Block* ptr = new(block_start) Block(std::forward<Args>(args)...);

	

	return *(ptr->proxy_ptr_);
}

}  // namespace recycled_ptr