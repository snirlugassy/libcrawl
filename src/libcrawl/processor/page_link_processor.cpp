#include "libcrawl/processor/page_link_processor.h"

namespace libcrawl {

Links PageLinkProcessor::Process(const std::string& content) {
  Links links;
  // std::regex link_regex("<a href=\"([^\"]+)\">");
  // regex for http links only
  std::regex link_regex("<a href=\"(http[^\"]+)\">");
  std::smatch match;
  std::string::const_iterator search_start(content.cbegin());
  while (std::regex_search(search_start, content.cend(), match, link_regex)) {
    links.push_back(match[1]);
    search_start = match.suffix().first;
  }
  return links;
}

}  // namespace libcrawl