#include "tuple_ext.h"
#include <tuple>
#include <type_traits>

using namespace tuple_ext;
using namespace std;

template<typename X,typename Y>
  concept is_same_value = 
    std::is_same_v<
      std::remove_cv_t<decltype(X::value)>,
      std::remove_cv_t<decltype(Y::value)>
    >;




struct tuple_testing
{
  // Some types
  using zero_t = std::integral_constant<unsigned int, 0>;
  using one_t = std::integral_constant<unsigned int, 1>;
  using two_t = std::integral_constant<unsigned int, 2>;
  using three_t = std::integral_constant<unsigned int, 3>;

  struct tuple_cat_tests {

    // concat [zero_t,one_t] [two_t,three_t] = [zero_t,one_t,two_t,three_t]
    static_assert (
      is_same_v<
        concat_t<
          tuple<zero_t,one_t>,
          tuple<two_t,three_t>
        >,
        tuple<zero_t,one_t,two_t,three_t>
      >
    );

    // concat [zero_t,one_t] [] = [zero_t,one_t]
    static_assert (
      is_same_v<
        concat_t<
          tuple<zero_t,one_t>,
          tuple<>
        >,
        tuple<zero_t,one_t>
      >
    );

    // concat [] [zero_t,one_t] = [zero_t,one_t]
    static_assert (
      is_same_v<
        concat_t<
          tuple<>,
          tuple<zero_t,one_t>
        >,
        tuple<zero_t,one_t>
      >
    );
  };



  struct head_tests {

    // head [zero_t,one_t,two_t] = zero_t
    static_assert (
      is_same_v<
        head_t<tuple<zero_t,one_t,two_t>>,
        zero_t
        >
    );

    // head [zero_t] = zero_t
    static_assert (
      is_same_v<
        head_t<tuple<zero_t>>,
        zero_t
      >
    );

  };



  struct tail_tests {

    // tail [zero_t,one_t,two_t] = [one_t,two_t]
    static_assert (
      is_same_v<
       tail_t<tuple<zero_t,one_t,two_t>>,
       tuple<one_t,two_t>
      >
    );

    // tail [zero_t] = []
    static_assert (
      is_same_v<
       tail_t<tuple<zero_t>>,
       tuple<>
      >
    );

  };



  struct has_type_tests {

    static_assert ( has_type_v< zero_t, tuple<one_t,two_t,zero_t> > );
    static_assert ( ! has_type_v< zero_t ,tuple<one_t,two_t> > );
    static_assert ( ! has_type_v< zero_t ,tuple<> > );

  };


  struct reverse_tests {

    // reverse [zero_t,one_t,two_t] = [two_t,one_t,zero_t]
    static_assert (
      is_same_v<
       reverse_t<tuple<zero_t,one_t,two_t>>,
       tuple<two_t,one_t,zero_t>
      >
    );

    // reverse [zero_t] = [zero_t]
    static_assert (
      is_same_v<
        reverse_t<tuple<zero_t>>,
        tuple<zero_t>
      > );

    // reverse [] = []
    static_assert (
      is_same_v<
        reverse_t<tuple<>>,
        tuple<>
      >
    );

  };

  struct unique_tests {

    // unique [zero_t,one_t,one_t,two_t,zero_t,two_t] = [zero_t,one_t,two_t]
    static_assert (
      is_same_v<
        unique_t<tuple<zero_t,one_t,one_t,two_t,zero_t,two_t>>,
        tuple<zero_t,one_t,two_t>
      >
    );

    // unique [zero_t,one_t] = [zero_t,one_t]
    static_assert (
      is_same_v<
        unique_t<tuple<zero_t,one_t>>,
        tuple<zero_t,one_t>
      >
    );

    // unique [] = []
    static_assert (
      is_same_v<
       unique_t<tuple<>>,
       tuple<>
      >
    );

    // unique [zero_t] = [zero_t]
    static_assert (
      is_same_v<
        tuple<zero_t>,
        tuple<zero_t>
      >
    );

  };

  struct remove_test {

    // remove [zero_t,two_t] [zero_t,one_t,two_t,three_t] = [one_t,three_t]
    static_assert (
      is_same_v<
        remove_t<
          tuple<zero_t,two_t>,
          tuple<zero_t,one_t,two_t,three_t>
        >,
        tuple<one_t,three_t>
      >
    );

