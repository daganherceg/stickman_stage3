#ifndef STAGE3DIALOG_H
#define STAGE3DIALOG_H

#include "stage2dialog.h"

class Stage3Dialog : public Stage2Dialog
{
public:
    Stage3Dialog(Game &game, std::unique_ptr<Stickman> stickman, std::unique_ptr<EntityFactory> factory, std::vector<std::pair<std::unique_ptr<Entity>, int>> obstacleLayout);

protected:
    void input(QKeyEvent &event);
    void released(QKeyEvent &event);

    void handleMovement(QKeyEvent &event);
    void update();

    void render(Renderer &renderer);
    void renderObstacles(Renderer &renderer, unsigned int counter);

    // TODO Overwrite the speedup function
private:
    int constantVelocity;
    int currentLevel;
    bool levelComplete;
    int maxLevel;
};
#endif // STAGE3DIALOG_H
