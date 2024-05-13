#pragma once

#include "libcrawl/defs.h"

namespace libcrawl {

class WebPage {
 public:
  WebPage(const URL& url, const HTMLText& html_text) : url_(url), html_text_(html_text){};
  URL GetURL() const { return url_; };
  HTMLText GetHTMLText() const { return html_text_; };
  void SetHTMLText(const HTMLText& html_text) { html_text_ = html_text; }
  void AppendHTMLText(const HTMLText& html_text) { html_text_ += html_text; }

  void AddLink(const Link& link) { out_links_.push_back(link); }
  Links GetLinks() const { return out_links_; }

 private:
  URL url_;
  HTMLText html_text_;
  Links out_links_;
};

}  // namespace libcrawl