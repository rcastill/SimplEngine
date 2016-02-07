//
// Created by rcastill on 1/31/16.
//

#ifndef PROJECT_STRAT_FIGHTER_H
#define PROJECT_STRAT_FIGHTER_H

#include "GraphicObject.h"
#include "Position.h"
#include "Bullet.h"

class GameScene;

class Fighter : public GraphicObject
{
public:
    Fighter(GameScene *gameScene, string username);

    void init();
    void onKeyReleased(SDL_Keycode key);
    void onMouseLeftReleased(int x, int y);
    void continuousUpdate(const Uint8 *keyboardPressed, MouseState mouseState);
    void render(Renderer &renderer);

    Position pos;

private:
    GameScene *gameScene;
    bool follow;

    Texture *asset;
    string usernameText;
    Font *cantarellRegular;

    Texture *usernameTexture;
    Texture *angleTexture;
};


#endif //PROJECT_STRAT_FIGHTER_H
