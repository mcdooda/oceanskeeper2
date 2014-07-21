#ifndef GAME_MODELS_UNITMODEL_H
 #define GAME_MODELS_UNITMODEL_H

#include <string>
#include "../../engine/graphics/texture.h"

#include "entitymodel.h"
#include "missilemodel.h"

namespace game
{

    class UnitModel : public EntityModel
    {
        public:
            UnitModel(std::string modelName, std::string missileModelName, float maxHealth, float speed, std::string texture, bool hasAiFunction, bool hasPopFunction);

            float getMaxHealth();
            MissileModel* getMissileModel();

        protected:
            float m_maxHealth;
            MissileModel* m_missileModel;
    };

    void registerUnitModel(std::string modelName, UnitModel* model);
    UnitModel* getUnitModel(std::string modelName);
    void freeUnitModels();

}

#endif
