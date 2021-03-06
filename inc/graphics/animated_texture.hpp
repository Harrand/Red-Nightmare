//
// Created by Harrand on 01/09/2018.
//

#ifndef TOPAZ_ANIMATED_TEXTURE_HPP
#define TOPAZ_ANIMATED_TEXTURE_HPP
#include "graphics/texture.hpp"
#include "utility/time.hpp"

class PolyFrameTexture
{
public:
    using FrameMap = std::map<std::size_t, Texture>;
    //PolyFrameTexture(const std::string& animated_texture_filename);
    PolyFrameTexture();
    PolyFrameTexture(FrameMap frames);

    using iterator = PolyFrameTexture::FrameMap::iterator;
    using const_iterator = PolyFrameTexture::FrameMap::const_iterator;

    iterator begin();
    const_iterator cbegin() const;
    iterator end();
    const_iterator cend() const;

    const Texture* get_frame(std::size_t frame) const;
    void set_frame(std::size_t frame, Texture texture);
    std::size_t get_number_of_frames() const;
private:
    PolyFrameTexture::FrameMap frames;
};

class AnimatedTexture : public PolyFrameTexture, public FrameScheduler
{
public:
    AnimatedTexture(PolyFrameTexture::FrameMap frames, unsigned int fps);
    const Texture& get_frame_texture() const;
private:
    using FrameScheduler::set_number_of_frames;
};


#endif //TOPAZ_ANIMATED_TEXTURE_HPP
