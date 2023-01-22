namespace recycled_ptr {

template <typename Type>
class recycled_ptr;

template <typename Type>
class recycled_block;

class memory_pool;

template <typename Type>
using block_proxy = recycled_block<Type> *;

template <typename Type>
using block_proxy_ptr = const block_proxy<Type> *;

}  // namespace recycled_ptr