#ifndef FREESTICKMAN_H
#define FREESTICKMAN_H

#include "jumpingstickman.h"
#include "entity.h"
#include "stickman.h"

class FreeStickman : public JumpingStickman
{
public:
    /**
     * @brief FreeStickman An extension of the JumpingStickman class which adds adds the functionality of killing enemies
     * @param floor The y position which is considered the floor (i.e. will stop falling at)
     * @param jumpImpulse The vertical velocity applied when jumping
     * @param maxJumpCount The maximum amount of jumps that can be peformed mid-air (including the initial jump)
     * @param gravity The falling rate
     */
    FreeStickman(int floor, int jumpImpulse = 15, int maxJumpCount = 2, int gravity = -1);
    ~FreeStickman() override;

    // toggles the mode / size of the stickman
    void setMode(std::string mode) override;
    void update(std::vector<std::unique_ptr<Entity>> &obstacles) override;
};


#endif // FREESTICKMAN_H
