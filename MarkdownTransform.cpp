#include "MarkdownTransform.h"

template<typename T>
void destroy(T * v) {
    for (int i = 0; i < (int)v->ch.size(); ++i) {
        destroy(v->ch[i]);
    }
    delete v;
}

void Cdfs(Cnode * v, string index) {
    TOC += "<li>\n";
    TOC += "<a href=\"#" + v->tag + "\">" + index
            + " " + v->heading + "</a>\n";
    int n = (int)v->ch.size();
    if (n) {
        TOC += "<ul\n";
        for (int i = 0; i < n; ++i) {
            Cdfs(v->ch[i], index + to_string(i + 1) + ".");
        }
        TOC += "</ul>\n";
    }
    TOC += "</li>\n";
}

void Cins(Cnode * v, int x, const string &  hd, int tag) {
    int n = (int)v->ch.size();
    if (x == 1) {
        v->ch.push_back(new Cnode(hd));
        v->ch.back()->tag = "tag" + to_string(tag);
        return ;
    }

    if (!n || v->ch.back()->heading.empty()) {
        v->ch.push_back(new Cnode(""));
    }
    Cins(v->ch.back(), x - 1, hd, tag);
}

void dfs(node * v) {
    
}