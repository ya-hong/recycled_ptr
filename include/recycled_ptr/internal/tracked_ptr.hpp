#pragma once

#include "recycled_ptr/internal/basic_ptr.hpp"
#include "recycled_ptr/types.hpp"

namespace gc {

class tracked_ptr : virtual public basic_ptr {
	friend class static_mem_tracker;

public:
	tracked_ptr();
	tracked_ptr(const basic_ptr&);

	/// @brief 将被移动指针的trakcer指向自己
	/// @param
	tracked_ptr(tracked_ptr&&);

	tracked_ptr& operator=(const basic_ptr&) = delete;
	tracked_ptr& operator=(basic_ptr&&) = delete;
	virtual ~tracked_ptr();

	void track();
	void untrack();

private:
	static ptr_tracker tracker_;
	size_t tracker_ref_;
};

}  // namespace gc
