#include "freestickman.h"
#include "collision.h"
#include "score.h"

#include <iostream>
#include <algorithm>

FreeStickman::FreeStickman(int floor, int jumpImpulse, int maxJumpCount, int gravity) :
    JumpingStickman(floor, jumpImpulse, maxJumpCount, gravity)  {

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
            if ((col.down && jumpVelocity < 0 && other->height() > 1) || getMode() == "giant") {
                // Hitting obstacle from above || is Giant
                jumpVelocity = 0;
                grounded = true;
                jumpCount = 0;
                newY = by + other->height() + 1;

                // Automatically jumping & move forward when hitting obstacle
                if (getMode() != "giant") getCoordinate().setXCoordinate(getCoordinate().getXCoordinate() + 30);
                if (getMode() == "giant") ac.setXCoordinate(ac.getXCoordinate() - 50);
                if (getMode() != "giant") jump();

                other->setSize(0, 0);
                other->setVelocity(1000);


                // Swap collision element with first element (ensure collision element deleted)
                std::vector<std::unique_ptr<Entity>>::iterator it = std::find(obstacles.begin(), obstacles.end(), other);
                int index = int(std::distance(obstacles.begin(), it));
                if (index > 0) {
                    std::iter_swap(obstacles.begin(), obstacles.begin() + index);
                }
            } if (col.up && other->height() > 1) {
                // Hitting obstacle from below
                jumpVelocity = 0;
                newY = by - height() - 1;
            } else if (other->height() > 1) {
                // Hidding obstacle from the side
                colliding = true;

                ac.setXCoordinate(ac.getXCoordinate() - 50);
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

void FreeStickman::setMode(std::string mode) {
    this->mode = mode;
    this->setSize(mode);
    if (size.compare("tiny") == 0) {
        maxJumpCount = 1;
    } else if(size.compare("normal") == 0) {
        maxJumpCount = 2;
    } else if(size.compare("large") == 0) {
        maxJumpCount = 3;
    } else {
        maxJumpCount = 0;
    }

}


