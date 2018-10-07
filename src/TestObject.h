#ifndef MOONSHINE_TESTOBJECT_H
#define MOONSHINE_TESTOBJECT_H

#include "Entity.h"
#include "GL/ForwardDeclarations.h"

#include <memory>
#include <vector>
#include <array>

namespace Moonshine
{

class TestObject : public Entity
{
public:
    TestObject();
    ~TestObject();

    virtual void update() override;
    virtual void render() override;

private:
    std::shared_ptr<GL::VertexArray> _vao;
    std::vector<std::shared_ptr<GL::Buffer>> _bufs;
    std::shared_ptr<GL::Program> _prog;
    std::array<float, 4> _bgcolor = { 0.05f, 0.05f, 0.05f, 1.0f };
};

}

#endif //MOONSHINE_TESTOBJECT_H
