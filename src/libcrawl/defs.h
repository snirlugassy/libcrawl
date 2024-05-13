#pragma once

#include <string>
#include <vector>
#include <memory>

namespace libcrawl {

// general definitions

using Text = std::string;
using HTMLText = std::string;
using URL = std::string;
using Link = std::string;
using Links = std::vector<Link>;

using Identifier = uint64_t;

template <typename T>
using Ptr = std::shared_ptr<T>;

template <typename T>
using Vector = std::vector<T>;

}  // namespace libcrawl