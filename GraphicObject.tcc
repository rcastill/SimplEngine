template <typename ObjectType, typename... Args>
ObjectType *GraphicObject::addChild(Args... args)
{
    children.push_back(make_shared<ObjectType>(args...));
    return static_cast<ObjectType*>(children.back().get());
}