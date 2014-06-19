#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <GL/glew.h>

namespace viewer
{
class ShaderProgram;

class Shader
{
public:
    enum ShaderType
    {
        VERTEX,
        FRAGMENT,
        GEOMETRY,
        TESSELATION_CONTROL,
        TESSELATION_EVALUATION,
        COMPUTE
    };

    explicit Shader(ShaderProgram* shaderProgram, ShaderType type,
            const std::string& code, bool immediate = false);
    Shader(const Shader&) = delete;
    Shader(Shader&&) = delete;
    ~Shader();

    inline GLuint id() const { return mID; }
    inline ShaderType type() const { return mType; }
    inline std::string error() const { return mError; }

private:
    void generateID();
    bool compile(const std::string& code);
    bool compile(const char* code);
    bool compileFile(const std::string& filename);
    bool compileFile(const char* filename);

    GLuint mID;
    ShaderType mType;
    std::string mError;
};
}

#endif
