#include "ShaderProgram.h"

#include <stdexcept>

#include <glm/gtc/type_ptr.hpp>

namespace viewer
{
ShaderProgram::ShaderProgram() :
    mID(glCreateProgram())
{
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(mID);
}

void ShaderProgram::add(const Shader* shader)
{
    mShaders.push_back(shader);
}

void ShaderProgram::link()
{
    for(auto&& s : mShaders)
    {
        glAttachShader(mID,s->id());
    }
    glLinkProgram(mID);

    auto result = GL_FALSE;
    glGetProgramiv(mID, GL_LINK_STATUS, &result);
    if (result == GL_FALSE)
    {
        // failed to compile
        int infoLogLength;
        glGetProgramiv(mID, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> errorMessage(std::max(infoLogLength,1));
        glGetProgramInfoLog(mID, infoLogLength, nullptr, &errorMessage[0]);
        mError = &errorMessage[0];
        throw std::runtime_error(error());
    }
}

void ShaderProgram::activate()
{
    glUseProgram(mID);
}

void ShaderProgram::setUniform(const char* name, GLfloat v0)
{
    glUniform1f(lookupUniform(name),v0);
}

void ShaderProgram::setUniform(const char* name, GLfloat v0, GLfloat v1)
{
    glUniform2f(lookupUniform(name),v0,v1);
}

void ShaderProgram::setUniform(const char* name, GLfloat v0, GLfloat v1,
        GLfloat v2)
{
    glUniform3f(lookupUniform(name),v0,v1,v2);
}

void ShaderProgram::setUniform(const char* name, GLfloat v0, GLfloat v1,
                                      GLfloat v2, GLfloat v3)
{
    glUniform4f(lookupUniform(name),v0,v1,v2,v3);
}

void ShaderProgram::setUniform(const char* name, GLint v0)
{
    glUniform1i(lookupUniform(name),v0);
}

void ShaderProgram::setUniform(const char* name, GLint v0, GLint v1)
{
    glUniform2i(lookupUniform(name),v0,v1);
}

void ShaderProgram::setUniform(const char* name, GLint v0, GLint v1, GLint v2)
{
    glUniform3i(lookupUniform(name),v0,v1,v2);
}

void ShaderProgram::setUniform(const char* name, GLint v0,
        GLint v1, GLint v2, GLint v3)
{
    glUniform4i(lookupUniform(name),v0,v1,v2,v3);
}

void ShaderProgram::setUniform(const char* name, GLuint v0)
{
    glUniform1ui(lookupUniform(name),v0);
}

void ShaderProgram::setUniform(const char* name, GLuint v0, GLuint v1)
{
    glUniform2ui(lookupUniform(name),v0,v1);
}

void ShaderProgram::setUniform(const char* name, GLuint v0,
        GLuint v1, GLuint v2)
{
    glUniform3ui(lookupUniform(name),v0,v1,v2);
}

void ShaderProgram::setUniform(const char* name, GLuint v0, GLuint v1,
                                      GLuint v2, GLuint v3)
{
    glUniform4ui(lookupUniform(name),v0,v1,v2,v3);
}

void ShaderProgram::setUniform(const char* name, const GLfloat* v)
{
    glUniform1fv(lookupUniform(name),1,v);
}

void ShaderProgram::setUniform(const char* name, const glm::f32vec2& v)
{
    glUniform2fv(lookupUniform(name),1,glm::value_ptr(v));
}

void ShaderProgram::setUniform(const char* name, const glm::f32vec3& v)
{
    glUniform3fv(lookupUniform(name),1,glm::value_ptr(v));
}

void ShaderProgram::setUniform(const char* name, const glm::f32vec4& v)
{
    glUniform4fv(lookupUniform(name),1,glm::value_ptr(v));
}

void ShaderProgram::setUniform(const char* name, const GLint* v)
{
    glUniform1iv(lookupUniform(name),1,v);
}

void ShaderProgram::setUniform(const char* name, const glm::i32vec2& v)
{
    glUniform2iv(lookupUniform(name),1,glm::value_ptr(v));
}

void ShaderProgram::setUniform(const char* name, const glm::i32vec3& v)
{
    glUniform3iv(lookupUniform(name),1,glm::value_ptr(v));
}

void ShaderProgram::setUniform(const char* name, const glm::i32vec4& v)
{
    glUniform4iv(lookupUniform(name),1,glm::value_ptr(v));
}

void ShaderProgram::setUniform(const char* name, const GLuint* v)
{
    glUniform1uiv(lookupUniform(name),1,v);
}

void ShaderProgram::setUniform(const char* name, const glm::u32vec2& v)
{
    glUniform2uiv(lookupUniform(name),1,glm::value_ptr(v));
}

void ShaderProgram::setUniform(const char* name, const glm::u32vec3& v)
{
    glUniform3uiv(lookupUniform(name),1,glm::value_ptr(v));
}

void ShaderProgram::setUniform(const char* name, const glm::u32vec4& v)
{
    glUniform4uiv(lookupUniform(name),1,glm::value_ptr(v));
}

void ShaderProgram::setUniform(const char* name, const glm::f32mat2& v)
{
    glUniformMatrix2fv(lookupUniform(name),1,GL_FALSE,glm::value_ptr(v));
}

void ShaderProgram::setUniform(const char* name, const glm::f32mat3& v)
{
    glUniformMatrix3fv(lookupUniform(name),1,GL_FALSE,glm::value_ptr(v));
}

void ShaderProgram::setUniform(const char* name, const glm::f32mat4& v)
{
    glUniformMatrix4fv(lookupUniform(name),1, GL_FALSE, glm::value_ptr(v));
}

void ShaderProgram::setUniform(const char* name, const glm::f32mat2x3& v)
{
    glUniformMatrix2x3fv(lookupUniform(name),1, GL_FALSE, glm::value_ptr(v));
}

void ShaderProgram::setUniform(const char* name, const glm::f32mat3x2& v)
{
    glUniformMatrix3x2fv(lookupUniform(name),1, GL_FALSE, glm::value_ptr(v));
}

void ShaderProgram::setUniform(const char* name, const glm::f32mat2x4& v)
{
    glUniformMatrix2x4fv(lookupUniform(name),1, GL_FALSE, glm::value_ptr(v));
}

void ShaderProgram::setUniform(const char* name, const glm::f32mat4x2& v)
{
    glUniformMatrix4x2fv(lookupUniform(name),1, GL_FALSE, glm::value_ptr(v));
}

void ShaderProgram::setUniform(const char* name, const glm::f32mat3x4& v)
{
    glUniformMatrix3x4fv(lookupUniform(name),1, GL_FALSE, glm::value_ptr(v));
}

void ShaderProgram::setUniform(const char* name, const glm::f32mat4x3& v)
{
    glUniformMatrix4x3fv(lookupUniform(name),1, GL_FALSE, glm::value_ptr(v));
}

GLint ShaderProgram::lookupUniform(const char* name)
{
    auto i = mUniforms.find(name);
    if (i == mUniforms.end())
    {
        // create the uniform
        auto id = glGetUniformLocation(mID,name);
        mUniforms.insert({name,id});
        return id;
    }
    return i->second;
}
}
