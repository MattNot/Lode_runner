#include "../Headers/Enemy.hpp"
string Enemy::getEntity() { return "Enemy"; }

void Enemy::setRedHat(bool hat) { this->hat = hat; }

bool Enemy::isRedHat() { return hat; }

void Enemy::die()
{
    this->setFrame(0);
    this->setX(this->getInitX());
    this->setY(this->getInitY());
    cout << getY();
}

Enemy::Enemy() : Entity()
{
    for (int i = 0; i < 12; ++i)
        sprite[i] = NULL;
}

Enemy::Enemy(int x, int y, string sprite[12]) : Entity(x, y)
{
    for (int i = 0; i < 12; ++i)
        this->sprite[i] = al_load_bitmap(sprite[i].c_str());
}

Enemy::~Enemy()
{
    for (int i = 0; i < 12; ++i)
        al_destroy_bitmap(sprite[i]);
}
bool Enemy::isInHole(list<Quadruple> holes, char map[16][28], bool head)
{
    for (auto i : holes)
    {
        if (head)
        {
            if ((this->getY() - 18) / 20 == i.first && this->getX() / 20 == i.second)
            {
                if (map[i.first][i.second] == '#')
                {
                    this->die();
                    this->setFall(false);
                    return false;//visto che è morto
                }
                if (this->fallen < 0.1 && i.third < 6.8)
                {
                    map[getY() / 20][getX() / 20] = '}';
                }
                return true;
            }
        }
        else
        {
            if ((this->getY()) / 20 == i.first && this->getX() / 20 == i.second)
            {
                if (map[i.first][i.second] == '#')
                {
                    this->die();
                    this->setFall(false);
                    return false;//visto che è morto
                }
                if (this->fallen < 0.1 && i.third < 6.8)
                {
                    map[getY() / 20][getX() / 20] = '}';
                }
                return true;
            }
        }
    }
    return false;
}
void Enemy::update(char map[16][28], list<Quadruple> holes, Player &p, int &nextY, int &nextX)
{
    bool headInHole = isInHole(holes,map,true);
    bool footInHole = isInHole(holes,map,false);
    if (headInHole && isRedHat())
    {
        map[(this->getY() / 20) - 1][this->getX() / 20] = '$';
        this->setRedHat(false);
        this->setFrame(4);
    }
    else if (this->getFall() && !headInHole)
    {
        this->setY(this->getY() + 5);
        if (map[((this->getY() + 5) / 20)][(this->getX() / 20)] == '#' || map[((this->getY() + 5) / 20)][(this->getX() / 20)] == 'H' || map[((this->getY() + 5) / 20)][(this->getX() / 20)] == '@')
        {
            this->setFall(false);
            /*if(this->isRedHat()){ non si sa mai
                setRedHat(false);
                if(map[(this->getY()+5)/20][(this->getX()/20)+1] == ' ')
                    map[(this->getY()+5)/20][(this->getX()/20)+1] == '$';
                else
                    map[(this->getY()+5)/20][(this->getX()/20)-1] == '$';
            }*/
        }
        if (map[((this->getY() - 18) / 20)][(this->getX() / 20)] == '-' && map[((this->getY()) / 20)][(this->getX() / 20)] == '-')
        {
            this->setFall(false);
            this->setFrame(5);
        }

        if (map[((this->getY() - 18) / 20)][(this->getX() / 20)] == '-' && map[((this->getY() + 5) / 20)][(this->getX() / 20)] != '#')
        {
            this->setFall(true);
            this->setFrame(4);
        }
    }
    else
    {
        bool check = false;
        if (!footInHole)
        {
            if (this->getX() / 20 < nextX)
            {
                this->moveRight(map, isRedHat());

                check = false;
            }
            if ((this->getX() + 18) / 20 > nextX)
            {
                this->moveLeft(map, isRedHat());
                check = true;
            }
            if (this->getY() < (nextY * 20) + 18)
                this->moveDown(map, isRedHat());
            if (this->getY() / 20 > nextY)
                this->moveUp(map, check, isRedHat());
        }
    }
    //cout << this->isInHole(holes, map);
    if (footInHole)
    {
        fallen += 0.1;
        if (2.8 < fallen && fallen <= 2.9)
        {
            this->setFrame(3);
            this->setY(this->getY() - 3);
            this->setFall(false);
        }
        if (2.9 < fallen && fallen <= 3.0)
        {
            this->setY(this->getY() - 3);
            setMirrorY(true);
        }
        if(3.1 < fallen && fallen <= 3.2)
        {
            this->setY(this->getY() - 3);
            setMirrorY(false);
        }
        if(3.2 < fallen && fallen <= 3.3)
        {
            this->setY(this->getY() - 3);
            setMirrorY(true);
        }
        if(3.3 < fallen && fallen <= 3.4)
        {
            this->setY(this->getY() - 3);
            setMirrorY(false);
        }
        if(3.4 < fallen && fallen <= 3.5)
        {
            this->setY(this->getY() - 3);
            setMirrorY(true);
        }
        if (3.6 < fallen)
        {
            fallen = 0;
            this->setY(this->getY() - 2);
            if (p.getX() > this->getX() && map[(this->getY())/20][(this->getX()/20) + 1] != '#')
            {
                this->setX(this->getX() + 15);
            }
            else if (p.getX() < this->getX() && map[(this->getY())/20][(this->getX()/20) - 1] != '#')
            {
                this->setX(this->getX() - 15);
            }
            this->setFall(false);
        }
    }
    if (map[getY() / 20][(getX()) / 20] == '$')
    {
        if (!isRedHat())
        {
            setRedHat(true);
            map[getY() / 20][getX() / 20] = ' ';
        }
    }
}
