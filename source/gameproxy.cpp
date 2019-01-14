#include "include/gameproxy.h"

GameProxy::GameProxy(QWidget *parrent)
    :QObject(parrent)
{
    _gameWidget = new GameWidget(parrent);

    QObject::connect(_gameWidget, &GameWidget::endOfLevel,
                     this, &GameProxy::onEndOfLevel);

    QObject::connect(_gameWidget->getGameScene(), &GameScene::killed,
                     this, &GameProxy::changeLifes);
}

GameWidget *GameProxy::getGameWidget() const
{
    return _gameWidget;
}

void GameProxy::initializeGame()
{
    //javi gameWidgetu da se inicijalizuje
    _gameWidget->initializeLevel(1);

    //inicijalizuj svoje vrednosti
    _activeLevel = 1;
    _numOfLifes = 3;
    _score = 100;
    _gameWidget->setLifeInformation(_numOfLifes);
}

void GameProxy::changeLifes()
{
    if (--_numOfLifes < 0)
    {
        updateScore(0); //!< only add for level reached
        saveScore();
        _gameWidget->abort();
        emit this->gameOver();
    }
    _gameWidget->setLifeInformation(_numOfLifes);
}

void GameProxy::updateScore(double bonus)
{
    _score += bonus + _activeLevel + _numOfLifes;
}

void GameProxy::saveScore()
{
    QFile file("resources/score.txt");
    file.open(QIODevice::ReadOnly);
    QString bestScore = file.readLine();
    if (bestScore.toDouble() < _score) {
        file.close();
        file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
        QTextStream out(&file);
        out << _score << endl;
        }
    file.close();
}

void GameProxy::onEndOfLevel(double bonus)
{
    updateScore(bonus);

    //show short sum

    if (++_activeLevel <= NUM_OF_LEVELS)
        _gameWidget->initializeLevel(_activeLevel);
}