//
// Created by rcastill on 12/25/15.
//

#include "Resource.h"

Resource::Resource(string path) :
    path(path),
    refCount(1)
{
}

Resource::~Resource()
{
}

void Resource::setGraphicsEngine(GraphicsEngine *engine)
{
    gfx = engine;
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

ResourceVector::size_type Resource::id() const
{
    return resId;
}
