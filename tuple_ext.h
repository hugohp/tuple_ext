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
template<typename T,typename Tp>
requires ( is_tuple<Tp> )
inline constexpr bool has_type_v = impl::has_type<T, Tp>::value;


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
template<typename T1,typename T2>
requires ( is_tuple<T1> && is_tuple<T2> )
using remove_t = typename impl::remove<T1>::from<T2>::type;


// *********************
// *      inter_t      *
// *********************
template<typename T1,typename T2>
requires ( is_tuple<T1> && is_tuple<T2> )
using inter_t = typename impl::inter<T1>::with<T2>::type;


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
template<typename T1,typename T2>
requires ( is_tuple<T1> && is_tuple<T2> )
using zip_t = typename impl::zip<T1>::with<T2>::type;


// *********************
// *      unzip_t      *
// *********************
template<typename T>
requires ( is_tuple<T> )
using unzip_t = typename impl::unzip<T>::type;


// *********************
// *     filter_t      *
// *********************
template<template<typename T> typename F, typename Tp>
requires ( is_tuple<Tp> )
using filter_t = typename impl::filter<F,Tp>::type;


// *********************
// *      map_t        *
// *********************
template<template<typename T> typename F, typename Tp>
requires ( is_tuple<Tp> )
using map_t = typename impl::map<F,Tp>::type;


// *********************
// *     foldr_t       *
// *********************
template<
  template<typename,typename> typename F, // F(TX,TY)
  typename TY,
  typename TXs
>
requires ( is_tuple<TXs> )
using foldr_t = typename impl::foldr<F,TY,TXs>::type;


// *********************
// *     foldl_t       *
// *********************
template<
  template<typename,typename> typename F, // F(TX,TY)
  typename TY,
  typename TXs
>
requires ( is_tuple<TXs> )
using foldl_t = typename impl::foldl<F,TY,TXs>::type;

} // namespace tuple_ext
