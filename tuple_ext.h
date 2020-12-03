#pragma once
#include "impl/tuple_ext_impl.h"


namespace tuple_ext{

// *********************
// *       head_t      *
// *********************

template<typename T>
requires ( is_tuple<T> && (std::tuple_size_v<T> != 0) )
using head_t = typename impl::head<T>::type;


// *********************
// *     tail_t      *
// *********************
template<typename T>
requires is_tuple<T>
using tail_t = typename impl::tail<T>::type;


// *********************
// *    has_type_t     *
// *********************
template<typename T,typename Tp> struct has_type;

template<typename T,typename... Ts>
struct has_type<T,std::tuple<Ts...>>
{
  static constexpr bool value = impl::has_type<T,Ts...>::value;
};

template<typename T,typename Tp>
requires ( is_tuple<Tp> )
inline constexpr bool has_type_v = has_type<T, Tp>::value;


// *********************
// *    reverse_t      *
// *********************
template<typename T>
requires ( is_tuple<T> )
using reverse_t = typename impl::reverse<T>::type;


// *********************
// *    unique_t     *
// *********************
template<typename T>
requires ( is_tuple<T> )
using unique_t = typename impl::unique<T>::type;


// *********************
// *    remove_t     *
// *********************
template<typename T1,typename T2> struct remove;

template<typename ...T1s,typename... T2s>
struct remove<std::tuple<T1s...>,std::tuple<T2s...>>
{
  using type = typename impl::remove<T1s...>::from<T2s...>::type;
};

template<typename T1,typename T2>
requires ( is_tuple<T1> && is_tuple<T2> )
using remove_t = typename remove<T1,T2>::type;


// *********************
// *      inter_t      *
// *********************
template<typename T1,typename T2> struct inter;

template<typename... T1s,typename... T2s>
struct inter<std::tuple<T1s...>,std::tuple<T2s...>>
{
  using type = unique_t<typename impl::inter<T1s...>::with<T2s...>::type>;
};

template<typename T1,typename T2>
requires ( is_tuple<T1> && is_tuple<T2> )
using inter_t = typename inter<T1,T2>::type;


// *********************
// *  fst_t and snd_t  *
// *********************
template<typename T>
using fst_t = typename impl::fst<T>::type;

template<typename T>
using snd_t = typename impl::snd<T>::type;


// *********************
// *      zip_t        *
// *********************
template<typename T1,typename T2> struct zip;

template<typename... T1s,typename... T2s>
struct zip<std::tuple<T1s...>,std::tuple<T2s...>>
{
  using type = typename impl::zip<T1s...>::with<T2s...>::type;
};

template<typename T1,typename T2>
requires ( is_tuple<T1> && is_tuple<T2> )
using zip_t = typename zip<T1,T2>::type;


// *********************
// *      unzip_t      *
// *********************
template<typename T>
requires ( is_tuple<T> )
using unzip_t = typename impl::unzip<T>::type;

} // namespace tuple_ext
