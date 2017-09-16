#ifndef MOONSHINE_HELPERS_H
#define MOONSHINE_HELPERS_H

#include <type_traits>

template<typename E>
constexpr auto ToUnderlyingType(E e) -> typename std::underlying_type<E>::type
{
    return static_cast<typename std::underlying_type<E>::type>(e);
}

#endif //MOONSHINE_HELPERS_H
