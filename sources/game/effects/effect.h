#ifndef GAME_EFFECTS_EFFECTS_H
 #define GAME_EFFECTS_EFFECTS_H

#include <string>

#include "../../engine/vector2d.h"
#include "../../engine/graphics/texture.h"

namespace game
{
    namespace effects
    {

        class Effect
        {
            public:
                enum Layer
                {
                    ABOVEALL,
                    ABOVE,
                    BELOWALL,
                    BELOW,

                    NUMLAYERS
                };

            public:
                Effect(std::string texture, float duration, engine::Vector3d position, Layer layer);
                virtual ~Effect();

                virtual void show() = 0;
                float getProgression();
                Layer getLayer();

            protected:
                void addStep(float time, bool lastStep = false);
                void calcCurrentStep();
                float getStepProgression();

                float m_begin;
                float m_duration;
                engine::Vector3d m_position;
                engine::graphics::Texture* m_texture;
                Layer m_layer;

                int m_currentStepIndex;
                std::vector<float>::iterator m_currentStep;
                std::vector<float>::iterator m_lastStep;
                std::vector<float> m_steps;
        };

        void init();
        void showAboveAll();
        void showAbove();
        void showBelowAll();
        void showBelow();
        void show(Effect::Layer layer);
        void add(Effect* effect);

    }
}

#endif
