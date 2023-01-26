#pragma once
#include <functional>
#include <memory>
#include <tuple>
#include <vector>

namespace recycled_ptr {

class basic_ptr;

class tracked_ptr;

template <typename Type>
class recycled_ptr;

template <typename Type>
class root_ptr;

template <typename Type>
class tracked_allocator;

using collect_fn = std::function<void(void*)>;

// class ptr_tracker;
using ptr_tracker = std::vector<std::pair<tracked_ptr*, bool>>;
using mem_tracker = std::vector<std::tuple<void*, size_t, collect_fn>>;

// using tracker_ref = ptr_tracker::iterator;

template <class Type>
using allocator = std::allocator_traits<std::allocator<Type>>;

template <class Type>
class tracked_allocator_traits;

class static_ptr_tracker;
class static_mem_tracker;

}  // namespace recycled_ptr
