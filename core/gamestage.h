#ifndef GAMESTAGE_H
#define GAMESTAGE_H

#include <QKeyEvent>
#include <QPainter>
#include "renderer.h"

class GameStage {
public:
    GameStage() = default;
    virtual ~GameStage() = 0;

    virtual void update();
    virtual void render(Renderer &renderer);
    virtual void input(QKeyEvent &event);
    virtual void released(QKeyEvent &event) {} // TODO Added
};

#endif // GAMESTAGE_H
