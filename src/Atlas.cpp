#include "Atlas.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>

namespace viewer
{

std::vector<std::string>& split(const std::string& s, char delim,
        std::vector<std::string>& elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss,item,delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string& s, char delim)
{
    std::vector<std::string> elems;
    split(s,delim,elems);
    return elems;
}

Atlas::Atlas(const char* name)
{
    // load up the file
    std::ifstream f(name, std::ios::in);
    if (f.is_open())
    {
        bool dimload = false;
        std::string line;
        while(std::getline(f,line))
        {
            if (line[0] == '#')
            {
                // comment line, ignore
                continue;
            }
            else
            {
                // remove all the spaces
                line.erase(std::remove_if(
                            std::begin(line),std::end(line), ::isspace),
                        std::end(line));
                // split on colon
                auto cs = split(line,':');
                if (!cs.empty())
                {
                    // split on comma
                    auto vs = split(cs[1],',');
                    if (cs[0] == "dimensions")
                    {
                        if (dimload)
                        {
                            throw std::runtime_error(
                                    "Dimensions already defined");
                        }
                        // load the dimensions
                        if (vs.size() < 2)
                        {
                            throw std::runtime_error(
                                    "Dimensions needs width and height");
                        }
                        std::istringstream(vs[0]) >> mWidth;
                        std::istringstream(vs[1]) >> mHeight;
                        dimload = true;
                    }
                    else
                    {
                        if (vs.size() < 4)
                        {
                            throw std::runtime_error(
                                    "Regions need four entries");
                        }
                        region r;
                        std::istringstream(vs[0]) >> r.u;
                        std::istringstream(vs[1]) >> r.v;
                        std::istringstream(vs[2]) >> r.w;
                        std::istringstream(vs[3]) >> r.h;
                        mTransforms.insert({cs[0],r});
                    }
                }
            }
        }
    }
    else
    {
        throw std::runtime_error("Couldn't open atlas file");
    }
}

Atlas::Atlas(const std::string& name) :
    Atlas(name.c_str())
{
}

float Atlas::u(const std::string& texture, float coord) const
{
    const auto& it = mTransforms.find(texture);
    if (it != mTransforms.end())
    {
        const auto& r = it->second;
        return (r.w * coord + r.u)/mWidth;
    }
    throw std::runtime_error("Utransform Invalid texture object");
}

float Atlas::v(const std::string& texture, float coord) const
{
    const auto& it = mTransforms.find(texture);
    if (it != mTransforms.end())
    {
        const auto& r = it->second;
        return 1.0f - (r.h * (1.0f - coord) + r.v)/mHeight;
    }
    throw std::runtime_error("Vtransform Invalid texture object");
}

}
