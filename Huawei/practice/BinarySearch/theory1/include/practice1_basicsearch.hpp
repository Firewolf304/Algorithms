#pragma once
#include <string>
#include <vector>

namespace firewolf::binary_search {

template <typename type>
int search(const std::vector<type> &massive, type value);

template <typename type>
int search2(const std::vector<type> &vector, type value);

} // namespace firewolf::binary_search

#include "practice1_basicsearch.ipp"