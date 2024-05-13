#include "libcrawl/graph/crawl_graph.h"

namespace libcrawl {

void CrawlGraph::Init(WebPage_ptr root) {
  root_id_ = next_id++;
  auto root_node = pushNode(root_id_, root, 0);
  root_ = root_node;
}

Vector<Identifier> CrawlGraph::ExpendNode(Identifier node_id, Vector<WebPage_ptr> out_links) {
  if (nodes.find(node_id) == nodes.end()) {
    throw std::runtime_error("Node not found" + std::to_string(node_id));
  }

  Vector<Identifier> new_nodes_ids;
  GraphNode_ptr node = nodes[node_id];
  uint32_t depth = node->GetDepth() + 1;
  for (auto& page_ptr : out_links) {
    Identifier id = next_id++;
    auto new_node = pushNode(id, page_ptr, depth + 1);
    links_[node_id] = id;
    node->AddOutLink(new_node);
    new_node->AddInLink(node);
    new_nodes_ids.push_back(id);
  }
  return new_nodes_ids;
}

WebPage_ptr CrawlGraph::GetPage(Identifier node_id) {
  if (nodes.find(node_id) == nodes.end()) {
    return nullptr;
  }
  return nodes[node_id]->GetPage();
}

GraphNode_ptr CrawlGraph::GetNode(Identifier node_id) {
  if (nodes.find(node_id) == nodes.end()) {
    return nullptr;
  }
  return nodes[node_id];
}

GraphNode_ptr CrawlGraph::pushNode(Identifier id, WebPage_ptr page, uint32_t depth) {
  auto node = std::make_shared<GraphNode>(id, page, depth);
  nodes[id] = node;
  return node;
}

}  // namespace libcrawl