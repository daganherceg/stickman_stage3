#ifndef STAGE3DIALOG_H
#define STAGE3DIALOG_H

#include "stage2dialog.h"
#include "freestickman.h"

#include <QCoreApplication>


class Stage3Dialog : public Stage2Dialog
{
public:
    /**
     * @brief Stage3Dialog which builds upon Stage2Dialog
     * @param game The container of the dialog
     * @param stickman The player's stickman object
     * @param factory An entity factory for producing obstacles
     * @param obstacleLayout Pairs of (obstacle, space_until_next_obstacle) describing the sequence in which obstacles will be spawned
     */
    Stage3Dialog(Game &game, std::unique_ptr<Stickman> stickman, std::unique_ptr<EntityFactory> factory, std::vector<std::pair<std::unique_ptr<Entity>, int>> obstacleLayout);

    int constantVelocity;
    int currentLevel;
    int maxLevel;
    bool levelComplete;
    int playerVelocity;
    int obstacleVelocity;
    unsigned int savedScore;

protected:
    void input(QKeyEvent &event);
    void released(QKeyEvent &event);

    void handleMovement(QKeyEvent &event);
    void update();
    void speedUp(unsigned int counter);

    void render(Renderer &renderer);
    void renderObstacles(Renderer &renderer, unsigned int counter);
    void spawnObstacles(unsigned int counter);

    // HELPER Functions (Separated here in anticipation of moving this functionality away from Dialog)
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
};
#endif // STAGE3DIALOG_H
