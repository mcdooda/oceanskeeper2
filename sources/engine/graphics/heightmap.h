#ifndef ENGINE_GRAPHICS_HEIGHTMAP_H
 #define ENGINE_GRAPHICS_HEIGHTMAP_H

#include "texture.h"

namespace engine
{
    namespace graphics
    {

        struct Vertex3d
        {
            float x, y, z;
            float tx, ty;
            unsigned char r, g, b, a;
            unsigned int ox, oy;
        };

        class HeightMap : public Texture
        {
            public:
                HeightMap(std::string heightmap, float multiplier = 0.0017);

            protected:
                virtual void show();

            private:
                float getHeight(unsigned int x, unsigned int y);
                sf::Color getColor(float x, float y);
                void generateGlTexture();
                void computeHeightmap();

                Texture* m_heightmap;

                Vertex3d* m_model;
                unsigned int* m_indices;
                unsigned int m_num_indices;

                float m_multiplier;
        };

    }
}

#endif
