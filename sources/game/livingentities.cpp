#include "livingentities.h"
#include "entities/unit.h"

namespace game
{

    LivingEntities::LivingEntities()
    {
        m_sideEntities[Entity::ENEMY] = std::vector<Entity*>();
        m_sideEntities[Entity::ALLY]  = std::vector<Entity*>();
    }

    void LivingEntities::add(Entity* entity)
    {
        m_entities.push_back(entity);
        m_sideEntities[entity->getSide()].push_back(entity);
    }

    void LivingEntities::addAfterMoving(Entity* entity)
    {
        m_addedEntities.push_back(entity);
    }

    void LivingEntities::applyAdd()
    {
        std::vector<Entity*>::iterator end = m_addedEntities.end();
        for (std::vector<Entity*>::iterator it = m_addedEntities.begin(); it != end; it++)
            add(*it);

        m_addedEntities.clear();
    }

    void LivingEntities::remove(Entity* entity)
    {
        m_removedEntities.insert(entity);
    }

    void LivingEntities::applyRemove()
    {
        std::set<Entity*>::iterator end = m_removedEntities.end();
        for (std::set<Entity*>::iterator it = m_removedEntities.begin(); it != end; it++)
        {
            std::vector<Entity*>::iterator it1 = find(m_entities.begin(), m_entities.end(), *it);
            m_entities.erase(it1);

            Entity::Side side = (*it)->getSide();
            std::vector<Entity*>::iterator it2 = find(m_sideEntities[side].begin(), m_sideEntities[side].end(), *it);
            m_sideEntities[side].erase(it2);

            //delete *it;
            (*it)->destroy();
        }
        m_removedEntities.clear();
    }

    int LivingEntities::getNum()
    {
        return m_entities.size() + m_addedEntities.size();
    }

    int LivingEntities::getNumBySide(Entity::Side side)
    {
        int addedNum = 0;
        std::vector<Entity*>::iterator end = m_addedEntities.end();
        for (std::vector<Entity*>::iterator it = m_addedEntities.begin(); it != end; it++)
        {
            if ((*it)->getSide() == side)
                addedNum++;
        }
        return m_sideEntities[side].size() + addedNum;
    }

    Entity* LivingEntities::getOldestBySide(Entity::Side side)
    {
        return m_sideEntities[side][0];
    }

    const std::vector<Entity*>& LivingEntities::getEntitiesBySide(Entity::Side side)
    {
        return m_sideEntities[side];
    }

    const std::vector<Entity*>& LivingEntities::getEntities()
    {
        return m_entities;
    }

    const std::map<Entity::Side, std::vector<Entity*> >& LivingEntities::getSideEntities()
    {
        return m_sideEntities;
    }

    void LivingEntities::moveForward(float frameTime)
    {
        std::vector<game::Entity*>::iterator end = m_entities.end();
        for (std::vector<game::Entity*>::iterator it = m_entities.begin(); it != end; it++)
        {
            (*it)->moveForward(frameTime);

            if ((*it)->isOutOfField())
                remove(*it);
        }
        applyRemove();
        applyAdd();
    }

    void LivingEntities::showShadow()
    {
        std::vector<game::Entity*>::iterator end = m_entities.end();
        for (std::vector<game::Entity*>::iterator it = m_entities.begin(); it != end; it++)
            (*it)->showShadow();
    }

    void LivingEntities::show(DisplayManager* dm)
    {
        std::vector<game::Entity*>::iterator end = m_entities.end();
        for (std::vector<game::Entity*>::iterator it = m_entities.begin(); it != end; it++)
            dm->add(*it);
    }

    void LivingEntities::showAndFire(DisplayManager* dm)
    {
        std::vector<game::Entity*>::iterator end = m_entities.end();
        for (std::vector<game::Entity*>::iterator it = m_entities.begin(); it != end; it++)
        {
            dm->add(*it);
            ((Unit*)*it)->fire();
        }
    }

}
