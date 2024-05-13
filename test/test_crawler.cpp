#include "libcrawl/crawler/crawler.h"

#include <gtest/gtest.h>
#include <iostream>

using namespace libcrawl;

class CrawlerTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

static const std::string kTestURL = "http://www.google.com";

TEST_F(CrawlerTest, TestInit) {
  Crawler crawler;
  crawler.Init(kTestURL, 2);
  auto graph = crawler.GetGraph();
  EXPECT_EQ(graph.GetRootID(), 0);

  auto root_page = graph.GetRootPage();
  EXPECT_EQ(root_page->GetURL(), kTestURL);

  std::cout << root_page->GetHTMLText() << std::endl;
}

TEST_F(CrawlerTest, TestCrawl) {
  Crawler crawler;
  crawler.Init(kTestURL, 2);
  crawler.Crawl();
  auto graph = crawler.GetGraph();
  auto root_page = graph.GetRootPage();
  std::cout << "root page url:" << root_page->GetURL() << std::endl;

  graph.TreePrint();
}