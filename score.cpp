#include "score.h"

Score::Score():
    hiscore(), currScore(0) {
    for (int i = 0; i < 10; i++) {
        std::string spritePath = ":sprites/" + std::to_string(i) + ".png";
        QPixmap sprite(QString::fromStdString(spritePath));
        digits[i] = sprite;
    }
}

void Score::increment() {
    currScore++;
}

// Render score from left to right. Requires FILO reading of integer
void Score::render(Renderer &renderer) {
    std::stack<int> number;
    unsigned int score = currScore;
    while (score > 0) {
        number.push(score % 10);
        score = score / 10;
    }

    int length = number.size();
    for (int i = 0; i < length; i++) {
        renderer.draw(700+i*10, 20, digits[number.top()]);
        number.pop();
    }
}

// TODO Added the following
unsigned int Score::getScore() {
    return currScore;
}

void Score::setScore(unsigned int score) {
    currScore = score;
}
