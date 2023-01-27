#include "recycled_ptr/basic_ptr.hpp"

namespace gc {

basic_ptr::operator bool() const {
	return ptr_ != nullptr;
}

void *basic_ptr::get() const {
	return ptr_;
}

void basic_ptr::set(void *ptr) {
	ptr_ = ptr;
}

template <class U, class V>
std::basic_ostream<U, V> &operator<<(std::basic_ostream<U, V> &os,
									 const basic_ptr &ptr) {
	os << ptr.ptr_;
	return os;
}

}  // namespace gc
