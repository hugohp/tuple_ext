#include "tuple_ext.h"
#include <tuple>

using namespace tuple_ext;
using namespace std;

struct tuple_testing
{
  // Some types
  struct t0 {};
  struct t1 {};
  struct t2 {};
  struct t3 {};
  struct t4 {};

  struct tuple_cat_tests {

    // concat [[t0,t1],[t2,t3]] = [t0,t1,t2,t3]
    static_assert (
      is_same_v<
        tuple_cat_t<
          tuple<t0,t1>,
          tuple<t2,t3>
        >,
        tuple<t0,t1,t2,t3>
      >
    );

    // concat [[t0,t1],[]] = [t0,t1]
    static_assert (
      is_same_v<
        tuple_cat_t<
          tuple<t0,t1>,
          tuple<>
        >,
        tuple<t0,t1>
      >
    );

    // concat [[],[t0,t1]] = [t0,t1]
    static_assert (
      is_same_v<
        tuple_cat_t<
          tuple<>,
          tuple<t0,t1>
        >,
        tuple<t0,t1>
      >
    );
  };



  struct head_tests {

    // head [t0,t1,t2] = t0
    static_assert (
      is_same_v<
        head_t<tuple<t0,t1,t2>>,
        t0
        >
    );

    // head [t0] = t0
    static_assert (
      is_same_v<
        head_t< tuple<t0>>,
        t0
      >
    );

  };



  struct tail_tests {

    // tail [t0,t1,t2] = [t1,t2]
    static_assert (
      is_same_v<
       tail_t<tuple<t0,t1,t2>>,
       tuple<t1,t2>
      >
    );

    // tail [t0] = []
    static_assert (
      is_same_v<
       tail_t<tuple<t0>>,
       tuple<>
      >
    );

  };



  struct has_type_tests {

    static_assert ( has_type_v< t0, tuple<t1,t2,t0> > );
    static_assert ( ! has_type_v< t0 ,tuple<t1,t2> > );

  };


  struct reverse_tests {

    // reverse [] = []
    static_assert (
      is_same_v<
        reverse_t<tuple<>>,
        tuple<>
      >
    );

    // reverse [t0] = [t0]
    static_assert (
      is_same_v<
        reverse_t<tuple<t0>>,
        tuple<t0>
      > );

    // reverse [t0,t1,t2] = [t2,t1,t0]
    static_assert (
      is_same_v<
       reverse_t<tuple<t0,t1,t2>>,
       tuple<t2,t1,t0>
      >
    );

  };

  struct distinct_tests {

    // distinct [] = []
    static_assert (
      is_same_v<
       distinct_t<tuple<>>,
       tuple<>
      >
    );

    // distinct [t0] = [t0]
    static_assert (
      is_same_v<
        tuple<t0>,
        tuple<t0>
      >
    );

    // distinct [t0,t1] = [t0,t1]
    static_assert (
      is_same_v<
        distinct_t<tuple<t0,t1>>,
        tuple<t0,t1>
      >
    );

    // distinct [t0,t1,t1,t2,t0,t2] = [t0,t1,t2]
    static_assert (
      is_same_v<
        distinct_t<tuple<t0,t1,t1,t2,t0,t2>>,
        tuple<t0,t1,t2>
      >
    );

  };

  struct remove_test {

    // remove [t0,t2] [t0,t1,t2,t3] = [t1,t3]
    static_assert (
      is_same_v<
        remove_t<
          tuple<t0,t2>,
          tuple<t0,t1,t2,t3>
        >,
        tuple<t1,t3>
      >
    );

    // remove [] [t0,t1,t2,t3] = [t0,t1,t2,t3]
    static_assert (
      is_same_v<
        remove_t<
          tuple<>,
          tuple<t0,t1,t2,t3>
        >,
        tuple<t0,t1,t2,t3>
      >
    );

    // remove [t0,t1,t2,t3] [] = []
    static_assert (
      is_same_v<
        remove_t<
          tuple<t0,t1,t2,t3>,
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

    // inter [t0,t1,t2,t3] [t0,t1] = [t0,t1]
    static_assert (
      is_same_v<
        inter_t<
          tuple<t0,t1,t2,t3>,
          tuple<t0,t1>
        >,
        tuple<t0,t1>
      >
    );

    // inter [t0,t1] [t2,t3] = []
    static_assert (
      is_same_v<
        inter_t<
          tuple<t0,t1>,
          tuple<t2,t3>
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
};

