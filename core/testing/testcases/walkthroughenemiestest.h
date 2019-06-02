#ifndef WALKTHROUGHENEMIESTEST_H
#define WALKTHROUGHENEMIESTEST_H

#include "freestickman.h"
#include "testrunner.h"
#include "entity.h"

class WalkThroughEnemiesTest : public TestRunner {
public:
    WalkThroughEnemiesTest();
    ~WalkThroughEnemiesTest() = default;

    void update();
    void render(Renderer &renderer);

private:
    int counter;
    std::unique_ptr<FreeStickman> stickman;
    std::vector<std::unique_ptr<Entity>> obstacles;
};


#endif // WALKTHROUGHENEMIESTEST_H
