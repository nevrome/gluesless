#include <vector>
#include <algorithm>

template<typename T>
std::vector<T> remove_duplicates(std::vector<T> &v) {
  std::sort(v.begin(), v.end());
  auto it = std::unique(v.begin(), v.end());  // 10 20 30 20 10 ?  ?  ?  ?
  v.resize(std::distance(v.begin(), it)); // 10 20 30 20 10
  return(v);
}
