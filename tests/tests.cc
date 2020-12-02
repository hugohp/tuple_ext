#include "tuple_ext.h"
#include <tuple>

using namespace tuple_ext;
using namespace std;

struct tuple_testing
{
  struct Type0 {};
  struct Type1 {};
  struct Type2 {};
  struct Type3 {};
  struct Type4 {};

  struct head_test {
    static_assert (is_same<head_t<tuple<Type0>>,Type0>::value);
    static_assert (is_same<head_t<tuple<Type0,Type1,Type2>>,Type0>::value);
  };

  struct tail_test {
    static_assert (is_same<tail_t<tuple<>>,tuple<>>::value);
    static_assert (is_same<tail_t<tuple<Type0>>,tuple<>>::value);
    static_assert (is_same<tail_t<tuple<Type0,Type1,Type2>>,tuple<Type1,Type2>>::value);
  };

  struct has_type_test {
    static_assert (has_type<Type0,tuple<Type1,Type2,Type0>>::value);
    static_assert (! has_type<Type0,tuple<Type1,Type2>>::value);
  };

  struct reverse_test {
    using rtype0 = reverse_t<tuple<>>;
    static_assert (is_same<rtype0,tuple<>>::value);

    using rtype1 = reverse_t<tuple<Type0>>;
    static_assert (is_same<rtype1,tuple<Type0>>::value);

    using rtype2 = reverse_t<tuple<Type0,Type1,Type2>>;
    static_assert (is_same<rtype2,tuple<Type2,Type1,Type0>>::value);
  };

  struct distinct_test {
    using utype0 = distinct_t<tuple<>>;
    static_assert (is_same<utype0,tuple<>>::value);

    using utype1 = distinct_t<tuple<Type0>>;
    static_assert (is_same<utype1,tuple<Type0>>::value);

    using utype2 = distinct_t<tuple<Type0,Type1>>;
    static_assert (is_same<utype2,tuple<Type0,Type1>>::value);

    using utype3 = distinct_t<tuple<Type0,Type1,Type1,Type2,Type0,Type2>>;
    static_assert (is_same<utype3,tuple<Type0,Type1,Type2>>::value);
  };

  struct remove_test {
    using rtype0 = remove_t<tuple<>,tuple<>>;
    static_assert (is_same<rtype0,tuple<>>::value);

    using rtype1 = remove_t<tuple<>,tuple<Type0,Type1>>;
    static_assert (is_same<rtype1,tuple<Type0,Type1>>::value);

    using rtype2 = remove_t<tuple<Type0>,tuple<>>;
    static_assert (is_same<rtype2,tuple<>>::value);

    using rtype3 = remove_t<tuple<Type0,Type1>,tuple<Type0,Type1,Type2,Type3>>;
    static_assert (is_same<rtype3,tuple<Type2,Type3>>::value);

    using rtype4 = remove_t<tuple<Type0,Type1>,tuple<Type0,Type2,Type3>>;
    static_assert (is_same<rtype4,tuple<Type2,Type3>>::value);

    using rtype5 = remove_t<tuple<Type0,Type1>,tuple<Type0,Type0,Type1>>;
    static_assert (is_same<rtype5,tuple<>>::value);

  };

  struct append_test {
    using atype0 = append_t<tuple<>,tuple<>>;
    static_assert (is_same<atype0,tuple<>>::value);

    using atype1 = append_t<tuple<>,tuple<Type0,Type1>>;
    static_assert (is_same<atype1,tuple<Type0,Type1>>::value);

    using atype2 = append_t<tuple<Type0>,tuple<>>;
    static_assert (is_same<atype2,tuple<Type0>>::value);

    using atype3 = append_t<tuple<Type0,Type3>,tuple<Type0,Type1>>;
    static_assert (is_same<atype3,tuple<Type0,Type1,Type0,Type3>>::value);

  };

  struct prepend_test {
    using atype0 = prepend_t<tuple<>,tuple<>>;
    static_assert (is_same<atype0,tuple<>>::value);

    using atype1 = prepend_t<tuple<>,tuple<Type0,Type1>>;
    static_assert (is_same<atype1,tuple<Type0,Type1>>::value);

    using atype2 = prepend_t<tuple<Type0>,tuple<>>;
    static_assert (is_same<atype2,tuple<Type0>>::value);

    using atype3 = prepend_t<tuple<Type0,Type3>,tuple<Type0,Type1>>;
    static_assert (is_same<atype3,tuple<Type0,Type3,Type0,Type1>>::value);
  };

  struct inter_test {
    using itype0 = inter_t<tuple<>,tuple<>>;
    static_assert (is_same<itype0,tuple<>>::value);

    using itype1 = inter_t<tuple<>,tuple<Type0,Type1>>;
    static_assert (is_same<itype1,tuple<>>::value);

    using itype2 = inter_t<tuple<Type0>,tuple<>>;
    static_assert (is_same<itype2,tuple<>>::value);

    using itype3 = inter_t<tuple<Type0,Type3>,tuple<Type0,Type1>>;
    static_assert (is_same<itype3,tuple<Type0>>::value);

    using itype4 = inter_t<tuple<Type0,Type0>,tuple<Type0,Type1>>;
    static_assert (is_same<itype4,tuple<Type0>>::value);

  };

  struct union_test {
    using utype0 = union_t<tuple<>,tuple<>>;
    static_assert (is_same<utype0,tuple<>>::value);

    using utype1 = union_t<tuple<>,tuple<Type0,Type1>>;
    static_assert (is_same<utype1,tuple<Type0,Type1>>::value);

    using utype2 = union_t<tuple<Type0>,tuple<>>;
    static_assert (is_same<utype2,tuple<Type0>>::value);

    using utype3 = union_t<tuple<Type0,Type3>,tuple<Type0,Type1>>;
    static_assert (is_same<utype3,tuple<Type0,Type3,Type1>>::value);

  };

  struct select_test {
    using stype0 = select_t<tuple<>,tuple<>>;
    static_assert (is_same<stype0,tuple<>>::value);

    using stype1 = select_t<tuple<>,tuple<Type0,Type1>>;
    static_assert (is_same<stype1,tuple<>>::value);

    using stype3 = select_t<tuple<Type0,Type1>,tuple<Type0,Type1,Type3>>;
    static_assert (is_same<stype3,tuple<Type0,Type1>>::value);
  };
};

