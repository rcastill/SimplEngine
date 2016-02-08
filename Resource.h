//
// Created by rcastill on 12/25/15.
//

#ifndef PROJECT_STRAT_RESOURCE_H
#define PROJECT_STRAT_RESOURCE_H

//#include "GraphicsEngine.h"
#include <memory>
#include <string>
#include <vector>

using namespace std;

class GraphicsEngine;
class Resource;
typedef vector<shared_ptr<Resource>> ResourceVector;

class Resource
{
public:
    Resource(string path);
    virtual ~Resource();

    void retain();
    void dispose();

    bool unique() const;
    void unique(bool unique);

    string getPath() const;

    void id(ResourceVector::size_type id);
    size_t id() const;

private:
    friend class GraphicsEngine;

    string path;
    int refCount;
    bool resUnique;
    size_t resId;

protected:
    GraphicsEngine *gfx;
};


#endif //PROJECT_STRAT_RESOURCE_H
