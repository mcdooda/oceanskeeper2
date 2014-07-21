#ifndef GAME_DISPLAYMANAGER_H
 #define GAME_DISPLAYMANAGER_H

#include "entities/entity.h"

#define MAX_ENTITIES 2000

namespace game
{

    class DisplayManager
    {
        public:
            DisplayManager();
            
            void showAll();
            void clear();
            
            void add(Entity* entity);
            
        private:
            void sort();
            
            game::Entity* m_entities[MAX_ENTITIES];
            int m_numEntities;
    };

}

#endif
