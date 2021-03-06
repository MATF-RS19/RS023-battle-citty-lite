#ifndef TANK_H
#define TANK_H

#include <QGraphicsObject>
#include <QMap>
#include <QKeyEvent>
#include "include/bullet.h"



class Tank : public QGraphicsObject
{
    Q_OBJECT

public:
    Tank(int id);
    ~Tank() = default;

    enum Weapon {
        gun,        //cigla (1 sloj)
        d,          //cigla (2 sloja)
        e,          //cigla (4 sloja) + beton (1 sloj)
        f,          //cigla (4 sloja) + beton (2 sloja)
        g,          //cigla (4 sloja) + beton (4 sloja)
        r           //cigla (4 sloja) + beton (4 sloja) + cisti sumu
    };

    /*!
     * \brief onShot should be called every time
     * the tank is shoted by opponent.
     * \details change resistant and destroy tank if
     * its resistant become 0.
     */
    void onShot();

    /*!
     * \brief setSpeed
     */
    void setSpeed(qreal);

    /*!
     * \brief getWeapon
     * \return Weapon
     */
    Weapon getWeapon();

    /*!
     * \brief setWeapon
     * \param newWeapon
     */
    void setWeapon(const Weapon& newWeapon);

    /*!
     * \brief getSmer
     * \return 1, 2, 3 or 4 depending on wich way tank is
     * faced (Up, Down, Right or Left).
     */
    int getDirection();

    virtual void colisionDetection();

    /*!
     * \brief setUp sets indicator if tank is faced to 'up'
     * \param t
     */
    void setUp(bool t);
    void setDown(bool t);
    void setRight(bool t);
    void setLeft(bool t);
    void move();
    void reMoving();
    Bullet* shoot();
    bool shootingEnabled;

protected:
    bool _moving; //should be set and reset at the collision

    bool _movingUp, _movingDown, _movingLeft, _movingRight;
    int _resistent;         //!< how many times can survive bullet
    qreal _speed = 5;           //!< should be incremented/decremented when get boost
    Weapon _weapon;
    bool _isManual;         //!< indicates if more then one bullet can be projected at the same time
    qreal _x;               //!< x coordinate
    qreal _y;               //!< y coordinate
    const int _size = 50;   //!< size of tank (width and heigh)
    QMap<QString, QPixmap> _icons; //!< icons for every 'smer'
    QString _activeIcon;    //!< active 'smer'

public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QVector<int> grid;
    void adjustPosition();
};

#endif // TANK_H
