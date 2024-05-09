#ifndef LIST_H
#define LIST_H

#include <type_traits>

template<typename... Ts>
struct typelist {};

template <typename T, typename TypeListTypes>
struct contains
{};

template <typename T, typename... Ts>
struct contains<T, typelist<Ts...>>
{
	static constexpr bool value = (std::is_same_v<T, Ts> || ...);
};

template <typename T, typename... Ts>
constexpr bool contains_v = contains<T, Ts...>::value;

#endif // !LIST_H