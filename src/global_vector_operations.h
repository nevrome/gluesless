#include <vector>
#include <algorithm>
#include "Snap.h"

template<typename T>
inline std::vector<T> remove_duplicates(std::vector<T> &v) {
  std::sort(v.begin(), v.end());
  auto it = std::unique(v.begin(), v.end());  // 10 20 30 20 10 ?  ?  ?  ?
  v.resize(std::distance(v.begin(), it)); // 10 20 30 20 10
  return(v);
}

template<typename T>
inline std::vector<T> erase_elements_of_second_vector_from_the_first(std::vector<T> &first, std::vector<T> &second) {
  first.erase(
    remove_if(
      first.begin(), first.end(),
      [&](auto x){ return find(second.begin(), second.end() , x) != second.end(); }
    ),
    first.end()
  );
  return(first);
}

inline TIntV combine_vectors_to_TIntV(std::vector<int> &first, std::vector<int> &second) {
  TIntV new_vector;
  new_vector.Reserve(first.size() + second.size());
  for (auto& i : first) {
    new_vector.Add(i);
  }
  for (auto& i : second) {
    new_vector.Add(i);
  }
  return(new_vector);
}
