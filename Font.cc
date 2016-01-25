//
// Created by rcastill on 1/23/16.
//

#include "Font.h"

#include <iostream>

Font::Font(string path, int fontSize) :
    Resource(path),
    fontSize(fontSize),
    ttfFont(TTF_OpenFont(path.c_str(), fontSize),
            [](TTF_Font *f) { TTF_CloseFont(f); })
{
    if (!ttfFont)
        throw runtime_error(TTF_GetError());
}

Font::operator bool()
{
    return (ttfFont) ? true : false;
}
