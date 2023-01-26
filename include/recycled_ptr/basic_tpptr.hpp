// #pragma once

// #include "recycled_ptr/basic_ptr.hpp"
// #include "recycled_ptr/types.hpp"

// namespace recycled_ptr {

// /// @brief
// /// recycled_ptr和root_ptr的基类(带类型信息)。派生类中只有构造析构函数不同
// /// @tparam Type
// template <typename Type>
// class basic_tpptr : public basic_ptr {
// 	using ptr_tp = basic_tpptr<Type>;

// public:
// 	basic_tpptr() = default;

// 	/// @brief 只允许相同Type之间构造
// 	/// @param other
// 	basic_tpptr(const ptr_tp &other) = default;
// 	basic_tpptr(ptr_tp &&other) = default;

// 	/// @brief 只允许相同Type之间使用等号
// 	/// @param other
// 	/// @return
// 	basic_tpptr &operator=(const ptr_tp &other);
// 	basic_tpptr &operator=(ptr_tp &&other);

// 	virtual ~basic_ptr() = 0;

// 	void swap(ptr_tp &other);

// 	/// @brief 隐藏了基类basic_ptr中的operator=，避免不同类型的等号直接相等
// 	/// @param other
// 	/// @return
// 	ptr_tp &operator=(const ptr_tp &other);

// 	Type &operator*() const;
// 	Type *operator->() const;

// 	/// @brief 返回维护的指针。覆盖了基类的get()
// 	/// @return Type*
// 	Type *get() const;
// };

// template <typename Type>
// void swap(basic_tpptr<Type> &lhs, basic_tpptr<Type> &rhs);

// }  // namespace recycled_ptr

// #include "recycled_ptr/tpp/basic_tpptr.tpp"
