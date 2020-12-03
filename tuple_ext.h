#pragma once
#include <type_traits>
#include <tuple>


namespace tuple_ext{

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

// *********************
// *       head_t      *
// *********************

namespace impl
{
  template<typename T> struct head;

  template<typename T,typename... Ts>
  struct head<std::tuple<T,Ts...>>
  {
    using type = T;
  };
}

template<typename T>
requires ( is_tuple<T> && (std::tuple_size_v<T> != 0) )
using head_t = typename impl::head<T>::type;

// *********************
// *     tail_t      *
// *********************

namespace impl
{
  template<typename T> struct tail;

  template<typename T,typename... Ts>
  struct tail<std::tuple<T,Ts...>>
  {
    using type = std::tuple<Ts...>;
  };
}


template<typename T>
requires is_tuple<T>
using tail_t = typename impl::tail<T>::type;

// *********************
// *    has_type_t     *
// *********************

namespace impl
{
  template<typename T, typename... Ts>
  struct has_type
  {
    static constexpr bool value = (std::is_same<T,Ts>::value || ...);
  };
}

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
namespace impl
{
  template<typename... Ts>
  struct reverse
  {
    using type = std::tuple<>;
  };

  template<typename T,typename... Ts>
  struct reverse<T,Ts...>
  {
    using type = concat_t<typename reverse<Ts...>::type, std::tuple<T>>;
  };
}

template<typename T> struct reverse;

template<typename... Ts>
struct reverse<std::tuple<Ts...>>
{
  using type = typename impl::reverse<Ts...>::type;
};


template<typename T>
requires ( is_tuple<T> )
using reverse_t = typename reverse<T>::type;

// *********************
// *    unique_t     *
// *********************

namespace impl
{
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
        impl::has_type<T,Ts...>::value,
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
    using type = reverse_t<
      typename impl::runique <
        typename impl::reverse<Ts...>::type
      >::type
    >;
  };
}

template<typename T> struct unique;

template<typename... Ts>
struct unique<std::tuple<Ts...>>
{
  using type = typename impl::unique<Ts...>::type;
};

template<typename T>
requires ( is_tuple<T> )
using unique_t = typename impl::unique<T>::type;


// *********************
// *    remove_t     *
// *********************
namespace impl
{
  template<typename ... T1s>
  struct remove
  {
    template<typename... T2s>
    struct from
    {
      using type = concat_t<
        typename std::conditional<
          impl::has_type<T2s,T1s...>::value,
          std::tuple<>,
          std::tuple<T2s>
        >::type...
      >;
    };

  };
}

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
namespace impl
{
  template<typename ... T1s>
  struct inter
  {
    template<typename... T2s>
    struct with
    {
      using type = concat_t<
        typename std::conditional<
          impl::has_type<T1s,T2s...>::value,
          std::tuple<T1s>,
          std::tuple<>
        >::type...
      >;
    };

  };
}

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
// *      zip_t        *
// *********************
namespace impl
{
  template<typename ... T1s>
  struct zip
  {
    template<typename... T2s>
    struct with
    {
      using type = std::tuple<
        std::pair<T1s,T2s>...
      >;
    };
  };
}

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
namespace impl
{
  // is_pair_v / are_pairs_v
  template<typename T>
  struct is_pair : std::false_type {};

  template<typename T1, typename T2>
  struct is_pair<std::pair<T1,T2>> : std::true_type {};

  template<typename T>
  inline constexpr bool is_pair_v = is_pair<T>::value;

  template<typename... Ts>
  inline constexpr bool are_pairs_v = ( is_pair<Ts>::value && ... );

  // fst_t: fst (a,b) = a
  template<typename T> struct fst;

  template<typename T1,typename T2>
  struct fst<std::pair<T1,T2>>
  {
    using type = T1;
  };

  template<typename T>
  using fst_t = typename fst<T>::type;

  // snd_t: snd (a,b) = b
  template<typename T> struct snd;

  template<typename T1,typename T2>
  struct snd<std::pair<T1,T2>>
  {
    using type = T2;
  };

  template<typename T>
  using snd_t = typename snd<T>::type;

  // unzip
  template<typename... Ts>
  struct unzip
  {
    using type = std::pair<
      std::tuple<fst_t<Ts>...>,
      std::tuple<snd_t<Ts>...>
    >;
  };
}

template<typename T> struct unzip;

template<typename... Ts>
struct unzip<std::tuple<Ts...>>
{
  using type = typename impl::unzip<Ts...>::type;
};

template<typename T>
requires ( is_tuple<T> )
using unzip_t = typename unzip<T>::type;


} // namespace tuple_ext
