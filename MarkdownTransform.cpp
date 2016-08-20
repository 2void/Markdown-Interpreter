#include "MarkdownTransform.h"

template<typename T>
void destroy(T * v) {
    for (int i = 0; i < (int)v->ch.size(); ++i) {
        destroy(v->ch[i]);
    }
    delete v;
}