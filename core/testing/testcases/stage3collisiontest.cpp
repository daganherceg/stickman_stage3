#include "stage3collisiontest.h"

Stage3CollisionTest::Stage3CollisionTest() : TestRunner ("Stage3CollisionTest") {
    stickman = std::make_unique<FreeStickman>(50);
    stickman->setSprite(":sprites/sprite0.png");
    stickman->setCoordinate(Coordinate(50, 50, 450));
    stickman->setSize("normal");

    obstacles.push_back(std::move(std::make_unique<Bird>(Coordinate(400, 50, 450), 2)));
}

void Stage3CollisionTest::update() {
    stickman->update(obstacles);
    if (stickman->isColliding()) {
        status = Status::Passed;
    }
    obstacles[0]->collisionLogic(*stickman);
}

void Stage3CollisionTest::render(Renderer &renderer) {
    stickman->render(renderer, counter++);
    obstacles[0]->render(renderer, counter);
}
