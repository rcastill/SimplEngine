#include <iostream>
#include "GraphicsEngine.h"
#include "Game.h"

int main()
{
    /*
     * RAII System Init
     * Dummy stack variable that ensures systems are the first
     * being initialized and the LAST being destroyed. This measure
     * was taken to fix crashes of SDL2_ttf library. They were caused
     * because fonts were destroyed after library's system was quitted.
     * Other libraries (i.e. SDL2 and SDL2_image) did not issued the
     * problem, still they were wrapped in RAII System Init.
     */
    auto RAIISystemInit = GraphicsEngine::SDL2Systems();
    GraphicsEngine gfxEngine("GFX SDL2 Engine", 800, 600);
    gfxEngine.setLoopDelay(2);
    gfxEngine.setRenderColor(Color::WHITE);
    gfxEngine.addObject<Game>();
    gfxEngine.openWindow();
    gfxEngine.mainloop();
    return 0;
}