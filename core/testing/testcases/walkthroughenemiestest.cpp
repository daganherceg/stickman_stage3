#include "walkthroughenemiestest.h"

#include <iostream>

WalkThroughEnemiesTest::WalkThroughEnemiesTest() : TestRunner ("WalkThroughEnemiesTest") {
    stickman = std::make_unique<FreeStickman>(50);
    stickman->setSprite(":sprites/sprite0.png");
    stickman->setCoordinate(Coordinate(50, 50, 450));
    stickman->setMode("giant");

    obstacles.push_back(std::move(std::make_unique<Bird>(Coordinate(400, 50, 450), 2)));
}

void WalkThroughEnemiesTest::update() {
    stickman->update(obstacles);
    if (obstacles[0]->height() == 0) {
        status = Status::Passed;
    }
    obstacles[0]->collisionLogic(*stickman);
    stickman->update(obstacles);
}

void WalkThroughEnemiesTest::render(Renderer &renderer) {
    stickman->render(renderer, counter++);
    obstacles[0]->render(renderer, counter);
}
