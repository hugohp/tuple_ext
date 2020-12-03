#pragma once
#include <type_traits>
#include <tuple>


namespace tuple_ext{

namespace impl
{
  template<typename T>
  struct false_type : std::false_type {};
}

// *********************
// *     concat_t      *
// *********************

template<typename...Ts>
using concat_t = decltype(std::tuple_cat(std::declval<Ts>()...));

// *********************
// *       head_t      *
// *********************

namespace impl
{
  template<typename... Ts> struct head {};
  
  template<typename T,typename... Ts>
  struct head<T,Ts...>
  {
    using type = T;
  };
} // namespace impl

template<typename Tp> struct head;

template<typename T>
struct head
{
  static_assert (impl::false_type<T>::value,"tuple_functions: head only takes tuple as template parameter");
};

template<typename... Ts>
struct head<std::tuple<Ts...>>
{
  using type = typename impl::head<Ts...>::type;
};

template<typename Tp> 
using head_t = typename head<Tp>::type;

// *********************
// *     tail_t      *
// *********************

namespace impl
{
  template<typename... Ts>
  struct tail
  {
    using type = std::tuple<>;
  };
  
  template<typename T,typename... Ts>
  struct tail<T,Ts...>
  {
    using type = std::tuple<Ts...>;
  };
} // namespace impl

template<typename Tp> struct tail;

template<typename T>
struct tail
{
  static_assert (impl::false_type<T>::value,"tuple_ext: tail only takes tuple as template parameter");
};

template<typename... Ts>
struct tail<std::tuple<Ts...>>
{
  using type = typename impl::tail<Ts...>::type;
};

template<typename Tp> 
using tail_t = typename tail<Tp>::type;

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
} // namespace impl

template<typename T,typename Tp> struct has_type;

template<typename T, typename Tp>
struct has_type
{
  static_assert (impl::false_type<T>::value,"tuple_ext: has_type only takes tuple as second template parameter");
};

template<typename T,typename... Ts>
struct has_type<T,std::tuple<Ts...>>
{
  static constexpr bool value = impl::has_type<T,Ts...>::value;
};

template<typename T,typename Tp>
inline constexpr bool has_type_v = has_type<T, Tp>::value;

// *********************
// *    reverse_t      *
// *********************
namespace impl
{
  template<typename... Ts>
  struct reverse{
    using type = std::tuple<>;
  };
  
  template<typename T,typename... Ts>
  struct reverse<T,Ts...> : reverse<Ts...>
  {
    using type = concat_t<typename reverse<Ts...>::type, std::tuple<T>>;
  };
}
  
template<typename Tp> struct reverse;

template<typename T>
struct reverse
{
  static_assert (impl::false_type<T>::value,"tuple_ext: reverse only takes tuple as template parameter");
};
  
template<typename... Ts>
struct reverse<std::tuple<Ts...>>
{
  using type = typename impl::reverse<Ts...>::type;
};


template<typename Tp> 
using reverse_t = typename reverse<Tp>::type;

// *********************
// *    distinct_t     *
// *********************

namespace impl
{
  // Distinct items of a list in the order of the last occurence.
  template<typename ...Ts>
  struct last_distinct {
    using type = std::tuple<Ts...>;
  };
  
  template<typename T,typename... Ts>
  struct last_distinct<T,Ts...>{
 
    using type = 
     typename std::conditional_t<
       has_type<T,Ts...>::value,
       typename last_distinct<Ts...>::type,
       concat_t<std::tuple<T>,typename last_distinct<Ts...>::type> 
     >;
  };

  template<typename Tp> struct last_distinct_tp;

  template<typename... Ts>
  struct last_distinct_tp<std::tuple<Ts...>>{
    using type = typename last_distinct<Ts...>::type;
  };


  template<typename... Ts>
  struct distinct{
    using type = reverse_t 
        <
          typename impl::last_distinct_tp <
            typename impl::reverse<Ts...>::type
          >::type
        >;
  };
  
}

template<typename Tp> struct distinct;

template<typename T>
struct distinct
{
  static_assert (impl::false_type<T>::value,"tuple_ext: distinct only takes tuple as template parameter");
};

template<typename ...Ts>
struct distinct<std::tuple<Ts...>>
{
  using type = typename impl::distinct<Ts...>::type;
};
template<typename Tp> 
using distinct_t = typename distinct<Tp>::type;


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
          has_type<T2s,T1s...>::value,
          std::tuple<>,
          std::tuple<T2s>
        >::type...
      >;
    };
  
  };
} // namespace impl

template<typename Tp1,typename Tp2> struct remove;

template<typename Tp1,typename Tp2>
struct remove
{
  static_assert (impl::false_type<Tp1>::value,"tuple_ext: remove only takes tuples as template parameters");
};

template<typename ...T1s,typename... T2s>
struct remove<std::tuple<T1s...>,std::tuple<T2s...>>
{
  using type = typename impl::remove<T1s...>::from<T2s...>::type;
};

template<typename Tp1,typename Tp2> 
using remove_t = typename remove<Tp1,Tp2>::type;

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
          has_type<T1s,T2s...>::value,
          std::tuple<T1s>,
          std::tuple<>
        >::type...
      >;
    };
  
  };
} 

template<typename Tp1,typename Tp2> struct inter;

template<typename Tp1,typename Tp2>
struct inter
{
  static_assert (impl::false_type<Tp1>::value,"tuple_ext: inter only takes tuples as template parameters");
};

template<typename... T1s,typename... T2s>
struct inter<std::tuple<T1s...>,std::tuple<T2s...>>
{
  using type = distinct_t<typename impl::inter<T1s...>::with<T2s...>::type>;
};

template<typename Tp1,typename Tp2>
using inter_t = typename inter<Tp1,Tp2>::type;

} // namespace tuple_ext

