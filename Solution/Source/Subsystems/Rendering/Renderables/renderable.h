#pragma once

class ATexture;

class Renderable
{
public:
    Renderable() = default;

    Renderable(const Renderable&) = default;
    Renderable(Renderable&&) = default;
    Renderable& operator=(const Renderable&) = default;
    Renderable& operator=(Renderable&&) = default;
    
    virtual ~Renderable() = default;

    virtual ATexture* getTexture() = 0;
    virtual const ATexture* getTexture() const = 0;

    virtual int getWidth() const;
    virtual int getHeight() const;

    virtual Renderable* clone() const = 0;
};