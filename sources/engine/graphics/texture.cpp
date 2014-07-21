#include <iostream>
#include <map>
#include <string>
#include "texture.h"
#include "heightmap.h"
#include "../exception.h"
#include "../pi.h"

namespace engine
{
    namespace graphics
    {

        Texture::Texture(std::string filename)
        {
            filename = "resources/images/" + filename;
            if (!loadFromFile(filename))
                throw Exception((std::string("Error loading ")+filename).c_str());

            glGenTextures(1, &m_texture);
            bind();
            gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, getSize().x, getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, getPixelsPtr());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            float w = getSize().x / 2;
            float h = getSize().y / 2;

            m_vertices[0] = -w; m_vertices[1] = -h;
            m_vertices[2] =  w; m_vertices[3] = -h;
            m_vertices[4] =  w; m_vertices[5] =  h;
            m_vertices[6] = -w; m_vertices[7] =  h;
        }

        void Texture::show()
        {
            static const float tex_coords[8] = {0,0, 1,0, 1,1, 0,1};

            bind();
            glVertexPointer(2, GL_FLOAT, 0, m_vertices);
            glTexCoordPointer(2, GL_FLOAT, 0, tex_coords);
            glDrawArrays(GL_QUADS, 0, 4);
        }
        
        void Texture::showFlatten()
        {
            Texture::show();
        }

        void Texture::show(Vector3d pos, Vector3d rotation, ColorRGBA c, float scale)
        {
            static const float f = 180 / M_PI;
            c.use();
            glPushMatrix();
            glTranslated(pos.x, pos.y, pos.z);
            glScaled(scale, scale, 1);
            glRotated(rotation.z * f, 0, 0, 1);
            glRotated(rotation.x * f, 0, 1, 0);
            glRotated(rotation.y * f, 1, 0, 0);
            show();
            glPopMatrix();
        }
        
        void Texture::showFlatten(Vector3d pos, Vector3d rotation, ColorRGBA c, float scale)
        {
            static const float f = 180 / M_PI;
            c.use();
            glPushMatrix();
            glTranslated(pos.x, pos.y, pos.z);
            glScaled(scale, scale, 1);
            glRotated(rotation.z * f, 0, 0, 1);
            glRotated(rotation.x * f, 0, 1, 0);
            glRotated(rotation.y * f, 1, 0, 0);
            showFlatten();
            glPopMatrix();
        }

        void Texture::showPolygon(Vector2d pos, const std::vector<Vector2d>& points)
        {
            ColorRGBA(255, 255, 255, 255).use();
            glPushMatrix();
            glTranslated(pos.x, pos.y, 0);

            int numPoints = points.size();
            float* tex_coords = new float[numPoints * 2];
            float* vertices = new float[numPoints * 2];

            std::vector<Vector2d>::const_iterator end = points.end();
            int i = 0;
            for (std::vector<Vector2d>::const_iterator it = points.begin(); it != end; it++)
            {
                int xIndex = i * 2;
                int yIndex = i * 2 + 1;
                tex_coords[xIndex] = it->x + 0.5;
                tex_coords[yIndex] = it->y + 0.5;
                vertices[xIndex] = it->x * getSize().x;
                vertices[yIndex] = it->y * getSize().y;
                i++;
            }

            bind();
            glVertexPointer(2, GL_FLOAT, 0, vertices);
            glTexCoordPointer(2, GL_FLOAT, 0, tex_coords);
            glDrawArrays(GL_TRIANGLE_FAN, 0, numPoints);

            delete tex_coords;

            glPopMatrix();
        }

        void Texture::showPerspective(Vector2d a, Vector2d b, Vector2d c, Vector2d d)
        {
            ColorRGBA(255, 255, 255, 255).use();

            Vector2d e((a.x + b.x) / 2, a.y + (c.y - a.y) * (b.x - a.x) / (b.x - a.x + c.x - d.x));

            static const unsigned char indices[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
            static const float tex_coords[] = {
                0,0, 1,0, 0.5,0.5,
                1,0, 1,1, 0.5,0.5,
                1,1, 0,1, 0.5,0.5,
                0,1, 0,0, 0.5,0.5
            };

            const float vertices[] = {
                a.x,a.y, b.x,b.y, e.x,e.y,
                b.x,b.y, c.x,c.y, e.x,e.y,
                c.x,c.y, d.x,d.y, e.x,e.y,
                d.x,d.y, a.x,a.y, e.x,e.y,
            };

            glEnable(GL_TEXTURE_2D);
            bind();
            glVertexPointer(2, GL_FLOAT, 0, vertices);
            glTexCoordPointer(2, GL_FLOAT, 0, tex_coords);
            glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, indices);
        }

        void Texture::setSmooth(bool smooth)
        {
            glBindTexture(GL_TEXTURE_2D, m_texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smooth ? GL_LINEAR : GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smooth ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST);
        }

        void Texture::bind()
        {
            glBindTexture(GL_TEXTURE_2D, m_texture);
        }

        std::map<std::string, Texture*> textures;

        Texture* getTexture(std::string filename)
        {
            if (filename == "")
                return NULL;

            Texture* texture;
            std::map<std::string, Texture*>::iterator it = textures.find(filename);
            if (it != textures.end())
            {
                texture = it->second;
            }
            else
            {
                size_t extension = filename.find('.');

                if (extension != std::string::npos)
                    texture = new Texture(filename);

                else
                    texture = new HeightMap(filename);

                textures[filename] = texture;
            }
            return texture;
        }

        void freeTextures()
        {
            for (std::map<std::string, Texture*>::iterator it = textures.begin(); it != textures.end(); it++)
                delete it->second;

            textures.clear();
        }

    }
}
