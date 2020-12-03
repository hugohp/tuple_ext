# tuple_ext

Extentions to *std::tuple* partially inspired on Andrei Alexandresku's typelists, but for C++20.

Noticing *std::tuple* is similar to a Haskell list, here we implement some Haskell-like prelude functions e.g. concat, head, tail, map.

## Examples
```
  using namespace std;
  using namespace tuple_ext;

  // Let us define some types
  using zero_t  = std::integral_constant<unsigned int, 0>;
  using one_t   = std::integral_constant<unsigned int, 1>;
  using two_t   = std::integral_constant<unsigned int, 2>;
  using three_t = std::integral_constant<unsigned int, 3>;
  using four_t  = std::integral_constant<unsigned int, 4>;
  using five_t  = std::integral_constant<unsigned int, 5>;
  using six_t   = std::integral_constant<unsigned int, 6>;

  // concat [0,1] [2,3] = [0,1,2,3]
  using concat_result_t = concat_t<
    tuple<zero_t,one_t>,
    tuple<two_t,three_t>
    >;

  // head [0,1,2] = 0
  using head_result_t = head_t<tuple<zero_t,one_t,two_t>>;

  // tail [0,1,2] = [1,2]
  using tail_result_t = tail_t<tuple<zero_t,one_t,two_t>>;

  // reverse [0,1,2] = [2,1,0]
  using reverse_result_t = reverse_t<tuple<zero_t,one_t,two_t>>;

  // unique [0,1,1,2,0,2] = [0,1,2]
  using unique_result_t = unique_t<tuple<zero_t,one_t,one_t,two_t,zero_t,two_t>>;

  // remove [0,two_t] [0,1,2,3] = [1,3]
  using remove_result_t = remove_t<tuple<zero_t,two_t>,tuple<zero_t,one_t,two_t,three_t>>;

  // inter [0,1,2,3] [0,1] = [0,1]
  using inter_result_t = inter_t<tuple<zero_t,one_t,two_t,three_t>,tuple<zero_t,one_t>>;

  // zip [0,1] [2,3]  = [(0,2),(1,3)]
  using zip_result_t = zip_t<tuple<zero_t,one_t>,tuple<two_t,three_t>>;

  // unzip [(0,2),(1,3)] = ([0,1],[2,3])
  using unzip_result_t = unzip_t< tuple<pair<zero_t,two_t>,pair<one_t,three_t>> >;

  // f(x) = x + 1 
  template<typename T>
  struct add_one_t { 
    using value_type = std::remove_cv_t<decltype(T::value)>;
    using type = std::integral_constant<value_type,T::value + 1>;
  };

  // map f [0,1,2] = [1,2,3]
  using map_result_t = map_t< add_one_t, std::tuple<zero_t,one_t,two_t> >;
```
