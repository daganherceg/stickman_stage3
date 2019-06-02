#ifndef STICKMAN_H
#define STICKMAN_H

#include "gameobject.h"
#include "coordinate.h"
#include "renderer.h"
#include <string>
#include <QPainter>
#include <QKeyEvent>
#include <vector>
#include <memory>

class Entity;
class Stickman : public GameObject {
public:
    Stickman() = default;
    virtual ~Stickman();

    void setCoordinate(Coordinate coordinate);

    void setSize(std::string size);

    void setSprite(std::string path);

    // TODO these were not here
    virtual void setMode(std::string mode);
    std::string getMode();

    Coordinate &getCoordinate();

    void render(Renderer &renderer, unsigned int time);

    virtual void handleInput(QKeyEvent &event);
    virtual void update(std::vector<std::unique_ptr<Entity>> &obstacles);

    // TODO This should not be here
    virtual int getNumLives() { return lives; }
    virtual void setNumLives(int lives) { this->lives = lives; }

    bool isColliding();
    int width();
    int height();

protected:
    bool colliding;
    Coordinate coordinate;
    std::string size;
    QPixmap sprite;
    int lives;
    std::string mode;
};

#endif // STICKMAN_H
