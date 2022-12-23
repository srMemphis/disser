#pragma once

// Bit flags from enums
#define MAKE_BIT_FLAGS(Enum)								\
	Enum operator| (const Enum lhs, const Enum rhs) {		\
		return static_cast<Enum>(							\
		static_cast<std::underlying_type_t<Enum>>(lhs) |	\
		static_cast<std::underlying_type_t<Enum>>(rhs));	\
	}														\
	Enum operator& (const Enum lhs, const Enum rhs) {		\
		return static_cast<Enum>(							\
		static_cast<std::underlying_type_t<Enum>>(lhs) &	\
		static_cast<std::underlying_type_t<Enum>>(rhs));	\
	}														\
	Enum operator^ (const Enum lhs, const Enum rhs) {		\
		return static_cast<Enum>(							\
		static_cast<std::underlying_type_t<Enum>>(lhs) ^	\
		static_cast<std::underlying_type_t<Enum>>(rhs));	\
	}														\
	Enum& operator|= (Enum& lhs, const Enum& rhs) {			\
		return lhs = lhs | rhs;								\
	}														\
	Enum& operator&= (Enum& lhs, const Enum& rhs) {			\
		return lhs = lhs & rhs;								\
	}														\
	Enum& operator^= (Enum& lhs, const Enum& rhs) {			\
		return lhs = lhs ^ rhs;								\
	}														\
	Enum operator~ (const Enum rhs) {						\
		return static_cast<Enum>(							\
		~static_cast<std::underlying_type_t<Enum>>(rhs));	\
	}														\
