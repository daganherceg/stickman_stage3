#ifndef CHANGEMODETEST_H
#define CHANGEMODETEST_H

#include "testrunner.h"
#include "freestickman.h"
#include "entity.h"

class ChangeModeTest : public TestRunner {
public:
    ChangeModeTest();
    ~ChangeModeTest() = default;

    void update();
    void render(Renderer &renderer);

private:
    int counter;
    std::unique_ptr<FreeStickman> stickman;
    std::vector<std::unique_ptr<Entity>> obstacles;
};

#endif // CHANGEMODETEST_H
