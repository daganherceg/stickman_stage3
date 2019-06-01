#include "freestickman.h"
#include "collision.h"
#include "score.h"

#include <iostream>
#include <algorithm>

FreeStickman::FreeStickman(int floor, int jumpImpulse, int maxJumpCount, int gravity) :
    JumpingStickman(floor, jumpImpulse, jumpVelocity, gravity)  {

}

FreeStickman::~FreeStickman() {

}

void FreeStickman::update(std::vector<std::unique_ptr<Entity>> &obstacles) {
    // TODO use a visitor here

    Coordinate &ac = getCoordinate();
    int newY = ac.getYCoordinate() + jumpVelocity;
    colliding = false;

    // Check for collisions
    for (auto &other : obstacles) {
        Collision::CollisonResult col = Collision::moveCast(*this, *other, 0, jumpVelocity);

        if (col.overlapped) {
            int by = other->getCoordinate().getYCoordinate();
            if (col.down && jumpVelocity < 0 && other->height() > 1) {
                // Hitting obstacle from above
                jumpVelocity = 0;
                grounded = true;
                jumpCount = 0;
                newY = by + other->height() + 1;



                // Automatically jumping when hitting obstacle
                jump();

                // TODO Separate entity change from game change
                other->setSize(0, 0);
                other->setVelocity(1000);

                // END TODO

                // Swap collision element with first element (ensure collision element deleted)
                std::vector<std::unique_ptr<Entity>>::iterator it = std::find(obstacles.begin(), obstacles.end(), other);
                int index = std::distance(obstacles.begin(), it);
                if (index > 0) {
                    std::iter_swap(obstacles.begin(), obstacles.begin() + index);
                }

            } else if (col.up && other->height() > 1) {
                // Hitting obstacle from below
                jumpVelocity = 0;
                newY = by - height() - 1;
            } else if (other->height() > 1) {
                // Hidding obstacle from the side
                colliding = true;

                // TODO EXTENTION push back
                // TODO add protected logic here
                ac.setXCoordinate(ac.getXCoordinate() - 30);
            }

            // END TODO
        }
    }

    // Check if we're below the floor
    if (newY <= floor) {
        newY = floor;
        grounded = true;
        jumpVelocity = 0;
        jumpCount = 0;
    }

    ac.setYCoordinate(newY);
    jumpVelocity += gravity;
}
