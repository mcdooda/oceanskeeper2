#ifndef GAME_MODELS_SHIPMODEL_H
 #define GAME_MODELS_SHIPMODEL_H

#include "unitmodel.h"

namespace game
{

    class ShipModel : public UnitModel
    {
        public:
            ShipModel();

            MissileModel* getSpecialMissileModel();

            void setLevel(int level);

        private:
            MissileModel* m_specialMissileModel;
    };

}

#endif
