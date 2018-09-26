#include "TestObject.h"

#include "glad/glad.h"

#include "GL/Buffer.h"
#include "GL/VertexArray.h"
#include "GL/Shader.h"
#include "GL/Program.h"

#include <vector>
#include <array>
#include <spdlog/spdlog.h>

using vec3 = std::array<float, 3>;
using namespace Moonshine::GL;

const std::vector<vec3> vertices
{
    { -0.5f, -0.5f, 0.0f },
    { 0.5f, 0.5f, 0.0f },
    { -0.5f, 0.5f, 0.0f },
    { 0.5f, -0.5f, 0.0f },
    { 0.5f, 0.5f, 0.0f },
    { -0.5f, -0.5f, 0.0f }
};

const std::vector<vec3> colors
{
    { 1.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f },
    { 1.0f, 1.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    { 1.0f, 0.0f, 0.0f }
};

const std::vector<vec3> normals
{
    { 0.0f, 0.0f, 1.0f },
    { 0.0f, 0.0f, 1.0f },
    { 0.0f, 0.0f, 1.0f },
    { 0.0f, 0.0f, 1.0f },
    { 0.0f, 0.0f, 1.0f },
    { 0.0f, 0.0f, 1.0f }
};


const std::string vertShader = R"Bottle(
    #version 400 core

    layout(location = 0) in vec3 pos;
    layout(location = 1) in vec3 color;
    layout(location = 2) in vec3 normal;

    out vec3 vertex_color;
    out vec3 vertex_normal;

    void main()
    {
        //const mat4 proj(1.0);
        //const mat4 model(1.0);
        //const mat4 view(1.0);

        vertex_color = color;
        vertex_normal = normal;

        //gl_Position = proj * model * view * vec4(pos, 1.0);
        gl_Position = vec4(pos, 1.0);
    }
)Bottle";

const std::string geomShader = R"Bottle(
    #version 400 core

    layout(triangles) in;
    layout(triangle_strip, max_vertices = 3) out;

    in vec3 vertex_color[];
    in vec3 vertex_normal[];

    out vec3 color;
    out vec3 normal;

    void main()
    {
        gl_Position = gl_in[0].gl_Position;
        color = vertex_color[0];
        normal = vertex_normal[0];
        EmitVertex();

        gl_Position = gl_in[1].gl_Position;
        color = vertex_color[1];
        normal = vertex_normal[1];
        EmitVertex();

        gl_Position = gl_in[2].gl_Position;
        color = vertex_color[2];
        normal = vertex_normal[2];
        EmitVertex();
    }
)Bottle";

const std::string fragShader = R"Bottle(
    #version 400 core

    in vec3 color;
    in vec3 normal;

    out vec4 fragcolor;

    void main()
    {
        if (gl_FrontFacing)
        {
            //fragcolor = vec4(0.5, 0.5, 0.5, 1.0);
            fragcolor = vec4(color, 1.0);
        }
        else
        {
            fragcolor = vec4(0.5, 0.5, 0.5, 1.0);
        }
    }
)Bottle";

namespace Moonshine
{

TestObject::TestObject() :
    _vao(std::make_shared<VertexArray>()),
    _prog(std::make_shared<Program>())
{
    auto vbuf = std::make_shared<Buffer>();
    vbuf->setData(vertices, Buffer::Usage::StaticDraw);
    _bufs.emplace_back(vbuf);

    auto cbuf = std::make_shared<Buffer>();
    cbuf->setData(colors, Buffer::Usage::StaticDraw);
    _bufs.emplace_back(cbuf);

    auto nbuf = std::make_shared<Buffer>();
    nbuf->setData(normals, Buffer::Usage::StaticDraw);
    _bufs.emplace_back(nbuf);

    _vao->bindBuffer(0, *vbuf, 0, sizeof(vec3));
    _vao->setAttribFormat(0, 3, VertexArray::Type::Float);
    glVertexArrayAttribBinding(_vao->id(), 0, 0);
    _vao->enableAttrib(0);

    _vao->bindBuffer(1, *cbuf, 0, sizeof(vec3));
    _vao->setAttribFormat(1, 3, VertexArray::Type::Float);
    glVertexArrayAttribBinding(_vao->id(), 1, 1);
    _vao->enableAttrib(1);

    _vao->bindBuffer(2, *nbuf, 0, sizeof(vec3));
    _vao->setAttribFormat(2, 3, VertexArray::Type::Float);
    glVertexArrayAttribBinding(_vao->id(), 2, 2);
    _vao->enableAttrib(2);

    Shader vs(Shader::Type::Vertex);
    vs.setSource(vertShader);
    vs.compile();
    if (!vs.status())
    {
        spdlog::get("console")->error("Failed to compile vertex shader: {0}", vs.infoLog());
    }

    Shader gs(Shader::Type::Geometry);
    gs.setSource(geomShader);
    gs.compile();
    if (!gs.status())
    {
        spdlog::get("console")->error("Failed to compile geometry shader: {0}", gs.infoLog());
    }

    Shader fs(Shader::Type::Fragment);
    fs.setSource(fragShader);
    fs.compile();
    if (!fs.status())
    {
        spdlog::get("console")->error("Failed to compile fragment shader: {0}\n ", fs.infoLog());
    }

    _prog->attach(vs);
    _prog->attach(gs);
    _prog->attach(fs);
    _prog->link();
    if (!_prog->status())
    {
        fmt::print("Failed to link shader program: {0}", _prog->infoLog());
    }
}

TestObject::~TestObject() = default;

void TestObject::render()
{
    const std::array<float, 4> bgcolor = { 0.05f, 0.05f, 0.05f, 1.0f };
    const float depth = 1.0f;

    glClearNamedFramebufferfv(0, GL_COLOR, 0, bgcolor.data());
    glClearNamedFramebufferfv(0, GL_DEPTH, 0, &depth);

    _prog->use();
    _vao->bind();
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

}
