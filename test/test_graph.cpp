#include "libcrawl/graph/crawl_graph.h"
#include "libcrawl/graph/page_node.h"
#include "libcrawl/defs.h"

#include <gtest/gtest.h>

using namespace libcrawl;

using GraphNode_ptr = Ptr<GraphNode>;

// class CrawlGraph {
//  public:
//   CrawlGraph() = default;
//   ~CrawlGraph() = default;

//   void Init(WebPage_ptr root);
//   Vector<Identifier> ExpendNode(Identifier node_id, Vector<WebPage_ptr> out_links);
//   WebPage_ptr GetPage(Identifier node_id);
//   GraphNode_ptr GetNode(Identifier node_id);
//   WebPage_ptr GetRootPage() { return root_->GetPage(); }
//   Identifier GetRootID() const { return root_id_; }

//  private:
//   GraphNode_ptr pushNode(Identifier id, WebPage_ptr page, uint32_t depth);

//   Identifier next_id = 0;
//   Identifier root_id_;
//   GraphNode_ptr root_;
//   std::unordered_map<Identifier, GraphNode_ptr> nodes;
//   std::unordered_map<Identifier, Identifier> links_;  // id1 -> id2
// };

class CrawlGraphTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}

  URL root_url_ = "http://www.google.com";
  HTMLText default_html_ = "<html></html>";
};

TEST_F(CrawlGraphTest, TestInit) {
  CrawlGraph graph;
  auto root_page = std::make_shared<WebPage>(root_url_, default_html_);
  graph.Init(root_page);
  EXPECT_EQ(graph.GetRootID(), 0);

  auto root_page_ptr = graph.GetRootPage();
  EXPECT_NE(root_page_ptr, nullptr);
  EXPECT_EQ(root_page_ptr->GetURL(), root_url_);
  EXPECT_EQ(root_page_ptr->GetHTMLText(), default_html_);
}

TEST_F(CrawlGraphTest, TestExpendNode) {
  CrawlGraph graph;
  auto root_page = std::make_shared<WebPage>(root_url_, default_html_);
  graph.Init(root_page);

  auto out_links = std::vector<WebPage_ptr>();
  out_links.push_back(std::make_shared<WebPage>("http://www.google.com/test", "<html></html>"));
  out_links.push_back(std::make_shared<WebPage>("http://www.google.com/test/1", "<html></html>"));
  out_links.push_back(std::make_shared<WebPage>("http://www.google.com/test/2", "<html></html>"));

  auto expanded_ids = graph.ExpendNode(0, out_links);
  ASSERT_EQ(expanded_ids.size(), 3);
  EXPECT_EQ(expanded_ids[0], 1);
  EXPECT_EQ(expanded_ids[1], 2);
  EXPECT_EQ(expanded_ids[2], 3);
}

TEST_F(CrawlGraphTest, TestGetPage) {
  CrawlGraph graph;
  auto root_page = std::make_shared<WebPage>(root_url_, default_html_);
  graph.Init(root_page);

  auto out_links = std::vector<WebPage_ptr>();
  out_links.push_back(std::make_shared<WebPage>("http://www.google.com/test", "<html></html>"));
  out_links.push_back(std::make_shared<WebPage>("http://www.google.com/test/1", "<html></html>"));
  out_links.push_back(std::make_shared<WebPage>("http://www.google.com/test/2", "<html></html>"));

  auto expanded_ids = graph.ExpendNode(0, out_links);
  ASSERT_EQ(expanded_ids.size(), 3);

  auto page = graph.GetPage(1);
  EXPECT_EQ(page->GetURL(), "http://www.google.com/test");
}

TEST_F(CrawlGraphTest, TestGetNode) {
  CrawlGraph graph;
  auto root_page = std::make_shared<WebPage>(root_url_, default_html_);
  graph.Init(root_page);

  auto out_links = std::vector<WebPage_ptr>();
  out_links.push_back(std::make_shared<WebPage>("http://www.google.com/test", "<html></html>"));
  out_links.push_back(std::make_shared<WebPage>("http://www.google.com/test/1", "<html></html>"));
  out_links.push_back(std::make_shared<WebPage>("http://www.google.com/test/2", "<html></html>"));

  auto expanded_ids = graph.ExpendNode(0, out_links);
  ASSERT_EQ(expanded_ids.size(), 3);

  auto node = graph.GetNode(1);
  EXPECT_EQ(node->GetPage()->GetURL(), "http://www.google.com/test");
}

TEST_F(CrawlGraphTest, TestGetRootPage) {
  CrawlGraph graph;
  auto root_page = std::make_shared<WebPage>(root_url_, default_html_);
  graph.Init(root_page);

  auto out_links = std::vector<WebPage_ptr>();
  out_links.push_back(std::make_shared<WebPage>("http://www.google.com/test", "<html></html>"));
  out_links.push_back(std::make_shared<WebPage>("http://www.google.com/test/1", "<html></html>"));
  out_links.push_back(std::make_shared<WebPage>("http://www.google.com/test/2", "<html></html>"));

  auto expanded_ids = graph.ExpendNode(0, out_links);
  ASSERT_EQ(expanded_ids.size(), 3);

  auto root_page_ptr = graph.GetRootPage();
  EXPECT_NE(root_page_ptr, nullptr);
  EXPECT_EQ(root_page_ptr->GetURL(), root_url_);
  EXPECT_EQ(root_page_ptr->GetHTMLText(), default_html_);
}

TEST_F(CrawlGraphTest, TestGetRootID) {
  CrawlGraph graph;
  auto root_page = std::make_shared<WebPage>(root_url_, default_html_);
  graph.Init(root_page);

  auto out_links = std::vector<WebPage_ptr>();
  out_links.push_back(std::make_shared<WebPage>("http://www.google.com/test", "<html></html>"));
  out_links.push_back(std::make_shared<WebPage>("http://www.google.com/test/1", "<html></html>"));
  out_links.push_back(std::make_shared<WebPage>("http://www.google.com/test/2", "<html></html>"));

  auto expanded_ids = graph.ExpendNode(0, out_links);
  ASSERT_EQ(expanded_ids.size(), 3);

  EXPECT_EQ(graph.GetRootID(), 0);
}
