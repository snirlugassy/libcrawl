#include <gtest/gtest.h>
#include "libcrawl/processor/page_link_processor.h"

using namespace libcrawl;

TEST(PageLinkProcessorTest, Process) {
  std::string content = R"(
    <html>
      <head>
        <title>Test Page</title>
      </head>
      <body>
        <a href="http://example.com">Example</a>
        <a href="http://example.com/test">Example Test</a>
        <a href="http://example.com/test/1">Example Test 1</a>
      </body>
    </html>
  )";

  Links links = PageLinkProcessor::Process(content);
  ASSERT_EQ(links.size(), 3);
  EXPECT_EQ(links[0], "http://example.com");
  EXPECT_EQ(links[1], "http://example.com/test");
  EXPECT_EQ(links[2], "http://example.com/test/1");
}
