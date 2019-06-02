#ifndef LIVESTEST_H
#define LIVESTEST_H

#include "testrunner.h"
#include "freestickman.h"
#include "entity.h"

class LivesTest : public TestRunner {
    public:
        LivesTest();
        ~LivesTest() = default;

        void update();
        void render(Renderer &renderer);

    private:
        int counter;
        std::unique_ptr<FreeStickman> stickman;
        std::vector<std::unique_ptr<Entity>> obstacles;
    };

#endif // LIVESTEST_H
