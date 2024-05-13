#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include <stdexcept>

#include "libcrawl/defs.h"
#include "libcrawl/graph/page_node.h"
#include "libcrawl/page/web_page.h"

namespace libcrawl {

using WebPage_ptr = Ptr<WebPage>;
using GraphNode_ptr = Ptr<GraphNode>;

/**
TODO: 
  - maybe pass pages using reference or pointers to avoid copying
  - maybe use unordered_set for links
**/

class CrawlGraph {
 public:
  CrawlGraph() = default;
  ~CrawlGraph() = default;

  void Init(WebPage_ptr root);
  Vector<Identifier> ExpendNode(Identifier node_id, Vector<WebPage_ptr> out_links);
  WebPage_ptr GetPage(Identifier node_id);
  GraphNode_ptr GetNode(Identifier node_id);
  WebPage_ptr GetRootPage() { return root_->GetPage(); }
  Identifier GetRootID() const { return root_id_; }
  void TreePrint() const { root_->TreePrint(); }

 private:
  GraphNode_ptr pushNode(Identifier id, WebPage_ptr page, uint32_t depth);

  Identifier next_id = 0;
  Identifier root_id_;
  GraphNode_ptr root_;
  std::unordered_map<Identifier, GraphNode_ptr> nodes;
  std::unordered_map<Identifier, Identifier> links_;  // id1 -> id2
};

}  // namespace libcrawl