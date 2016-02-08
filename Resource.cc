//
// Created by rcastill on 12/25/15.
//

#include "Resource.h"
#include "GraphicsEngine.h"

#include <iostream>

Resource::Resource(string path) :
    path(path),
    refCount(1),
    resUnique(false)
{
    cout << "Resource(" << path << ")" << endl;
}

Resource::~Resource()
{
    cout << "~Resource(" << path << ")" <<  endl;
}


void Resource::retain()
{
    refCount++;
}

void Resource::dispose()
{
    gfx->disposeResource(this);
}

bool Resource::unique() const
{
    return resUnique;
}

void Resource::unique(bool unique)
{
    resUnique = unique;
}

string Resource::getPath() const
{
    return path;
}

void Resource::id(ResourceVector::size_type id)
{
    resId = id;
}

size_t Resource::id() const
{
    return resId;
}
