// #include "recycled_ptr/ptr_tracker.hpp"

// #include <vector>

// namespace gc {

// ptr_tracker::tracker_ref ptr_tracker::track(basic_ptr* ptr) {
// 	emplace_back(ptr, true);
// 	return std::prev(end());
// }

// void ptr_tracker::untrack(tracker_ref ref) {
// 	auto& [ptr, active] = *ref;
// 	active = false;
// }

// }  // namespace gc
