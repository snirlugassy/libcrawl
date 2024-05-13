#pragma once

#include "libcrawl/exporter/igraph_exporter.h"

namespace libcrawl {

class CsvGraphExporter : public IGraphExporter {
 public:
  void Export(const CrawlGraph& graph, const std::string& file_path) const override;
};

}  // namespace libcrawl