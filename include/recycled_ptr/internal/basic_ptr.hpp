#pragma once

#include "recycled_ptr/types.hpp"

namespace gc {

/// @brief 不带类型信息的基类
class basic_ptr {
	template <class U, class V>
	friend std::basic_ostream<U, V> &operator<<(std::basic_ostream<U, V> &os,
												const basic_ptr &ptr);

public:
	explicit operator bool() const;

	/// @brief 返回维护的指针。会被派生类覆盖
	/// @return void*
	void *get() const;

protected:
	basic_ptr() : ptr_(nullptr) {}
	basic_ptr(const basic_ptr &) = default;
	basic_ptr(basic_ptr &&) = default;
	basic_ptr &operator=(const basic_ptr &) = default;
	basic_ptr &operator=(basic_ptr &&) = default;
	~basic_ptr() = default;

	void set(void *ptr);

private:
	void *ptr_;
};

bool operator==(const basic_ptr &lhs, const basic_ptr &rhs);

bool operator!=(const basic_ptr &lhs, const basic_ptr &rhs);

bool operator<(const basic_ptr &lhs, const basic_ptr &rhs);

bool operator>(const basic_ptr &lhs, const basic_ptr &rhs);

bool operator<=(const basic_ptr &lhs, const basic_ptr &rhs);

bool operator>=(const basic_ptr &lhs, const basic_ptr &rhs);

bool operator==(const basic_ptr &lhs, std::nullptr_t);

bool operator==(std::nullptr_t, const basic_ptr &rhs);

bool operator!=(const basic_ptr &lhs, std::nullptr_t);

bool operator!=(std::nullptr_t, const basic_ptr &rhs);

bool operator<(const basic_ptr &lhs, std::nullptr_t);

bool operator<(std::nullptr_t, const basic_ptr &rhs);

bool operator>(const basic_ptr &lhs, std::nullptr_t);

bool operator>(std::nullptr_t, const basic_ptr &rhs);

bool operator<=(const basic_ptr &lhs, std::nullptr_t);

bool operator<=(std::nullptr_t, const basic_ptr &rhs);

bool operator>=(const basic_ptr &lhs, std::nullptr_t);

bool operator>=(std::nullptr_t, const basic_ptr &rhs);

}  // namespace gc
