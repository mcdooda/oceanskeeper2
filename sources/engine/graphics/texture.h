#ifndef ENGINE_GRAPHICS_TEXTURE_H
 #define ENGINE_GRAPHICS_TEXTURE_H

#include <string>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "../vector3d.h"
#include "color.h"

namespace engine
{
    namespace graphics
    {

        class Texture : public sf::Image
        {
            public:
                Texture(std::string filename);

                void show(Vector3d pos, Vector3d rotation = Vector3d(), ColorRGBA c = ColorRGBA(255, 255, 255, 255), float scale = 1);
                void showFlatten(Vector3d pos, Vector3d rotation = Vector3d(), ColorRGBA c = ColorRGBA(255, 255, 255, 255), float scale = 1);

                void showPolygon(Vector2d pos, const std::vector<Vector2d>& points);
                void showPerspective(Vector2d a, Vector2d b, Vector2d c, Vector2d d);

                void setSmooth(bool smooth);

                void bind();

            protected:
                virtual void show();
                virtual void showFlatten();

            private:

                GLuint m_texture;
                float m_vertices[8];
        };

        Texture* getTexture(std::string filename);
        void freeTextures();

    }
}

#endif
