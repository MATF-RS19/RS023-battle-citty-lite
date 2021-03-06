#ifndef NPC_H
#define NPC_H
#include <QTimer>
#include "include/tank.h"
#include <QTimer>

class Npc : public Tank
{
public:
    Npc(qreal x, qreal y, int id);
    ~Npc();
    Npc(const Npc& other);
    void colisionDetection() override;

    QTimer _shootTimer;
public slots:

    void onCollision();

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int _npcDirection;

private:

};

#endif // NPC_H
