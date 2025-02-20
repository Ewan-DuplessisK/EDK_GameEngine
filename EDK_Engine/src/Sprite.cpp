#include "Sprite.h"

void Sprite::draw() {

}

void Sprite::setTexture(const Texture &textP) {
    texture = textP;
    textureSize = {float(texture.getWidth()),float(texture.getHeight())};
}

bool Sprite::operator<(const Sprite &rightSprite) {
    return zDepth<rightSprite.getZDepth();
}
