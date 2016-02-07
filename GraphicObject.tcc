#include "GraphicsEngine.h"

template <typename ObjectType, typename... Args>
ObjectType *GraphicObject::addChild(Args... args)
{
    assert(gfx);
    children.push_back(make_shared<ObjectType>(args...));
    gfx->addToInitQueue(children.back());
    return static_cast<ObjectType*>(children.back().get());
}