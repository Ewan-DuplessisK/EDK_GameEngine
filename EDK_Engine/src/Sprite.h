#ifndef ORPG_GAMEENGINE_SPRITE_H
#define ORPG_GAMEENGINE_SPRITE_H


#include "Texture.h"

class Sprite {
public:
    Sprite(Texture& textP,int zDepthP = 10);
    ~Sprite(){};

    void draw();

    int getZDepth() const {return zDepth;}
    Vector2 getTextureSize() const {return textureSize;}
    bool getVisibility() const {return isVisible;}
    Matrix4 getTransform() const {return transform;}
    Texture* getTexture() {return &texture;}

    void setTexture(const Texture& textP);
    void setVisibility(bool visibilityP) {isVisible=visibilityP;}

    bool operator<(const Sprite& rightSprite);

private:
    Texture texture;
    Vector2 textureSize;
    int zDepth;
    bool isVisible;
    Matrix4 transform;
};


#endif //ORPG_GAMEENGINE_SPRITE_H
