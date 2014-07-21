#include "heightmap.h"

namespace engine
{
    namespace graphics
    {

        HeightMap::HeightMap(std::string heightmap, float multiplier) : Texture(heightmap + "/texture.png")
        {
            m_heightmap = engine::graphics::getTexture(heightmap + "/heightmap.png");
            m_multiplier = multiplier;
            computeHeightmap();
        }

        void HeightMap::show()
        {
            glEnable(GL_DEPTH_TEST);
            glClear(GL_DEPTH_BUFFER_BIT);
            bind();
            glVertexPointer(3, GL_FLOAT, sizeof(Vertex3d), &m_model[0].x);
            glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex3d), &m_model[0].tx);
            glDrawElements(GL_TRIANGLES, m_num_indices, GL_UNSIGNED_INT, m_indices);
            glDisable(GL_DEPTH_TEST);
        }

        float HeightMap::getHeight(unsigned int x, unsigned int y)
        {
            sf::Color color = m_heightmap->getPixel(x, y);
            return (float) (color.r + color.g + color.b) / 3 * m_multiplier;
        }

        sf::Color HeightMap::getColor(float x, float y)
        {
            return getPixel(x / m_heightmap->getSize().x * getSize().x, y / m_heightmap->getSize().y * getSize().y);
        }

        void HeightMap::computeHeightmap()
        {
            unsigned int width = m_heightmap->getSize().x;
            unsigned int height = m_heightmap->getSize().y;
            unsigned int num_vertices = width * height;

            m_model = new Vertex3d[num_vertices];

            unsigned int x, y, i;

            i = 0;
            for (x = 0; x < width; x++)
            {
                for (y = 0; y < height; y++)
                {
                    Vertex3d* v = &m_model[i];
                    v->ox = x;
                    v->oy = y;
                    v->tx = (float) x / (width - 1);
                    v->ty = (float) y / (height - 1);
                    v->x = ((float) x / (width - 1) - 0.5) * getSize().x;
                    v->y = ((float) y / (height - 1) - 0.5) * getSize().y;
                    v->z = getHeight(x, y) * getSize().x;
                    sf::Color color = getColor(x, y);
                    v->r = color.r;
                    v->g = color.g;
                    v->b = color.b;
                    v->a = color.a;
                    i++;
                }
            }

            m_num_indices = (width - 1) * 6 * (height - 1);
            m_indices = new unsigned int[m_num_indices];

            i = 0;
            for (y = 0; y < height - 1; y++)
            {
                for (x = 0; x < width - 1; x++)
                {
                    if (x < width / 2)
                    {
                        m_indices[i++] = y * width + x;
                        m_indices[i++] = (y + 1) * width + x;
                        m_indices[i++] = (y + 1) * width + x + 1;

                        m_indices[i++] = (y + 1) * width + x + 1;
                        m_indices[i++] = y * width + x + 1;
                        m_indices[i++] = y * width + x;
                    }
                    else
                    {
                        m_indices[i++] = (y + 1) * width + x;
                        m_indices[i++] = y * width + x;
                        m_indices[i++] = y * width + x + 1;

                        m_indices[i++] = y * width + x + 1;
                        m_indices[i++] = (y + 1) * width + x + 1;
                        m_indices[i++] = (y + 1) * width + x;
                    }
                }
            }
        }

    }
}
