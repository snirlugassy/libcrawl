#pragma once

#include "libcrawl/exporter/export_format.h"
#include "libcrawl/graph/crawl_graph.h"
#include "libcrawl/graph/page_node.h"
#include "libcrawl/page/web_page.h"

namespace libcrawl {

class IGraphExporter {
 public:
  virtual void Export(const CrawlGraph& graph, const std::string& file_path) const = 0;
};

}  // namespace libcrawl