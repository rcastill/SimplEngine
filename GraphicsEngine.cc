#include "GraphicsEngine.h"

#include "Texture.h"

GraphicsEngine::GraphicsEngine(string title, int width, int height) :
    windowTitle(title),
    windowWidth(width),
    windowHeight(height),
    running(true)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw runtime_error(IMG_GetError());

    SDL_Window *tmpWindow = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width, height,
            SDL_WINDOW_HIDDEN
    );

    if (tmpWindow == 0)
        throw runtime_error(SDL_GetError());

    sdlWindow.get_deleter() = [](SDL_Window *w) { SDL_DestroyWindow(w); };
    sdlWindow.reset(tmpWindow);

    SDL_Renderer *tmpRenderer = SDL_CreateRenderer(sdlWindow.get(), -1, SDL_RENDERER_ACCELERATED);

    if (tmpRenderer == 0)
        throw runtime_error(SDL_GetError());

    sdlRenderer.get_deleter() = [](SDL_Renderer *r) { SDL_DestroyRenderer(r); };
    sdlRenderer.reset(tmpRenderer);
}

GraphicsEngine::~GraphicsEngine()
{
    SDL_Quit();
}

void GraphicsEngine::openWindow()
{
    SDL_ShowWindow(sdlWindow.get());
}


void GraphicsEngine::delay(int msecs)
{
    SDL_Delay((Uint32) msecs);
}

void GraphicsEngine::setRenderColor(Color color)
{
    SDL_SetRenderDrawColor(
            sdlRenderer.get(),
            color.r(),
            color.g(),
            color.b(),
            color.a()
    );
}

int GraphicsEngine::width() const
{
    return windowWidth;
}

int GraphicsEngine::height() const
{
    return windowHeight;
}

void GraphicsEngine::setLoopDelay(int loopDelay)
{
    this->loopDelay = loopDelay;
}

void GraphicsEngine::mainloop()
{
    for (int i = 0; i < gfxObjects.size(); i++) {
        gfxObjects[i]->setGraphicsEngine(this);
        gfxObjects[i]->init();
    }

    SDL_Event event;

    while (running) {
        SDL_RenderClear(sdlRenderer.get());

        while (SDL_PollEvent(&event) != 0) {
            for (auto object : gfxObjects) {
                object->update(event);
            }
        }

        for (auto object : gfxObjects) {
            object->render();
        }

        SDL_RenderPresent(sdlRenderer.get());
        SDL_Delay((Uint32) loopDelay);
    }
}

void GraphicsEngine::disposeResource(Resource *resource)
{
    if (--(resource->refCount) == 0) {
        availableResIds.push_back(resource->id());
        resources[resource->id()] = 0;
    }
}

Texture *GraphicsEngine::loadTexture(string path)
{
    for (auto &resource : resources) {
        if (resource && resource->getPath() == path) {
            if (resource->unique())
                break;

            Resource *rawResource = resource.get();
            Texture *texture = dynamic_cast<Texture*>(rawResource);

            if (texture != NULL) {
                resource->retain();
                return texture;
            }

            break;
        }
    }

    SDL_Texture *sdlTexture = 0;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL)
        return 0;

    sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer.get(), loadedSurface);

    if (sdlTexture == NULL)
        return 0;

    SDL_FreeSurface(loadedSurface);

    auto texture = makeTexture(path, sdlTexture);

    ResourceVector::size_type id;
    if (!availableResIds.empty()) {
        id = availableResIds.back();
        availableResIds.pop_back();
        texture->id(id);
        resources[id] = texture;

    } else {
        id = resources.size();
        resources.push_back(texture);
    }

    return texture.get();
}

void GraphicsEngine::renderTexture(Texture *texture, SDL_Rect dstrect)
{
    SDL_RenderCopy(sdlRenderer.get(),
                   texture->sdlTexture.get(),
                   (texture->fullSource) ? 0 : &(texture->srcrect),
                   &dstrect);
}

void GraphicsEngine::renderTexture(Texture *texture, int x, int y, int w, int h)
{
    SDL_Rect dstrect = {x, y, w, h};
    renderTexture(texture, dstrect);
}

void GraphicsEngine::renderTexture(Texture *texture, int x, int y)
{
    int w, h;
    texture->getSize(w, h);
    renderTexture(texture, x, y, w, h);
}

void GraphicsEngine::size(int &w, int &h) const
{
    w = windowWidth;
    h = windowHeight;
}

shared_ptr<Texture> GraphicsEngine::makeTexture(string path, SDL_Texture *raw)
{
    auto texture = make_shared<Texture>(path);
    texture->sdlTexture.reset(raw);
    texture->updateInfo();
    return texture;
}

void GraphicsEngine::stop()
{
    running = false;
}
