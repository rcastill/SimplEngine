//
// Created by rcastill on 1/23/16.
//

#ifndef PROJECT_STRAT_BUTTON_H
#define PROJECT_STRAT_BUTTON_H


#include "GraphicObject.h"
#include "ButtonMaster.h"
#include "Font.h"
#include "Texture.h"
#include "Color.h"
#include "Renderer.h"
#include <string>

using namespace std;

class Game;

class SimpleButton : public GraphicObject
{
public:
    SimpleButton(ButtonMaster *master, string text);
    ~SimpleButton();

    void init();
    void onMouseMotion(int x, int y);
    void onMouseLeftReleased(int x, int y);
    void render(Renderer &renderer);

    bool inside(int x, int y);

    int x, y;

private:
    ButtonMaster *master;
    Font *cantarellRegular;
    string text;
    Texture *normalTexture;
    Texture *hoverTexture;
    Texture *activeTexture;
};


#endif //PROJECT_STRAT_BUTTON_H
