#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <GL/glew.h>

namespace viewer
{
class Texture
{
public:
    explicit Texture(const char* path);
    explicit Texture(const std::string& path);
    Texture(const Texture&) = delete;
    Texture(Texture&&) = delete;
    ~Texture();

    void activate(int textureUnit);

private:
    GLuint mID;

};
}

#endif
