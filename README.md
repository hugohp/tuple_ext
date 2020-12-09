# tuple_ext

Extentions to *std::tuple* using type-level functions.

The *std::tuple* is similar to a Haskell list, but of types instead of values. This library implements some Haskell-like prelude functions to be used with *std::tuple*s: head, tail, reverse, map, foldl, foldr and more.

## Examples

```
#include "tuple_ext.h"
#include <functional>

using namespace std;
using namespace tuple_ext;

// Let us define some types
using zero_t  = std::integral_constant<unsigned int, 0>;
using one_t   = std::integral_constant<unsigned int, 1>;
using two_t   = std::integral_constant<unsigned int, 2>;
using three_t = std::integral_constant<unsigned int, 3>;
using four_t = std::integral_constant<unsigned int, 4>;
using five_t = std::integral_constant<unsigned int, 5>;
using six_t = std::integral_constant<unsigned int, 6>;
```

### ```concat```
```
// concat [0,1] [2,3] = [0,1,2,3]
using concat_result_t = concat_t<
  tuple<zero_t,one_t>,
  tuple<two_t,three_t>
  >;
```

### ```head```
```
// head [0,1,2] = 0
using head_result_t = head_t<tuple<zero_t,one_t,two_t>>;
static_assert( is_same_v<head_result_t, zero_t> );
```

### ```tail```
```
// tail [0,1,2] = [1,2]
using tail_result_t = tail_t<tuple<zero_t,one_t,two_t>>;
static_assert( is_same_v<tail_result_t, std::tuple<one_t,two_t>> );
```

### ```reverse```
```
// reverse [0,1,2] = [2,1,0]
using reverse_result_t = reverse_t<tuple<zero_t,one_t,two_t>>;
static_assert( is_same_v<reverse_result_t, std::tuple<two_t,one_t,zero_t>> );
```

### ```unique```
```
// unique [0,1,1,2,0,2] = [0,1,2]
using unique_result_t = unique_t<tuple<zero_t,one_t,one_t,two_t,zero_t,two_t>>;
static_assert( is_same_v<unique_result_t, std::tuple<zero_t,one_t,two_t>> );
```

### ```remove```
```
// remove [0,two_t] [0,1,2,3] = [1,3]
using remove_result_t = remove_t<tuple<zero_t,two_t>,tuple<zero_t,one_t,two_t,three_t>>;
static_assert( is_same_v<remove_result_t, std::tuple<one_t,three_t>> );
```

### ```inter```
```
// inter [0,1,2,3] [0,1] = [0,1]
using inter_result_t = inter_t<tuple<zero_t,one_t,two_t,three_t>,tuple<zero_t,one_t>>;
static_assert( is_same_v<inter_result_t, std::tuple<zero_t,one_t>> );
```

### ```zip```
```
// zip [0,1] [2,3]  = [(0,2),(1,3)]
using zip_result_t = zip_t<tuple<zero_t,one_t>,tuple<two_t,three_t>>;
static_assert( 
  is_same_v<
    zip_result_t, 
    std::tuple<
      std::pair<zero_t,two_t>,
      std::pair<one_t,three_t>
    >
  > 
);
```


### ```unzip```
```
// unzip [(0,2),(1,3)] = ([0,1],[2,3])
using unzip_result_t = unzip_t< tuple<pair<zero_t,two_t>,pair<one_t,three_t>> >;
static_assert( 
  is_same_v<
    unzip_result_t, 
    std::pair<
      std::tuple<zero_t,one_t>,
      std::tuple<two_t,three_t>
    >
  > 
);
```


### ```filter```
```
// is_even(x) = true if x is even, otherwise false
template<typename X>
struct is_even {
  static constexpr bool value = (std::modulus()(X::value,2) == 0);
};

// filter f [0,1,2,3,4] = [0,2,4]
using filter_result_t = filter_t<
  is_even,
  std::tuple<zero_t,one_t,two_t,three_t,four_t>
>;
static_assert( is_same_v<filter_result_t, std::tuple<zero_t,two_t,four_t>> );
```

### Some type-level functions
```
// sum(x,y) = x + y
template<typename X,typename Y>
struct sum {
  using value_type = std::remove_cv_t<decltype(X::value)>;
  using type = std::integral_constant<value_type,X::value + Y::value>;
};

// f(x) = 1 + x;
template<typename X>
struct add_one : sum<X,one_t>{};
```

### ```map```
```
// map f [0,1,2] = [1,2,3] where f(x) = 1 + x
using map_result_t = map_t< add_one, std::tuple<zero_t,one_t,two_t> >;
static_assert( is_same_v<map_result_t, std::tuple<one_t,two_t,three_t>> );
```

### ```foldr```
```
// foldr f 0 [1,2,3] = 6 where f(x,y) = x + y
using foldr_result_t = foldr_t<
  sum,
  zero_t,
  std::tuple<one_t,two_t,three_t>
>;
static_assert( is_same_v<foldr_result_t, six_t> );
```
