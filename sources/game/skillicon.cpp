#include "../engine/pi.h"

#include "skillicon.h"

namespace game
{

    SkillIcon::SkillIcon(std::string icon, std::string loadingIcon)
    {
        m_icon = engine::graphics::getTexture(icon);
        m_loadingIcon = engine::graphics::getTexture(loadingIcon);
    }

    void SkillIcon::show(float loading, engine::Vector3d pos)
    {
        m_icon->show(pos);

        float angle = (1 - loading) * 2 * M_PI;

        if (angle > 0 && angle <= 2 * M_PI)
        {
            if (angle >= 7.f / 8.f * 2 * M_PI)
            {
                std::vector<engine::Vector2d> points;

                points.push_back(engine::Vector2d(-0.5, -0.5));
                points.push_back(engine::Vector2d(-0.5,  0.5));
                points.push_back(engine::Vector2d(   0,  0.5));
                points.push_back(engine::Vector2d(   0, -0.5));

                m_loadingIcon->showPolygon(pos, points);

                points.clear();

                points.push_back(engine::Vector2d(   0,  0.5));
                points.push_back(engine::Vector2d( 0.5,  0.5));
                points.push_back(engine::Vector2d( 0.5, -0.5));
                points.push_back(engine::Vector2d(1 / tan(angle - M_PI / 2) / 2, -0.5));
                points.push_back(engine::Vector2d(   0,    0));

                m_loadingIcon->showPolygon(pos, points);
            }
            else if (angle >= 5.f / 8.f * 2 * M_PI)
            {
                std::vector<engine::Vector2d> points;

                points.push_back(engine::Vector2d(-0.5, -0.5));
                points.push_back(engine::Vector2d(-0.5,  0.5));
                points.push_back(engine::Vector2d(   0,  0.5));
                points.push_back(engine::Vector2d(   0, -0.5));

                m_loadingIcon->showPolygon(pos, points);

                points.clear();

                points.push_back(engine::Vector2d(   0,  0  ));
                points.push_back(engine::Vector2d(   0,  0.5));
                points.push_back(engine::Vector2d( 0.5,  0.5));
                points.push_back(engine::Vector2d( 0.5,  1 / tan(angle) / 2));

                m_loadingIcon->showPolygon(pos, points);
            }
            else if (angle >= 4.f / 8.f * 2 * M_PI)
            {
                std::vector<engine::Vector2d> points;

                points.push_back(engine::Vector2d(-0.5, -0.5));
                points.push_back(engine::Vector2d(-0.5,  0.5));
                points.push_back(engine::Vector2d(   0,  0.5));
                points.push_back(engine::Vector2d(   0, -0.5));

                m_loadingIcon->showPolygon(pos, points);

                points.clear();

                points.push_back(engine::Vector2d(   0,  0  ));
                points.push_back(engine::Vector2d(   0,  0.5));
                points.push_back(engine::Vector2d(-1 / tan(angle - M_PI / 2) / 2,  0.5));

                m_loadingIcon->showPolygon(pos, points);
            }
            else if (angle >= 3.f / 8.f * 2 * M_PI)
            {
                std::vector<engine::Vector2d> points;

                points.push_back(engine::Vector2d(-0.5, -0.5));
                points.push_back(engine::Vector2d(-0.5,  0.5));
                points.push_back(engine::Vector2d(-1 / tan(angle - M_PI / 2) / 2,  0.5));
                points.push_back(engine::Vector2d(   0,    0));
                points.push_back(engine::Vector2d(   0, -0.5));

                m_loadingIcon->showPolygon(pos, points);
            }
            else if (angle >= 1.f / 8.f * 2 * M_PI)
            {
                std::vector<engine::Vector2d> points;

                points.push_back(engine::Vector2d(-0.5, -0.5));
                points.push_back(engine::Vector2d(-0.5, -1 / tan(angle) / 2));
                points.push_back(engine::Vector2d(   0,    0));
                points.push_back(engine::Vector2d(   0, -0.5));

                m_loadingIcon->showPolygon(pos, points);
            }
            else
            {
                std::vector<engine::Vector2d> points;

                points.push_back(engine::Vector2d(1 / tan(angle - M_PI / 2) / 2, -0.5));
                points.push_back(engine::Vector2d(   0,    0));
                points.push_back(engine::Vector2d(   0, -0.5));

                m_loadingIcon->showPolygon(pos, points);
            }
        }
    }

}
