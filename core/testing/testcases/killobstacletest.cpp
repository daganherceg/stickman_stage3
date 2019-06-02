#include "killobstacletest.h"
#include "coordinate.h"

KillObstacleTest::KillObstacleTest() : TestRunner("KillObstacleTest") {
    stickman = std::make_unique<FreeStickman>(50);
    stickman->setSprite(":sprites/sprite0.png");
    stickman->setCoordinate(Coordinate(50, 50, 450));
    stickman->setSize("normal");
    stickman->setNumLives(2);

    obstacles.push_back(std::move(std::make_unique<Bird>(Coordinate(400, 50, 450), 2)));
}

void KillObstacleTest::update() {
    stickman->update(obstacles);
    if (obstacles[0]->getCoordinate().getXCoordinate() == stickman->getCoordinate().getXCoordinate() + 100) {
        stickman->jump();
    }
    if (obstacles[0]->height() == 0) {
        status = Status::Passed;
    }
    obstacles[0]->collisionLogic(*stickman);
}

void KillObstacleTest::render(Renderer &renderer) {
    stickman->render(renderer, counter++);
    obstacles[0]->render(renderer, counter);
}
