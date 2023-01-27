#include <unordered_map>

#include "recycled_ptr/basic_ptr.hpp"
#include "recycled_ptr/ptr_tracker.hpp"
#include "recycled_ptr/root_ptr.hpp"
#include "recycled_ptr/tracked_allocator_traits.hpp"

namespace gc {

mem_tracker static_mem_tracker::tracker_;

void static_mem_tracker::garbage_collect() {
	using map_tp = std::unordered_map<void*, std::pair<size_t, collect_fn>>;

	ptr_tracker& p_tracker = tracked_ptr::tracker_;
	mem_tracker& m_tracker = static_mem_tracker::tracker_;

	map_tp mem_map;

	for (auto [ptr, size, fn] : m_tracker) {
		mem_map.insert({ptr, {size, fn}});
	}

	ptr_tracker p_tracker_old;
	p_tracker_old.reserve(p_tracker.size());
	p_tracker_old.swap(p_tracker);

	mem_tracker m_tracker_new;
	m_tracker_new.reserve(m_tracker.size());

	std::function<void(map_tp::iterator)> find_mem_recursive =
		[&m_tracker_new, &mem_map,
		 &find_mem_recursive](map_tp::iterator it) -> void {
		void* ptr = it->first;
		auto [size, fn] = it->second;

		// 处理已找到的active memory
		mem_map.erase(it);
		m_tracker_new.emplace_back(ptr, size, fn);

		//使用alignof(basic_ptr)可以避免#pragma(n)改变类的内存对齐
		//此外alignas改变对齐应该不会导致错误
		//暂时没想到其他改变内存对齐方式的方法
		size_t step = alignof(basic_ptr);
		intptr_t start_position = ((intptr_t)ptr + step - 1) / step * step;
		intptr_t end_position = (intptr_t)ptr + size;
		for (size_t position = start_position;
			 position + sizeof(void*) <= end_position; position += step) {
			void** next = (void**)position;
			void* next_address = *next;
			auto it = mem_map.find(next_address);
			if (it != mem_map.end()) {
				find_mem_recursive(it);
			}
		}
	};

	for (auto& [ptr_ptr, active] : p_tracker_old) {
		if (!active) continue;
		ptr_ptr->track();
		void* mem_address = ptr_ptr->get();
		auto it = mem_map.find(mem_address);
		if (it != mem_map.end()) {
			find_mem_recursive(it);
		}
	}

	m_tracker.swap(m_tracker_new);

	for (auto& [ptr, pair] : mem_map) {
		auto& [size, fn] = pair;
		fn(ptr);
	}
}

}  // namespace gc
