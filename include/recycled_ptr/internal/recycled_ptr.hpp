#pragma once

#include "recycled_ptr/basic_ptr.hpp"
#include "recycled_ptr/types.hpp"

namespace gc {

/// @brief 指向非gc root内存块的指针
/// @tparam Type
template <typename Type>
class recycled_ptr : virtual public basic_ptr {
	using ptr_tp = recycled_ptr<Type>;

	template <typename Tp, typename... Args>
	friend recycled_ptr<Tp> make_object(Args &&...args);

public:
	recycled_ptr() = default;

	/// @brief 只允许相同Type之间构造
	/// @param other
	recycled_ptr(const ptr_tp &other) = default;
	recycled_ptr(ptr_tp &&other) = default;

	/// @brief 只允许相同Type之间使用等号
	/// @param other
	/// @return
	ptr_tp &operator=(const ptr_tp &other);
	ptr_tp &operator=(ptr_tp &&other);

	~recycled_ptr();

	void swap(ptr_tp &other);

	Type &operator*() const;
	Type *operator->() const;

	/// @brief 返回维护的指针并转变为对应的类型。覆盖了基类的get()
	/// @return Type*
	Type *get() const;
};

template <typename Type>
void swap(recycled_ptr<Type> &lhs, recycled_ptr<Type> &rhs);

}  // namespace gc

#include "recycled_ptr/tpp/recycled_ptr.tpp"
