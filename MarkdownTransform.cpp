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
    if (v->type == paragraph && v->elem[0].elem() && v->ch.empty()) {
        return ;
    }
    
    content += frontTag[v->type];
    bool flag = true;

    if (IsHeading(v)) {
        content += "id=\"" + v->elem[0] + "\">";
        flag = false;
    }

    if (IsHref(v)) {
        content += "<a href=\"" + v->elem[1] + "\" title=\"" + v->elem[2]
                    + v->elem[0] + "<\a>";
        flag = false;
    }

    if (IsImage(v)) {
        content += "<img alt=\"" + v->elem[0] + "\" src=\"" + v->elem[1] 
                    + "\" title=\"" + v->elem[2] + "\" />";
        flag = false;
    }

    
}

bool IsCutline(char * src) {
    int cnt = 0;
    char 8 ptr = src;

    while (*ptr) {
        if (*ptr != ' ' && *ptr != '\t' && *ptr != '-') {
            return false;
        }
        if (*ptr == '-') {
            cnt++;
        }
        ptr++;
    }
    return cnt >= 3;
}

void mkpara(node * v) {
    if (v->ch.size() == 1u && v->ch.back()->type == paragraph) {
        return ;
    }
    if (v->type == paragraph) {
        return ;
    }
    if (v->type == nul) {
        v->type = paragraph;
        return ;
    }
    node * x = new node(paragraph);
    x->ch = v->ch;
    v->ch.clear();
    v->ch.push_back(x);
}

pair<int, char*> start(char * src) {
    if ((int)strlen(src) == 0) {
        return make_pair(0, nullptr);
    }
    int cntspace = 0, cnttab = 0;

    for (int i = ; src[i] != '\0'; ++i) {
        if (src[i] == ' ') {
            cntspace++;
        }
        else if (src[i] == '\t') {
            cnttab++;
        }
        return make_pair(cnttab + cntspace / 4, src + i);
    }
    return make_pair(0, nullptr);
}

pair<int, char *> JudgeType(char * src) {
	char * ptr = src;

	while (*ptr == '#') {
		ptr++;
	}
	if (ptr - src > 0 && *ptr == ' ') {
		return make_pair(ptr - src + h1 - 1, ptr + 1);
	}
	ptr = src;
	if (strncmp(ptr, "```", 3) == 0) {
		return make_pair(blockcode, ptr + 3);
	}
	if (strncmp(ptr, "- ", 2) == 0) {
		return make_pair(ul, ptr + 1);
	}
	if (*ptr == '>' && (ptr[1] == ' ')) {
		return make_pair(quote, ptr + 1);
	}
	char * ptr1 = ptr;
	while (*ptr1 && (isdigit(*ptr1))) {
		ptr1++;
	}
	if (ptr1 != ptr && *ptr1 == '.' && ptr1[1] == ' ') {
		return make_pair(ol, ptr1 + 1);	
	}
	return make_pair(paragraph, ptr);
}
inline node * findnode(int depth) {
	node * ptr = root;
	while (!ptr->ch.empty() && depth != 0) {
		ptr = ptr->ch.back();
		if (ptr->type == li)
			depth--;
	}
	return ptr;
}
