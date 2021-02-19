/*
 * renderer.cc
 * Created: 2021-01-22, 23:16:03.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <voxelius/renderer.hh>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

void Mesh::clear()
{
    vertices.clear();
    indices.clear();
}

void Mesh::addVertex(const vertex &vertex)
{
    vertices.push_back(vertex);
}

void Mesh::addIndex(unsigned int index)
{
    indices.push_back(index);
}

void Mesh::update()
{
    vbo.setData(vertices.data(), sizeof(vertex) * vertices.size());
    ebo.setData(indices.data(), sizeof(unsigned int) * indices.size());

    vao.bindVBO(vbo, 0, offsetof(vertex, position), sizeof(vertex));
    vao.bindVBO(vbo, 1, offsetof(vertex, texcoord), sizeof(vertex));
    vao.bindEBO(ebo);

    vao.enableAttrib(0);
    vao.enableAttrib(1);

    vao.setAttribFormat<float>(0, 3, false);
    vao.setAttribFormat<float>(1, 2, false);

    vao.setAttribBinding(0, 0);
    vao.setAttribBinding(1, 1);
}

namespace renderer
{
static int view_width = 0;
static int view_height = 0;
static float view_aspect = 0.0;
static float view_fov = 0.0;
static float view_z_near = 0.0;
static float view_z_far = 0.0;

static mat4x4_t view_matrix = mat4x4_t(1.0);

static const gl::Program *cur_program = nullptr;

void setupView(int width, int height, float z_near, float z_far)
{
    view_width = width;
    view_height = height;
    view_aspect = (float)width / (float)height;
    view_z_near = z_near;
    view_z_far = z_far;
    glViewport(0, 0, width, height);
}

void use2dView(const vec3_t &cam_position, const quat_t &cam_rotation)
{
    view_matrix = glm::ortho<float>(-1.0, 1.0, 1.0 * view_aspect, -1.0 * view_aspect, view_z_near, view_z_far);
    view_matrix = glm::translate(view_matrix, cam_position);
    view_matrix = view_matrix * glm::mat4_cast(cam_rotation);
    glDisable(GL_DEPTH_TEST);
}

void use3dView(const vec3_t &cam_position, const quat_t &cam_rotation)
{
    view_matrix = glm::perspective<float>(glm::radians(view_fov), view_aspect, view_z_near, view_z_far);
    view_matrix = glm::translate(view_matrix, cam_position);
    view_matrix = view_matrix * glm::mat4_cast(cam_rotation);
    glEnable(GL_DEPTH_TEST);
}

void setFOV(float fov)
{
    view_fov = fov;
}

float getFOV()
{
    return view_fov;
}

void clearColor(const vec3_t &color)
{
    glClearColor(color.r, color.g, color.b, 1.0);
}

void clearColor(const vec4_t &color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void clear(bool color, bool depth, bool stencil)
{
    GLbitfield bits = 0;
    if(color)
        bits |= GL_COLOR_BUFFER_BIT;
    if(depth)
        bits |= GL_DEPTH_BUFFER_BIT;
    if(stencil)
        bits |= GL_STENCIL_BUFFER_BIT;
    glClear(bits);
}

void setProgram(const gl::Program *program)
{
    cur_program = program;
    if(!cur_program) {
        glUseProgram(0);
        return;
    }

    cur_program->setUniform(0, view_matrix);
    glUseProgram(cur_program->getProgram());
}

void setTexture(const gl::Texture *texture, unsigned int unit)
{
    glBindTextureUnit(unit, texture ? texture->getTexture() : 0);
}

void render(const Mesh &mesh, const mat4x4_t &model)
{
    if(cur_program) {
        cur_program->setUniform(1, model);
        glBindVertexArray(mesh.vao.getVAO());
        glDrawElements(GL_TRIANGLES, (GLsizei)mesh.getNumIndices(), GL_UNSIGNED_INT, nullptr);
    }
}
} // namespace renderer
