#include "libcrawl/defs.h"
#include "libcrawl/page/web_page.h"

#include <gtest/gtest.h>
#include <iostream>

using namespace libcrawl;

class WebPageTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
  URL url_ = "http://www.google.com";
  HTMLText default_html_ = "<html></html>";
};

TEST_F(WebPageTest, TestInit) {
  WebPage page(url_, default_html_);
  EXPECT_EQ(page.GetURL(), url_);
  EXPECT_EQ(page.GetHTMLText(), default_html_);
}

TEST_F(WebPageTest, TestAddLink) {
  WebPage page(url_, default_html_);
  page.AddLink("http://www.google.com/test");
  page.AddLink("http://www.google.com/test/1");
  page.AddLink("http://www.google.com/test/2");
  Links links = page.GetLinks();
  ASSERT_EQ(links.size(), 3);
  EXPECT_EQ(links[0], "http://www.google.com/test");
  EXPECT_EQ(links[1], "http://www.google.com/test/1");
  EXPECT_EQ(links[2], "http://www.google.com/test/2");
}

TEST_F(WebPageTest, TestSetHTMLText) {
  WebPage page(url_, default_html_);
  page.SetHTMLText("<html><body></body></html>");
  EXPECT_EQ(page.GetHTMLText(), "<html><body></body></html>");
}

TEST_F(WebPageTest, TestAppendHTMLText) {
  WebPage page(url_, default_html_);
  page.AppendHTMLText("<body></body>");
  EXPECT_EQ(page.GetHTMLText(), "<html></html><body></body>");
}

TEST_F(WebPageTest, TestGetLinks) {
  WebPage page(url_, default_html_);
  Links links = page.GetLinks();
  EXPECT_TRUE(links.empty());
}

TEST_F(WebPageTest, TestGetURL) {
  WebPage page(url_, default_html_);
  EXPECT_EQ(page.GetURL(), url_);
}

TEST_F(WebPageTest, TestGetHTMLText) {
  WebPage page(url_, default_html_);
  EXPECT_EQ(page.GetHTMLText(), default_html_);
}
