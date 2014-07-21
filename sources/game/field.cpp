#include "field.h"
#include "../engine/engine.h"

namespace game
{

    Field::Field()
    {
        reset();
    }

    void Field::reset()
    {
        const int FIELD_WIDTH  = 700;
        const int FIELD_HEIGHT = 1080;

        if (engine::getHeight() > 0)
        {
            const int SCREEN_WIDTH = engine::getWidth() * FIELD_HEIGHT / engine::getHeight();

            m_screenMinX = (FIELD_WIDTH - SCREEN_WIDTH) / 2;
            m_screenMaxX = FIELD_WIDTH - m_screenMinX;
            m_screenMinY = 0;
            m_screenMaxY = FIELD_HEIGHT;

            m_minX = 0;
            m_maxX = FIELD_WIDTH;
            m_minY = m_screenMinY;
            m_maxY = m_screenMaxY;
        }
    }

    const int Field::getScreenMinX()
    {
        return m_screenMinX;
    }

    const int Field::getScreenMaxX()
    {
        return m_screenMaxX;
    }

    const int Field::getScreenMinY()
    {
        return m_screenMinY;
    }

    const int Field::getScreenMaxY()
    {
        return m_screenMaxY;
    }

    const int Field::getMinX()
    {
        return m_minX;
    }

    const int Field::getMaxX()
    {
        return m_maxX;
    }

    const int Field::getMinY()
    {
        return m_minY;
    }

    const int Field::getMaxY()
    {
        return m_maxY;
    }

    const int Field::getCenterX()
    {
        return (m_minX + m_maxX) / 2;
    }

    const int Field::getCenterY()
    {
        return (m_minY + m_maxY) / 2;
    }

    bool Field::isInFieldX(int x)
    {
        return x >= getMinX() && x <= getMaxX();
    }

    bool Field::isInFieldY(int y)
    {
        return y >= getMinY() && y <= getMaxY();
    }

    bool Field::isInField(engine::Vector2d pos)
    {
        return isInFieldX(pos.x) && isInFieldY(pos.y);
    }

    float Field::getDistanceToFieldX(float x)
    {
        float distance = 0;

        if (x < getMinX())
            distance = getMinX() - x;

        else if (x > getMaxX())
            distance = x - getMaxX();

        return distance;
    }
}
