#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "Shader.h"

#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>

namespace viewer
{
class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();

    void add(const Shader* shader);
    void link();
    void activate();

    inline std::string error() const { return mError; }

    void setUniform(const char* name, GLfloat v0);
    void setUniform(const char* name, GLfloat v0, GLfloat v1);
    void setUniform(const char* name, GLfloat v0, GLfloat v1, GLfloat v2);
    void setUniform(const char* name, GLfloat v0, GLfloat v1,
                                      GLfloat v2, GLfloat v3);
    void setUniform(const char* name, GLint v0);
    void setUniform(const char* name, GLint v0, GLint v1);
    void setUniform(const char* name, GLint v0, GLint v1, GLint v2);
    void setUniform(const char* name, GLint v0, GLint v1, GLint v2, GLint v3);
    void setUniform(const char* name, GLuint v0);
    void setUniform(const char* name, GLuint v0, GLuint v1);
    void setUniform(const char* name, GLuint v0, GLuint v1, GLuint v2);
    void setUniform(const char* name, GLuint v0, GLuint v1,
                                      GLuint v2, GLuint v3);
    void setUniform(const char* name, const GLfloat* v);
    void setUniform(const char* name, const glm::f32vec2& v);
    void setUniform(const char* name, const glm::f32vec3& v);
    void setUniform(const char* name, const glm::f32vec4& v);
    void setUniform(const char* name, const GLint* v);
    void setUniform(const char* name, const glm::i32vec2& v);
    void setUniform(const char* name, const glm::i32vec3& v);
    void setUniform(const char* name, const glm::i32vec4& v);
    void setUniform(const char* name, const GLuint* v);
    void setUniform(const char* name, const glm::u32vec2& v);
    void setUniform(const char* name, const glm::u32vec3& v);
    void setUniform(const char* name, const glm::u32vec4& v);
    void setUniform(const char* name, const glm::f32mat2& v);
    void setUniform(const char* name, const glm::f32mat3& v);
    void setUniform(const char* name, const glm::f32mat4& v);
    void setUniform(const char* name, const glm::f32mat2x3& v);
    void setUniform(const char* name, const glm::f32mat3x2& v);
    void setUniform(const char* name, const glm::f32mat2x4& v);
    void setUniform(const char* name, const glm::f32mat4x2& v);
    void setUniform(const char* name, const glm::f32mat3x4& v);
    void setUniform(const char* name, const glm::f32mat4x3& v);

private:
    GLint lookupUniform(const char* name);

    GLuint mID;
    std::vector<const Shader*> mShaders;
    std::unordered_map<const char*,GLint> mUniforms;
    std::string mError;

};
}
#endif
