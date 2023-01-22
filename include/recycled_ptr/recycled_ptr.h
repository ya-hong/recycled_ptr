#pragma once

#include <iostream>

#include "recycled_ptr/types.h"

namespace recycled_ptr {

template <typename Type>
class recycled_ptr {
public:
	recycled_ptr() : proxy_ptr_(nullptr) {}
	recycled_ptr(const recycled_ptr<Type> &ptr);
	~recycled_ptr();

	void swap(recycled_ptr<Type> &ptr);
	Type &operator*() const;
	Type *operator->() const;
	explicit operator bool() const noexcept;

private:
	block_proxy_ptr<Type> proxy_ptr_;

	template <typename Type_, typename... Args>
	friend recycled_ptr<Type_> make_object(Args &&...args);
};

template <class T, class U>
bool operator==(const recycled_ptr<T> &lhs, const recycled_ptr<U> &rhs) noexcept;

template <class T, class U>
bool operator!=(const recycled_ptr<T> &lhs, const recycled_ptr<U> &rhs) noexcept;

template <class T, class U>
bool operator<(const recycled_ptr<T> &lhs, const recycled_ptr<U> &rhs) noexcept;

template <class T, class U>
bool operator>(const recycled_ptr<T> &lhs, const recycled_ptr<U> &rhs) noexcept;

template <class T, class U>
bool operator<=(const recycled_ptr<T> &lhs, const recycled_ptr<U> &rhs) noexcept;

template <class T, class U>
bool operator>=(const recycled_ptr<T> &lhs, const recycled_ptr<U> &rhs) noexcept;

template <class T>
bool operator==(const recycled_ptr<T> &lhs, std::nullptr_t) noexcept;

template <class T>
bool operator==(std::nullptr_t, const recycled_ptr<T> &rhs) noexcept;

template <class T>
bool operator!=(const recycled_ptr<T> &lhs, std::nullptr_t) noexcept;

template <class T>
bool operator!=(std::nullptr_t, const recycled_ptr<T> &rhs) noexcept;

template <class T>
bool operator<(const recycled_ptr<T> &lhs, std::nullptr_t) noexcept;

template <class T>
bool operator<(std::nullptr_t, const recycled_ptr<T> &rhs) noexcept;

template <class T>
bool operator>(const recycled_ptr<T> &lhs, std::nullptr_t) noexcept;

template <class T>
bool operator>(std::nullptr_t, const recycled_ptr<T> &rhs) noexcept;

template <class T>
bool operator<=(const recycled_ptr<T> &lhs, std::nullptr_t) noexcept;

template <class T>
bool operator<=(std::nullptr_t, const recycled_ptr<T> &rhs) noexcept;

template <class T>
bool operator>=(const recycled_ptr<T> &lhs, std::nullptr_t) noexcept;

template <class T>
bool operator>=(std::nullptr_t, const recycled_ptr<T> &rhs) noexcept;

template <class T, class U, class V>
std::basic_ostream<U, V> &operator<<(std::basic_ostream<U, V> &os, const recycled_ptr<T> &ptr);

template <typename Type>
void swap(recycled_ptr<Type> &lhs, recycled_ptr<Type> &rhs);

template <typename Type, typename... Args>
recycled_ptr<Type> make_object(Args &&...args);

}  // namespace recycled_ptr

#include "recycled_ptr/tpp/recycled_ptr.tpp"
