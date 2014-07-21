#include <cstdlib>
#include "random.h"

namespace engine
{
    namespace random
    {

        int rint(int min, int max)
        {
            return rand() % (max - min) + min;
        }

        float rfloat(float min, float max)
        {
            return (rand() / (float)RAND_MAX) * (max - min) + min;
        }

    }
}
