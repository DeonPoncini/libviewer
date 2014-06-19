#include "Shader.h"
#include "ShaderProgram.h"

#include <fstream>
#include <vector>

#include <stdexcept>

namespace viewer
{
Shader::Shader(ShaderProgram* shaderProgram, ShaderType type,
        const std::string& code, bool immediate) :
    mID(0),
    mType(type)
{
    generateID();
    bool status = false;
    if (immediate)
    {
        status = compile(code);
    }
    else
    {
        status = compileFile(code);
    }
    if (!status)
    {
        throw std::runtime_error(mError);
    }
    shaderProgram->add(this);
}

Shader::~Shader()
{
    glDeleteShader(mID);
}

void Shader::generateID()
{
    switch(mType)
    {
        case VERTEX:
            mID = glCreateShader(GL_VERTEX_SHADER);
            break;
        case FRAGMENT:
            mID = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        case GEOMETRY:
            mID = glCreateShader(GL_GEOMETRY_SHADER);
            break;
        case TESSELATION_CONTROL:
            mID = glCreateShader(GL_TESS_CONTROL_SHADER);
            break;
        case TESSELATION_EVALUATION:
            mID = glCreateShader(GL_TESS_EVALUATION_SHADER);
            break;
        case COMPUTE:
            mID = glCreateShader(GL_COMPUTE_SHADER);
            break;
    }
}

bool Shader::compile(const std::string& code)
{
    return compile(code.c_str());
}

bool Shader::compile(const char* code)
{
    glShaderSource(mID, 1, &code, nullptr);
    glCompileShader(mID);

    auto result = GL_FALSE;
    glGetShaderiv(mID, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        // failed to compile
        int infoLogLength;
        glGetShaderiv(mID, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> errorMessage(infoLogLength);
        glGetShaderInfoLog(mID, infoLogLength, nullptr, &errorMessage[0]);
        mError = &errorMessage[0];
        return false;
    }
    return true;
}

bool Shader::compileFile(const std::string& filename)
{
    return compileFile(filename.c_str());
}

bool Shader::compileFile(const char* filename)
{
    std::string source = "";
    std::ifstream stream(filename, std::ios::in);
    if (stream.is_open())
    {
        std::string line = "";
        while(std::getline(stream,line))
        {
            source += "\n" + line;
        }
        stream.close();
        return compile(source);
    }
    mError = std::string(filename) + " not found\n";
    return false;
}
}
