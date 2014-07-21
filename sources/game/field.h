#ifndef GAME_FIELD_H
 #define GAME_FIELD_H

#include "../engine/vector2d.h"

namespace game
{

    class Field
    {
        public:
            Field();

            void reset();

            const int getScreenMinX();
            const int getScreenMaxX();
            const int getScreenMinY();
            const int getScreenMaxY();

            const int getMinX();
            const int getMaxX();
            const int getMinY();
            const int getMaxY();
            const int getCenterX();
            const int getCenterY();

            bool isInFieldX(int x);
            bool isInFieldY(int y);
            bool isInField(engine::Vector2d pos);

            float getDistanceToFieldX(float x);

        private:

            int m_screenMinX;
            int m_screenMaxX;
            int m_screenMinY;
            int m_screenMaxY;

            int m_minX;
            int m_maxX;
            int m_minY;
            int m_maxY;
    };

}

#endif
