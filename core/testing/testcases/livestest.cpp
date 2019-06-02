#include "livestest.h"
#include "coordinate.h"

LivesTest::LivesTest() : TestRunner("LivesTest") {
    stickman = std::make_unique<FreeStickman>(50);
    stickman->setSprite(":sprites/sprite0.png");
    stickman->setCoordinate(Coordinate(50, 50, 450));
    stickman->setSize("normal");

    stickman->setNumLives(2);

    obstacles.push_back(std::move(std::make_unique<Bird>(Coordinate(400, 50, 450), 2)));
}

void LivesTest::update() {
    stickman->update(obstacles);
    if (stickman->isColliding()) {
        stickman->setNumLives(stickman->getNumLives() - 1);
    }
    if (stickman->getNumLives() == 1) status = Status::Passed;
    obstacles[0]->collisionLogic(*stickman);
}

void LivesTest::render(Renderer &renderer) {
    stickman->render(renderer, counter++);
    obstacles[0]->render(renderer, counter);
}
