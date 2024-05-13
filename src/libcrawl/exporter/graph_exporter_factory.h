#include <memory>
#include <stdexcept>

#include "libcrawl/exporter/csv_graph_exporter.h"
#include "libcrawl/exporter/export_format.h"
#include "libcrawl/exporter/igraph_exporter.h"
#include "libcrawl/exporter/json_graph_exporter.h"

namespace libcrawl {

class GraphExporterFactory {
 public:
  static std::unique_ptr<IGraphExporter> CreateExporter(ExportFormat format) {
    switch (format) {
      case ExportFormat::kJson:
        return std::make_unique<JsonGraphExporter>();
      case ExportFormat::kCsv:
        return std::make_unique<CsvGraphExporter>();
      default:
        throw std::invalid_argument("Invalid export format");
    }
  }
};

}  // namespace libcrawl