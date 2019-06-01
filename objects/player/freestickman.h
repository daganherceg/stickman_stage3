#ifndef FREESTICKMAN_H
#define FREESTICKMAN_H

#include "jumpingstickman.h"
#include "entity.h"
#include "stickman.h"

class FreeStickman : public JumpingStickman
{
public:
    FreeStickman(int floor, int jumpImpulse = 15, int maxJumpCount = 2, int gravity = -1);
    ~FreeStickman();

    void update(std::vector<std::unique_ptr<Entity>> &obstacles);
};


#endif // FREESTICKMAN_H
