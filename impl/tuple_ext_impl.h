#pragma once
#include <type_traits>
#include <tuple>

namespace tuple_ext
{

namespace impl
{
  template<typename T>
  struct is_tuple : std::false_type {};

  template<typename... Ts>
  struct is_tuple<std::tuple<Ts...>> : std::true_type {};
}


// *********************
// *     concepts      *
// *********************
template<typename T>
concept is_tuple = impl::is_tuple<T>::value;

template<typename... Ts>
concept are_tuple = ( is_tuple<Ts> && ... );


// *********************
// *     concat_t      *
// *********************
template<typename...Ts>
requires ( are_tuple<Ts...> )
using concat_t = decltype(std::tuple_cat(std::declval<Ts>()...));

namespace impl
{


// *********************
// *        head       *
// *********************
template<typename T> struct head;

template<typename T,typename... Ts>
struct head<std::tuple<T,Ts...>>
{
  using type = T;
};


// *********************
// *       tail        *
// *********************
template<typename T> struct tail;

template<typename T,typename... Ts>
struct tail<std::tuple<T,Ts...>>
{
  using type = std::tuple<Ts...>;
};


// *********************
// *     has_type      *
// *********************
template<typename T, typename Tp> struct has_type;

template<typename T, typename... Ts>
struct has_type<T,std::tuple<Ts...>>
{
  static constexpr bool value = (std::is_same<T,Ts>::value || ...);
};


// *********************
// *     reverse       *
// *********************
template<typename T> struct reverse;

template<typename... Ts>
struct reverse<std::tuple<Ts...>>
{
  using type = std::tuple<>;
};

template<typename T,typename... Ts>
struct reverse<std::tuple<T,Ts...>>
{
  using type = concat_t<typename reverse<std::tuple<Ts...>>::type, std::tuple<T>>;
};


// *********************
// *       unique      *
// *********************
template<typename T> struct runique;

template<typename... Ts>
struct runique<std::tuple<Ts...>>
{
  using type = std::tuple<Ts...>;
};

template<typename T,typename... Ts>
struct runique<std::tuple<T,Ts...>>
{
  using type = concat_t<
    std::conditional_t<
      impl::has_type<T,std::tuple<Ts...>>::value,
      std::tuple<>,
      std::tuple<T>
    >,
    typename runique<std::tuple<Ts...>>::type
  >;
};

template<typename T> struct unique;

template<typename... Ts>
struct unique<std::tuple<Ts...>>
{
  using type = typename reverse<
    typename impl::runique <
      typename impl::reverse<std::tuple<Ts...>>::type
    >::type
  >::type;
};


// *********************
// *     remove        *
// *********************
template<typename Tp> struct remove;

template<typename ... T1s>
struct remove<std::tuple<T1s...>>
{
  template<typename Tp> struct from;

  template<typename... T2s>
  struct from<std::tuple<T2s...>>
  {
    using type = concat_t<
      typename std::conditional<
        impl::has_type<T2s,std::tuple<T1s...>>::value,
        std::tuple<>,
        std::tuple<T2s>
      >::type...
    >;
  };
};


// *********************
// *       inter       *
// *********************
template<typename Tp> struct inter;

template<typename ... T1s>
struct inter<std::tuple<T1s...>>
{
  template<typename Tp> struct with;

  template<typename... T2s>
  struct with<std::tuple<T2s...>>
  {
    using type = concat_t<
      typename std::conditional<
        impl::has_type<T1s,std::tuple<T2s...>>::value,
        std::tuple<T1s>,
        std::tuple<>
      >::type...
    >;
  };
};


// *********************
// *       zip         *
// *********************

template<typename T1> struct zip;

template<typename... T1s>
struct zip<std::tuple<T1s...>>
{
  template<typename T2> struct with;

  template<typename... T2s>
  struct with<std::tuple<T2s...>>
  {
    using type = std::tuple<std::pair<T1s,T2s>... >;
  };
};

// *********************
// *       fst         *
// *********************
template<typename T> struct fst;

template<typename T1,typename T2>
struct fst<std::pair<T1,T2>>
{
  using type = T1;
};


// *********************
// *       snd         *
// *********************
template<typename T> struct snd;

template<typename T1,typename T2>
struct snd<std::pair<T1,T2>>
{
  using type = T2;
};


// *********************
// *      unzip        *
// *********************
template<typename T> struct unzip;

template<typename... Ts>
struct unzip<std::tuple<Ts...>>
{
  using type = std::pair<
    std::tuple<typename fst<Ts>::type...>,
    std::tuple<typename snd<Ts>::type...>
  >;
};

// *********************
// *       map         *
// *********************
template<template<typename T> typename F, typename Tp> struct map;

template<template<typename T> typename F, typename... Ts>
struct map<F,std::tuple<Ts...>>
{
  using type = std::tuple<typename F<Ts>::type...>;
};

// *********************
// *       foldr       *
// *********************
template<template<typename,typename> typename F, typename TY, typename TXs> struct foldr;

// foldr f x [] = x
template<
  template<typename,typename> typename F,
  typename TY,
  typename... TXs
>
struct foldr<F,TY,std::tuple<TXs...>>
{
  using type = TY;
};

// foldr f x (y:ys) = f x foldr f x ys
template<
  template<typename,typename> typename F, // F(X,TY)
  typename TY,
  typename X, typename... TXs
>
struct foldr<F,TY,std::tuple<X,TXs...>>
{
  using type = typename F<
    X,
    typename foldr<F,TY,std::tuple<TXs...>>::type
  >::type;
};

// *********************
// *       foldl       *
// *********************
template<template<typename,typename> typename F, typename TY, typename TXs> struct foldl;

// foldl f x [] = x
template<
  template<typename,typename> typename F,
  typename TY,
  typename... TXs
>
struct foldl<F,TY,std::tuple<TXs...>>
{
  using type = TY;
};

// foldl f x (y:ys) = f x foldl f x ys
template<
  template<typename,typename> typename F, // F(X,TY)
  typename TY,
  typename X, typename... TXs
>
struct foldl<F,TY,std::tuple<X,TXs...>>
{
  using type = typename foldl<
    F,
    typename F<X,TY>::type,
    std::tuple<TXs...>
  >::type;
};

} // namespace impl
} // namespace tuple_ext
