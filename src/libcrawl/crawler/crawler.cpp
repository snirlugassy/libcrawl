#include "libcrawl/crawler/crawler.h"

#include <curl/curl.h>

namespace libcrawl {

void Crawler::Init(const URL& root_url, uint32_t max_depth) {
  root_url_ = root_url;
  max_depth_ = max_depth;
  graph_ = std::make_unique<CrawlGraph>();
  WebPage_ptr root_page = processPage(root_url);
  graph_->Init(root_page);
  exporter_ = GraphExporterFactory::CreateExporter(ExportFormat::kCsv);
  page_link_processor_ = std::make_unique<PageLinkProcessor>();
}

void Crawler::Crawl() {
  if (!graph_) {
    throw std::runtime_error("Graph not initialized");
  }

  // breath first search (BFS) for crawling the web pages
  std::queue<Identifier> bfs_queue;
  bfs_queue.push(graph_->GetRootID());
  while (!bfs_queue.empty()) {
    Identifier node_id = bfs_queue.front();
    bfs_queue.pop();

    GraphNode_ptr node = graph_->GetNode(node_id);

    if (node->GetDepth() >= max_depth_) {
      continue;
    }

    Links out_links = node->GetPage()->GetLinks();
    for (const auto& link : out_links) {
      WebPage_ptr page = processPage(link);
      Identifier new_node_id = graph_->ExpendNode(node_id, {page})[0];
      bfs_queue.push(new_node_id);
    }
  }
}

const CrawlGraph& Crawler::GetGraph() const {
  if (!graph_) {
    throw std::runtime_error("Graph not initialized");
  }

  return *graph_;
}

void Crawler::ExportGraph(std::string file_path, ExportFormat format) const {}

static size_t write_callback(void* contents, size_t size, size_t nmemb, std::string* userp) {
  size_t realsize = size * nmemb;
  userp->append((char*)contents, realsize);
  return realsize;
}

HTMLText Crawler::extractHTML(const URL& url) const {
  CURL* curl = curl_easy_init();
  if (!curl) {
    throw std::runtime_error("Failed to initialize curl");
  }

  std::string content_buffer;
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content_buffer);
  CURLcode res = curl_easy_perform(curl);
  if (res != CURLE_OK) {
    throw std::runtime_error("Failed to fetch URL: " + url);
  }
  return content_buffer;
}

WebPage_ptr Crawler::processPage(const URL& url) const {
  HTMLText html = extractHTML(url);
  Links links = page_link_processor_->Process(html);
  WebPage_ptr page = std::make_shared<WebPage>(url, html);
  for (const auto& link : links) {
    page->AddLink(link);
  }
  return page;
}

}  // namespace libcrawl