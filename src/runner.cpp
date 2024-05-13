#include <iostream>

#include "libcrawl/crawler/crawler.h"
#include "libcrawl/defs.h"
#include "libcrawl/graph/crawl_graph.h"

using namespace libcrawl;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <URL> <max-depth>" << std::endl;
    return 1;
  }

  URL url(argv[1]);
  int max_depth = std::stoi(argv[2]);
  std::cout << "crawling " << url << "..." << std::endl;

  Crawler crawler;
  crawler.Init(url, max_depth);
  crawler.Crawl();
  crawler.ExportGraph("graph.json", ExportFormat::kJson);

  return 0;
}