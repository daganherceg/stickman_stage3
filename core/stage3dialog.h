#ifndef STAGE3DIALOG_H
#define STAGE3DIALOG_H

#include "stage2dialog.h"
#include "freestickman.h"

#include <QCoreApplication>


class Stage3Dialog : public Stage2Dialog
{
public:
    Stage3Dialog(Game &game, std::unique_ptr<Stickman> stickman, std::unique_ptr<EntityFactory> factory, std::vector<std::pair<std::unique_ptr<Entity>, int>> obstacleLayout);

protected:
    void input(QKeyEvent &event);
    void released(QKeyEvent &event);

    void handleMovement(QKeyEvent &event);
    void update();
    void speedUp(unsigned int counter);

    void render(Renderer &renderer);
    void renderObstacles(Renderer &renderer, unsigned int counter);
    void spawnObstacles(unsigned int counter);



private:
    // HELPER Functions
    void moveRight();
    void moveLeft();
    void leftBoundaryCollision();
    void rightBoundaryCollision();
    void nextLevel();
    void win();
    void lose();
    void resetLevel();
    void removeObstacles();
    void reward(std::unique_ptr<Entity> obstacle);


    int constantVelocity;
    int currentLevel;
    int maxLevel;
    bool levelComplete;
    int playerVelocity;
    int obstacleVelocity;
    unsigned int savedScore;
};
#endif // STAGE3DIALOG_H
