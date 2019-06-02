#ifndef KILLOBSTACLESTEST_H
#define KILLOBSTACLESTEST_H

#include "testrunner.h"
#include "freestickman.h"
#include "entity.h"

class KillObstacleTest : public TestRunner {
    public:
        KillObstacleTest();
        ~KillObstacleTest() = default;

        void update();
        void render(Renderer &renderer);

    private:
        int counter;
        std::unique_ptr<FreeStickman> stickman;
        std::vector<std::unique_ptr<Entity>> obstacles;
    };

#endif // KILLOBSTACLESTEST_H
