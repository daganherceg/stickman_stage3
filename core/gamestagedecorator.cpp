#include "gamestagedecorator.h"

GameStageDecorator::GameStageDecorator(std::unique_ptr<GameStage> stage) : stage(std::move(stage)) {

}

GameStageDecorator::~GameStageDecorator() {

}

void GameStageDecorator::update() {
    stage->update();
}

void GameStageDecorator::render(Renderer &renderer) {
    stage->render(renderer);
}

void GameStageDecorator::input(QKeyEvent &event) {
    stage->input(event);
}

// TODO Added
void GameStageDecorator::released(QKeyEvent &event) {
    stage->released(event);
}
// END TODO
