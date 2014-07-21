#ifndef GAME_LIVINGENTITIES_H
 #define GAME_LIVINGENTITIES_H

#include <vector>
#include <map>
#include <set>
#include "entities/entity.h"
#include "displaymanager.h"

namespace game
{

    class LivingEntities
    {
        public:
            LivingEntities();

            void add(Entity* entity);
            void addAfterMoving(Entity* entity);
            void applyAdd();
            void remove(Entity* entity);
            void applyRemove();

            int getNum();
            int getNumBySide(Entity::Side side);

            Entity* getOldestBySide(Entity::Side side);

            const std::vector<Entity*>& getEntitiesBySide(Entity::Side side);
            const std::vector<Entity*>& getEntities();
            const std::map<Entity::Side, std::vector<Entity*> >& getSideEntities();

            void moveForward(float frameTime);
            void showShadow();
            void show(DisplayManager* dm);
            void showAndFire(DisplayManager* dm);

        private:
            std::vector<Entity*> m_entities;
            std::map<Entity::Side, std::vector<Entity*> > m_sideEntities;
            std::set<Entity*> m_removedEntities;
            std::vector<Entity*> m_addedEntities;
    };

    class LivingUnits    : public LivingEntities {};
    class LivingMissiles : public LivingEntities {};

}

#endif
