#ifndef MarkdownTransform_H_
#define MarkdownTransform_H_

#include <string>

enum {
    maxLength = 10000,
    nul = 0,
    paragraph = 1,
    href = 2,
    ul = 3,
    ol = 4,
    li = 5,
    em = 6,
    strong = 7,
    hr = 8,
    br = 9,
    image = 10,
    quote = 11,
    h1 = 12,
    h2 = 13,
    h3 = 14,
    h4 = 15,
    h5 = 16,
    h6 = 17,
    blockcode = 18,
    code = 19
};

const std::string frontTag[] = {
    "", "<p>", "", "<ul>", "<ol>", "<li>", "<em>", "<strong>",
    "<hr color=#CCCCCC size=1 />", "<br />",
    "", "<blockquote>",
    "<h1 ", "<h2 ", "<h3 ", "<h4 ", "<h5 ", "<h6 ",
    "<pre><code>", "<code>"
};

class MarkdownTransform {
private:
    std::string content, TOC;
public:
    MarkdownTransform(const std::string & filename);

    std::string getTableOfContents() { return TOC; }

    std::string getContents() { return content; }

    ~MarkdownTransform();
};

#endif;