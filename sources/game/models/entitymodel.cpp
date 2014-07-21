#include "entitymodel.h"

namespace game
{

    EntityModel::EntityModel(float speed, std::string texture, bool hasAiFunction, bool hasPopFunction)
    {
        m_speed = speed;
        m_texture = engine::graphics::getTexture(texture);
        m_hasAiFunction = hasAiFunction;
        m_hasPopFunction = hasPopFunction;
    }

    float EntityModel::getSpeed()
    {
        return m_speed;
    }

    engine::graphics::Texture* EntityModel::getTexture()
    {
        return m_texture;
    }

    bool EntityModel::hasAiFunction()
    {
        return m_hasAiFunction;
    }

    bool EntityModel::hasPopFunction()
    {
        return m_hasPopFunction;
    }

}
