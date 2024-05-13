#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include "libcrawl/defs.h"
#include "libcrawl/page/web_page.h"

namespace libcrawl {

using WebPage_ptr = Ptr<WebPage>;

class GraphNode {
 public:
  GraphNode(Identifier id, WebPage_ptr page, uint32_t depth)
      : id_(id), page_(page), depth_(depth) {}
  Identifier GetID() const { return id_; }
  WebPage_ptr GetPage() const { return page_; }
  void AddInLink(Ptr<GraphNode> in_link) { in_links_.push_back(in_link); }
  void AddOutLink(Ptr<GraphNode> out_link) { out_links_.push_back(out_link); }
  Vector<Ptr<GraphNode>> GetInLinks() const { return in_links_; }
  Vector<Ptr<GraphNode>> GetOutLinks() const { return out_links_; }
  uint32_t GetDepth() const { return depth_; }
  void TreePrint() const {
    // print self with depth visualization
    for (uint32_t i = 0; i < depth_; ++i) {
      std::cout << "-";
    }
    std::cout << "[" << id_ << "]" << page_->GetURL() << std::endl;
    for (const auto& out_link : out_links_) {
      out_link->TreePrint();
    }
  }

 private:
  Identifier id_;
  WebPage_ptr page_;
  uint32_t depth_;
  Vector<Ptr<GraphNode>> in_links_;
  Vector<Ptr<GraphNode>> out_links_;
};

}  // namespace libcrawl