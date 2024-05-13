#include <memory>
#include <string>
#include <vector>
#include <regex>

#include "libcrawl/defs.h"

namespace libcrawl {

class PageLinkProcessor {
 public:
  static Links Process(const std::string& content);
};

}  // namespace libcrawl