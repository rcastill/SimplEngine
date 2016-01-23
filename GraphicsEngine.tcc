template <typename ObjectType, typename... Args>
ObjectType *GraphicsEngine::addObject(Args... args)
{
    gfxObjects.push_back(make_shared<ObjectType>(args...));
    return static_cast<ObjectType*>(gfxObjects.back().get());
}