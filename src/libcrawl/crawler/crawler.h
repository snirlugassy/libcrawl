#pragma once

#include <queue>
#include <stack>
#include <string>

#include "libcrawl/defs.h"
#include "libcrawl/exporter/graph_exporter_factory.h"
#include "libcrawl/graph/page_node.h"
#include "libcrawl/page/web_page.h"
#include "libcrawl/processor/page_link_processor.h"

namespace libcrawl {

class Crawler {
 public:
  Crawler() = default;
  void Init(const URL& root_url, uint32_t max_depth);
  void Crawl();
  const CrawlGraph& GetGraph() const;
  void ExportGraph(std::string file_path, ExportFormat format) const;

 private:
  HTMLText extractHTML(const URL& url) const;
  WebPage_ptr processPage(const URL& url) const;

  uint32_t max_depth_;
  URL root_url_;
  Ptr<CrawlGraph> graph_;
  Ptr<IGraphExporter> exporter_;
  Ptr<PageLinkProcessor> page_link_processor_;
};

}  // namespace libcrawl