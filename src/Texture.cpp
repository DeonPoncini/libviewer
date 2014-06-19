#include "Texture.h"

#include <fstream>
#include <stdexcept>
#include <cstring>
#include <vector>

namespace viewer
{

// DDS constants
static const unsigned MAGIC_SIZE = 4;
static const unsigned DDS_HEADER_SIZE = 124;

struct DDSHeader
{
    unsigned height;
    unsigned width;
    unsigned linearSize;
    unsigned mipMapCount;
    unsigned fourCC;
};

static const unsigned FOURCC_DXT1 = 0x31545844;
static const unsigned FOURCC_DXT3 = 0x33545844;
static const unsigned FOURCC_DXT5 = 0x53545844;

DDSHeader loadHeader(char* header)
{
    DDSHeader ret;
    ret.height = *(unsigned*)&(header[8]);
    ret.width = *(unsigned*)&(header[12]);
    ret.linearSize = *(unsigned*)&(header[16]);
    ret.mipMapCount = *(unsigned*)&(header[24]);
    ret.fourCC = *(unsigned*)&(header[80]);
    return ret;
}

Texture::Texture(const char* path) :
    mID(0)
{
    std::ifstream f(path, std::ios::binary);
    if (!f.is_open())
    {
        throw std::runtime_error(std::string("Couldn't load texture ") + path);
    }

    // verify the filetype
    char filecode[MAGIC_SIZE];
    f.read(filecode,MAGIC_SIZE);
    if (strncmp(filecode,"DDS ",MAGIC_SIZE) != 0)
    {
        throw std::runtime_error(std::string("Invalid file format ")
                + filecode);
    }

    // read the header
    char h[DDS_HEADER_SIZE];
    f.read(h,DDS_HEADER_SIZE);
    auto header = loadHeader(h);

    // how large is the file going to be
    auto bufsize = header.mipMapCount > 1 ?  header.linearSize * 2
        : header.linearSize;
    std::vector<char> buffer;
    buffer.reserve(bufsize);
    buffer.assign(std::istreambuf_iterator<char>(f),
            std::istreambuf_iterator<char>());
    f.close();

    unsigned format;
    switch (header.fourCC)
    {
        case FOURCC_DXT1:
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            break;
        case FOURCC_DXT3:
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
        case FOURCC_DXT5:
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            break;
        default:
            throw std::runtime_error(std::string("Invalid FourCC ") +
                    std::to_string(header.fourCC));
        break;
    }

    // create an opengl texture
    glGenTextures(1,&mID);
    // bind to the texture
    glBindTexture(GL_TEXTURE_2D, mID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    auto blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    auto offset = 0;
    // load mipmaps
    auto width = header.width;
    auto height = header.height;

    for (auto level = 0; level < header.mipMapCount &&
            (width || height); ++level)
    {
            auto size = ((width+3)/4)*((height+3)/4)*blockSize;
            glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width,
                height, 0, size, buffer.data() + offset);
            offset += size;
            width /= 2;
            height /=2;
            if (width < 1) width = 1;
            if (height < 1) height = 1;
    }
}

Texture::Texture(const std::string& path) :
    Texture(path.c_str())
{
}

Texture::~Texture()
{
    glDeleteTextures(1, &mID);
}

void Texture::activate(int textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, mID);
}
}
