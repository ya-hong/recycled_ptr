#include "recycled_ptr/tracked_ptr.hpp"

#include "recycled_ptr/basic_ptr.hpp"

namespace recycled_ptr {

ptr_tracker tracked_ptr::tracker_;

tracked_ptr::tracked_ptr() {
	track();
}

tracked_ptr::tracked_ptr(const basic_ptr& other) : basic_ptr(other) {
	track();
}

tracked_ptr::tracked_ptr(tracked_ptr&& other) : basic_ptr(std::move(other)) {
	auto& [ptr_ptr, active] = tracker_.at(other.tracker_ref_);
	ptr_ptr = this;
	tracker_ref_ = other.tracker_ref_;
	other.tracker_ref_ = -1;
}

tracked_ptr::~tracked_ptr() {
	untrack();
}

void tracked_ptr::track() {
	tracker_.emplace_back(this, true);
	tracker_ref_ = tracker_.size() - 1;
}

void tracked_ptr::untrack() {
	if (tracker_ref_ == -1) return;
	auto& [ptr_ptr, active] = tracker_.at(tracker_ref_);
	active = false;
}

}  // namespace recycled_ptr
