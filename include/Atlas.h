#ifndef ATLAS_H
#define ATLAS_H

#include <string>
#include <unordered_map>

namespace viewer
{

struct region
{
    unsigned u;
    unsigned v;
    unsigned w;
    unsigned h;
};

class Atlas
{
public:
    explicit Atlas(const char* name);
    explicit Atlas(const std::string& name);

    float u(const std::string& texture, float coord) const;
    float v(const std::string& texture, float coord) const;

private:
    unsigned mWidth;
    unsigned mHeight;

    std::unordered_map<std::string, region> mTransforms;
};
}

#endif
