#include <iostream>

#include "../../engine/engine.h"
#include "../../engine/input.h"
#include "../../engine/time.h"
#include "../../engine/lua/lua.h"
#include "../../engine/singleton.h"
#include "../../engine/graphics/shader/program.h"
#include "../../engine/vector3d.h"

#include "game.h"
#include "../models/unitmodel.h"
#include "../models/missilemodel.h"
#include "../livingentities.h"
#include "../entities/ship.h"
#include "../entities/laser.h"
#include "../effects/text.h"
#include "../luafunctions/luafunctions.h"
#include "../luafunctions/entity.h"
#include "../luafunctions/effect.h"
#include "../luafunctions/music.h"
#include "../luafunctions/sample.h"
#include "../models/nomissilemodel.h"
#include "../models/shieldmodel.h"
#include "../models/shipmodel.h"
#include "../field.h"
#include "../score.h"
#include "../skillicon.h"

namespace game
{
    namespace states
    {

        Game::Game()
        {
            m_endShown = false;
            m_missionFailed = false;
            m_missionFailedShown = false;
            initGame();

            engine::graphics::shader::VertexShader vs("resources/shaders/vs.glsl");
            engine::graphics::shader::FragmentShader fs("resources/shaders/fs.glsl");

            m_program.attachShader(&vs);
            m_program.attachShader(&fs);

            m_program.link();
            m_program.use();
        }

        Game::~Game()
        {
            freeUnitModels();
            freeMissileModels();
        }

        void Game::loop()
        {
            while (engine::isRunning())
            {
                // handle events
                handleEvents();

                // move all units
                float frameTime = engine::time::getFrameTime();

                //m_program.setUniform("factor", new engine::graphics::shader::Uniform1f(time));

                S(LivingMissiles)->moveForward(frameTime);
                S(LivingUnits)->moveForward(frameTime);

                // check mission failure
                m_missionFailed = !S(Ship)->isAlive();

                bool levelEnded = engine::lua::isCoroutineDead("level");

                if (m_missionFailed)
                {
                    if (!m_missionFailedShown)
                    {
                        new game::effects::text::MissionFailed();
                        m_missionFailedShown = true;
                    }
                }
                else if (!levelEnded)
                    engine::lua::resumeCoroutine("level");

                // display units
                engine::graphics::initDisplay();

                const std::vector<Entity*>& missiles = S(LivingMissiles)->getEntities();
                std::vector<Entity*>::const_iterator begin, end, it;

                begin = missiles.begin();
                end = missiles.end();

                const std::map<Entity::Side, std::vector<Entity*> >& units = S(LivingUnits)->getSideEntities();
                std::map<Entity::Side, std::vector<Entity*> >::const_iterator begin1, end1, it1;

                // for each missile
                for (it = begin; it != end; it++)
                {
                    game::Missile* missile = (Missile*) *it;

                    begin1 = units.begin();
                    end1 = units.end();

                    if (missile->isLaser())
                    {
                        Laser* laser = (Laser*) missile;
                        laser->setTarget(NULL);
                        laser->grow();
                        // for each side of entity
                        // it1->first is a side, it1->second is a vector of entities of this side
                        for (it1 = begin1; it1 != end1; it1++)
                        {
                            if (it1->first != missile->getSide())
                            {
                                const std::vector<Entity*>& sideUnits = it1->second;
                                std::vector<Entity*>::const_iterator begin2, end2, it2;

                                begin2 = sideUnits.begin();
                                end2 = sideUnits.end();
                                // for each enemy unit
                                for (it2 = begin2; it2 != end2; it2++)
                                {
                                    Unit* unit = (Unit*) *it2;
                                    laser->checkTarget(unit);
                                }
                            }
                        }
                        Unit* target = (Unit*) laser->getTarget();
                        if (target != NULL)
                        {
                            if (target->loseHealth(laser->getDamage() * engine::time::getFrameTime()))
                                S(LivingUnits)->remove(target);
                        }
                    }
                    else
                    {
                        // for each side of entity
                        // it1->first is a side, it1->second is a vector of entities of this side
                        for (it1 = begin1; it1 != end1; it1++)
                        {
                            if (it1->first != missile->getSide())
                            {
                                const std::vector<Entity*>& sideUnits = it1->second;
                                std::vector<Entity*>::const_iterator begin2, end2, it2;

                                begin2 = sideUnits.begin();
                                end2 = sideUnits.end();

                                // for each enemy unit
                                for (it2 = begin2; it2 != end2; it2++)
                                {
                                    Unit* unit = (Unit*) *it2;
                                    if (missile->collides(unit))
                                    {
                                        if (unit->loseHealth(missile->getDamage()))
                                            S(LivingUnits)->remove(unit);

                                        S(LivingMissiles)->remove(missile);

                                    }
                                }

                            }
                        }
                    }
                }

                // remove dead entities
                S(LivingMissiles)->applyRemove();
                S(LivingUnits)->applyRemove();

                // show the "sea"
                static engine::graphics::Texture* sea = NULL;
                if (sea == NULL)
                {
                    sea = engine::graphics::getTexture("background/sea.png");
                    sea->setSmooth(false);
                }
                engine::graphics::drawRectangle(
                    engine::Vector2d(S(Field)->getMinX(), S(Field)->getMinY()),
                    engine::Vector2d(S(Field)->getMaxX(), S(Field)->getMaxY()),
                    engine::graphics::ColorRGBA(18, 100, 224, 255),
                    sea
                );

                // show effects below entities
                game::effects::showBelowAll();
                game::effects::showBelow();

                // show entities shadows
                S(LivingUnits)->showShadow();
                S(LivingMissiles)->showShadow();

                // show entities
                static DisplayManager dm;
                S(LivingUnits)->showAndFire(&dm);
                S(LivingMissiles)->show(&dm);
                dm.showAll();
                dm.clear();

                // show effects above entities
                game::effects::showAbove();
                game::effects::showAboveAll();

                static engine::graphics::Texture* shipLifeTexture = engine::graphics::getTexture("units/ship/blue/texture.png");

                static const float ratio = 0.66;
                engine::Vector3d pos(S(Field)->getMaxX() + ratio * shipLifeTexture->getSize().x / 2 + 2, 0, 0);
                const float height = shipLifeTexture->getSize().y * ratio;
                for (int i = 0; i < S(Ship)->getNumLives(); i++)
                {
                    pos.y = S(Field)->getMaxY() - height / 2 - height * i;
                    shipLifeTexture->show(pos, engine::Vector3d(), engine::graphics::ColorRGBA(255, 255, 255, 255), ratio);
                }

                S(Score)->show();

                engine::Vector3d iconPos(S(Field)->getMinX() - 32, S(Field)->getMaxY() - 32, 0);

                {
                    static SkillIcon si("icons/laser.png", "icons/laser_loading.png");
                    si.show(S(Ship)->getSpecialLoading(), iconPos);
                    iconPos.y -= 64;
                }

                engine::graphics::endDisplay();

                // if we reached the end of the level
                if (levelEnded && !m_endShown)
                {
                    new game::effects::text::End();
                    m_endShown = true;
                }
            }
        }

