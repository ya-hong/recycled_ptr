#include <unordered_map>

#include "recycled_ptr/basic_ptr.hpp"
#include "recycled_ptr/ptr_tracker.hpp"
#include "recycled_ptr/root_ptr.hpp"
#include "recycled_ptr/tracked_allocator_traits.hpp"

namespace recycled_ptr {

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

		for (size_t offset = 0, step = sizeof(void*); offset + step <= size;
			 offset += step) {
			void** next = (void**)((uintptr_t)ptr + offset);
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

}  // namespace recycled_ptr