    // remove [] [zero_t,one_t,two_t,three_t] = [zero_t,one_t,two_t,three_t]
    static_assert (
      is_same_v<
        remove_t<
          tuple<>,
          tuple<zero_t,one_t,two_t,three_t>
        >,
        tuple<zero_t,one_t,two_t,three_t>
      >
    );

    // remove [zero_t,one_t,two_t,three_t] [] = []
    static_assert (
      is_same_v<
        remove_t<
          tuple<zero_t,one_t,two_t,three_t>,
          tuple<>
        >,
        tuple<>
      >
    );

    // remove [] [] = []
    static_assert (
      is_same_v<
        remove_t<
          tuple<>,
          tuple<>
        >,
        tuple<>
      >
    );

  };

  struct inter_test {

    // inter [zero_t,one_t,two_t,three_t] [zero_t,one_t] = [zero_t,one_t]
    static_assert (
      is_same_v<
        inter_t<
          tuple<zero_t,one_t,two_t,three_t>,
          tuple<zero_t,one_t>
        >,
        tuple<zero_t,one_t>
      >
    );

    // inter [zero_t,one_t] [two_t,three_t] = []
    static_assert (
      is_same_v<
        inter_t<
          tuple<zero_t,one_t>,
          tuple<two_t,three_t>
        >,
        tuple<>
      >
    );

    // inter [zero_t,one_t] [] = []
    static_assert (
      is_same_v<
        inter_t<
          tuple<zero_t,one_t>,
          tuple<>
        >,
        tuple<>
      >
    );

    // inter [] [zero_t,one_t] = []
    static_assert (
      is_same_v<
        inter_t<
          tuple<>,
          tuple<zero_t,one_t>
        >,
        tuple<>
      >
    );

    // inter [] [] = []
    static_assert (
      is_same_v<
        inter_t<
          tuple<>,
          tuple<>
        >,
        tuple<>
      >
    );
  };

  struct zip_tests {

    // zip [zero_t,one_t] [two_t,three_t]  = [(zero_t,two_t),(one_t,three_t)]
    static_assert (
      is_same_v<
        zip_t<
          tuple<zero_t,one_t>,
          tuple<two_t,three_t>
        >,
        tuple<pair<zero_t,two_t>,pair<one_t,three_t>>
      >
    );
  };

  struct unzip_tests {

    // unzip [(zero_t,two_t),(one_t,three_t)] = ([zero_t,one_t],[two_t,three_t])
    static_assert (
      is_same_v<
        unzip_t<
          tuple<pair<zero_t,two_t>,pair<one_t,three_t>>
        >,
        pair<tuple<zero_t,one_t>,tuple<two_t,three_t>>
      >
    );
  };

  // f(x,y) = x+y
  template<typename X,typename Y>
  requires ( is_same_value<X,Y> )
  struct sum {
    using value_type = std::remove_cv_t<decltype(X::value)>;
    using type = std::integral_constant<value_type,X::value + Y::value>;
  };

  // f(x) = 1 + x;
  template<typename X>
  struct add_one : sum<X,one_t>{};

  struct map_tests {

    // map f [0,1,2] = [1,2,3] where f(x) = 1 + x
    static_assert (
      is_same_v<
        map_t<
          add_one,
          std::tuple<zero_t,one_t,two_t>
        >,
        std::tuple<one_t,two_t,three_t>
      >
    );
  };

  struct foldr_tests {

    // foldr f 0 [1,2,3] = 6 where f(x,y) = x + y
    static_assert (
      is_same_v<
        foldr_t<
          sum,
          zero_t,
          std::tuple<one_t,two_t,three_t>
        >,
        std::integral_constant<unsigned int, 6>
      >
    );
  };

  struct foldl_tests {

    // foldl f 0 [1,2,3] = 6 where f(x,y) = x + y
    static_assert (
      is_same_v<
        foldl_t<
          sum,
          zero_t,
          std::tuple<one_t,two_t,three_t>
        >,
        std::integral_constant<unsigned int, 6>
      >
    );
  };

};

