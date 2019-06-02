#include "changemodetest.h"
#include "coordinate.h"

ChangeModeTest::ChangeModeTest() : TestRunner("ChangeModeTest") {
        stickman = std::make_unique<FreeStickman>(50);
        stickman->setSprite(":sprites/sprite0.png");
        stickman->setCoordinate(Coordinate(50, 50, 450));
        stickman->setSize("normal");
    }

void ChangeModeTest::update() {
    if (counter > 500) stickman->setMode("large");
    if (stickman->getMode() == "large") {
        status = Status::Passed;
    }
}

void ChangeModeTest::render(Renderer &renderer) {
    stickman->render(renderer, counter++);
}