        void Game::initGame()
        {
            using namespace engine::lua;

            effects::init();

            lua_State* L = getState();
            
            // initializing lua libs
            lua::init(L);
            luafunctions::init(L);
            luafunctions::entity::init(L);
            luafunctions::effect::init(L);
            luafunctions::music::init(L);
            luafunctions::sample::init(L);
            
            // registering graphical effects
            doFile("resources/scripts/effects.lua");
            
            // registering missile models
            doFile("resources/scripts/missiles.lua");
            new NoMissileModel();
            
            // registering unit models
            doFile("resources/scripts/units.lua");
            new ShieldModel();
            new ShipModel();

            S(LivingUnits)->add(S(Ship));

            saveCoroutine("level", "resources/scripts/level.lua");

            engine::time::reset();
        }

        void Game::handleEvents()
        {
            bool Z, Q, S, D, ctrl, space;
            engine::Vector2d direction(0, 0);
            static Ship* ship = S(Ship);

            engine::input::captureEvents();

            // quit
            if (engine::input::isJustPressed(engine::input::Keyboard::Escape) || engine::input::isWindowClosed())
                engine::stop();

            // toggle full screen
            if (engine::input::isJustPressed(engine::input::Keyboard::F))
            {
                if (!engine::time::isPauseEnabled())
                {
                    engine::time::pause();
                    new game::effects::text::Pause();
                }
                engine::toggleFullScreen();
                S(Field)->reset();
                engine::graphics::init(
                    engine::graphics::ColorRGBA(0, 0, 0, 0),
                    S(Field)->getScreenMinX(), S(Field)->getScreenMaxX(),
                    S(Field)->getScreenMaxY(), S(Field)->getScreenMinY()
                );
                m_program.use();
            }

            // resize
            if (engine::input::isWindowResized())
            {
                if (!engine::time::isPauseEnabled())
                {
                    engine::time::pause();
                    new game::effects::text::Pause();
                }
                engine::resize();
                S(Field)->reset();
                engine::graphics::init(
                    engine::graphics::ColorRGBA(0, 0, 0, 0),
                    S(Field)->getScreenMinX(), S(Field)->getScreenMaxX(),
                    S(Field)->getScreenMaxY(), S(Field)->getScreenMinY()
                );
            }

            // pause
            if (engine::input::isJustPressed(engine::input::Keyboard::P))
            {
                if (engine::time::isPauseEnabled())
                    engine::time::resume();

                else
                {
                    engine::time::pause();
                    new game::effects::text::Pause();
                }
            }

            // screenshot
            if (engine::input::isJustPressed(engine::input::Keyboard::F12))
            {
                engine::takeScreenShot();
                if (!engine::time::isPauseEnabled())
                {
                    engine::time::pause();
                    new game::effects::text::Pause();
                }
            }

            // moves
            Z = engine::input::isPressed(engine::input::Keyboard::Z) || engine::input::isPressed(engine::input::Keyboard::Up);
            Q = engine::input::isPressed(engine::input::Keyboard::Q) || engine::input::isPressed(engine::input::Keyboard::Left);
            S = engine::input::isPressed(engine::input::Keyboard::S) || engine::input::isPressed(engine::input::Keyboard::Down);
            D = engine::input::isPressed(engine::input::Keyboard::D) || engine::input::isPressed(engine::input::Keyboard::Right);

            // fire
            ctrl  = engine::input::isPressed(engine::input::Keyboard::RControl) || engine::input::isPressed(engine::input::Keyboard::LControl) || engine::input::isMousePressed(engine::input::Mouse::Left);
            space = engine::input::isPressed(engine::input::Keyboard::Space) || engine::input::isMousePressed(engine::input::Mouse::Right);

            if (!m_missionFailed)
            {
                if (Q && !D)
                    direction.x = -1;
                else if (D && !Q)
                    direction.x = 1;
                else
                    direction.x = 0;

                if (Z && !S)
                    direction.y = -1;
                else if (S && !Z)
                    direction.y = 1;
                else
                    direction.y = 0;

                ship->move(direction.normalize() * engine::time::getFrameTime());

                if (!engine::time::isPauseEnabled())
                {
                    if (ctrl)
                        ship->shipFire();

                    else
                        ship->removeLasers();

                    if (space)
                        ship->fireSpecial();
                }
            }
        }

    }
}
