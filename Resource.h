//
// Created by rcastill on 12/25/15.
//

#ifndef PROJECT_STRAT_RESOURCE_H
#define PROJECT_STRAT_RESOURCE_H

#include "GraphicsEngine.h"
#include <memory>
#include <string>

using namespace std;

class Resource;
typedef vector<shared_ptr<Resource>> ResourceVector;

class Resource
{
public:
    Resource(string path);
    virtual ~Resource();

    void retain();
    void dispose();

    void setGraphicsEngine(GraphicsEngine *gfx);

    bool unique() const;
    void unique(bool unique);

    string getPath() const;

    void id(ResourceVector::size_type id);
    ResourceVector::size_type id() const;

private:
    friend class GraphicsEngine;

    string path;
    int refCount;
    bool resUnique;
    ResourceVector::size_type resId;

protected:
    GraphicsEngine *gfx;
};


#endif //PROJECT_STRAT_RESOURCE_H
