#ifndef STAGE3COLLISIONTEST_H
#define STAGE3COLLISIONTEST_H

#include "freestickman.h"
#include "testrunner.h"
#include "entity.h"

class Stage3CollisionTest : public TestRunner {
public:
    Stage3CollisionTest();
    ~Stage3CollisionTest() = default;

    void update();
    void render(Renderer &renderer);

private:
    int counter;
    std::unique_ptr<FreeStickman> stickman;
    std::vector<std::unique_ptr<Entity>> obstacles;
};

#endif // STAGE3COLLISIONTEST_H
