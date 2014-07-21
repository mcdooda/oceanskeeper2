#include <sstream>

#include "shipmodel.h"

namespace game
{

    ShipModel::ShipModel() : UnitModel("Ship", "ShipMissile1", 1, 500, "units/ship/blue", false, false)
    {
        m_specialMissileModel = game::getMissileModel("ShipSpecial1");
    }

    MissileModel* ShipModel::getSpecialMissileModel()
    {
        return m_specialMissileModel;
    }

    void ShipModel::setLevel(int level)
    {
        std::string str;
        std::stringstream ss;

        ss << "ShipMissile" << level;
        ss >> str;
        m_missileModel = game::getMissileModel(str);
        ss.clear();

        ss << "ShipSpecial" << level;
        ss >> str;
        m_specialMissileModel = game::getMissileModel(str);
        //ss.clear();
    }

}
