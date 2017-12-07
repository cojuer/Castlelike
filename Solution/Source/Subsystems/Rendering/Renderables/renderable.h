#pragma once

class ATexture;

class Renderable
{
public:
    virtual ~Renderable() = default;
    virtual ATexture* getTexture() = 0;
    virtual const ATexture* getTexture() const = 0;

    virtual int getWidth() const;
    virtual int getHeight() const;

    virtual Renderable* clone() const = 0;
};