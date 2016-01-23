#include "GraphicsEngine.h"
#include "Game.h"

int main()
{
    GraphicsEngine gfxEngine("GFX SDL2 Engine", 800, 600);
    gfxEngine.setLoopDelay(2);
    gfxEngine.setRenderColor(Color::WHITE);
    gfxEngine.addObject<Game>();
    gfxEngine.openWindow();
    gfxEngine.mainloop();
    return 0;
}