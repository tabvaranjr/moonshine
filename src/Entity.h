#ifndef MOONSHINE_ENTITY_H
#define MOONSHINE_ENTITY_H

namespace Moonshine
{

class Entity
{
public:
    virtual void update() = 0;
    virtual void render() = 0;
};

}

#endif //MOONSHINE_ENTITY_H
