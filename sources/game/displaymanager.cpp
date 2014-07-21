#include "displaymanager.h"

namespace game
{

    DisplayManager::DisplayManager()
    {
        clear();
    }

    void DisplayManager::showAll()
    {
        sort();
        for (int i = 0; i < m_numEntities; i++)
            m_entities[i]->show();
    }

    void DisplayManager::clear()
    {
        m_numEntities = 0;
    }

    void DisplayManager::add(Entity* entity)
    {
        if (m_numEntities < MAX_ENTITIES)
            m_entities[m_numEntities++] = entity;
    }

    int compareAltitude(const void* a, const void* b)
    {
        Entity* ea = *(Entity**)a;
        Entity* eb = *(Entity**)b;

        int c = ea->getZ() - eb->getZ();

        if (c == 0)
        {
            c = ea->getY() - eb->getY();
            if (c == 0)
            {
                c = ea->getId() - eb->getId();
            }
        }

        return c;
    }

    void DisplayManager::sort()
    {
        qsort(m_entities, m_numEntities, sizeof(Entity*), compareAltitude);
    }

}
