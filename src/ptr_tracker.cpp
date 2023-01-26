// #include "recycled_ptr/ptr_tracker.hpp"

// #include <vector>

// namespace recycled_ptr {

// ptr_tracker::tracker_ref ptr_tracker::track(basic_ptr* ptr) {
// 	emplace_back(ptr, true);
// 	return std::prev(end());
// }

// void ptr_tracker::untrack(tracker_ref ref) {
// 	auto& [ptr, active] = *ref;
// 	active = false;
// }

// }  // namespace recycled_ptr
