#include "Animation.h"
#include <cmath>
#include <utility>
#include <iostream>


Animation::Animation() = default;

Animation::Animation(const std::string &name, const sf::Texture &t)
        : Animation(name, t, 1, 0) {}

Animation::Animation(std::string name, const sf::Texture &t, size_t frameCount, size_t speed)
        : m_name(std::move(name)), m_sprite(t), m_frameCount(frameCount), m_currentFrame(0), m_speed(speed) {
    m_size = vec2((float) t.getSize().x / float(frameCount), (float) t.getSize().y);
    m_sprite.setOrigin(m_size.x / 2.0f, m_size.y / 2.0f);
    m_sprite.setTextureRect(sf::IntRect(std::floor(float(m_currentFrame) * m_size.x), 0, m_size.x, m_size.y));
}

// updates the animation to show the next frame, depending on its speed
// animation loops when it reaches the end
void Animation::update() {
    // add the speed variable to the current frame
    m_currentFrame ++;
    //std::cout << m_currentFrame << std::endl;
    size_t frame;
	if (m_speed == 0)
		frame = 0;
    else
        frame = m_currentFrame / m_speed % m_frameCount;
    //std::cout << "animation-frame: " << frame << std::endl;
    m_sprite.setTextureRect(sf::IntRect(int(frame) * int(m_size.x), 0, int(m_size.x), int(m_size.y)));

    //std::cout << "animation: " << m_size.x * (m_currentFrame / m_speed % m_frameCount) << std::endl;
    
    // TODO: 1) calculate the correct frame of animation to play based on currentFrame and speed
    //       2) set the texture rectangle properly (see constructor for sample)

}

bool Animation::hasEnded() const {
    // TODO: detect when animation has ended (last frame waw played) and return true
    if (m_speed == 0)
        return true;
    return (m_currentFrame / m_speed) % m_frameCount == m_frameCount - 1;
}

const vec2 &Animation::getSize() const {
    return m_size;
}

const std::string &Animation::getName() const {
    return m_name;
}

sf::Sprite &Animation::getSprite() {
    return m_sprite;
}

