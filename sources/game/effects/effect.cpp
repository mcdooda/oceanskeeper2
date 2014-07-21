#include <map>
#include <vector>

#include "../../engine/time.h"

#include "effect.h"

namespace game
{
    namespace effects
    {

        Effect::Effect(std::string texture, float duration, engine::Vector3d position, Layer layer) : m_position(position)
        {
            m_texture = engine::graphics::getTexture(texture);
            m_duration = duration;
            m_begin = engine::time::getTime();
            m_layer = layer;
            addStep(0);
            add(this);
        }

        Effect::~Effect()
        {

        }

        float Effect::getProgression()
        {
            return (engine::time::getTime() - m_begin) / m_duration;
        }

        Effect::Layer Effect::getLayer()
        {
            return m_layer;
        }

        void Effect::addStep(float time, bool lastStep)
        {
            m_steps.push_back(time);
            if (lastStep)
            {
                m_currentStepIndex = 0;
                m_currentStep = m_steps.begin();
                m_lastStep = m_steps.end();
            }
        }

        void Effect::calcCurrentStep()
        {
            float time = (engine::time::getTime() - m_begin);
            while (m_currentStep + 1 != m_lastStep && time >= *(m_currentStep + 1))
            {
                m_currentStepIndex++;
                m_currentStep++;
            }
        }

        float Effect::getStepProgression()
        {
            float begin = *m_currentStep;
            float end = m_duration;

            std::vector<float>::iterator nextStep = m_currentStep + 1;
            if (m_lastStep != nextStep)
                end = *nextStep;

            return (engine::time::getTime() - begin - m_begin) / (end - begin);
        }


        std::vector<Effect*> effects[Effect::NUMLAYERS];

        void init()
        {
            effects[Effect::ABOVEALL] = std::vector<Effect*>();
            effects[Effect::ABOVE]    = std::vector<Effect*>();
            effects[Effect::BELOW]    = std::vector<Effect*>();
        }

        void showAboveAll()
        {
            show(Effect::ABOVEALL);
        }

        void showAbove()
        {
            show(Effect::ABOVE);
        }

        void showBelowAll()
        {
            show(Effect::BELOWALL);
        }

        void showBelow()
        {
            show(Effect::BELOW);
        }

        void show(Effect::Layer layer)
        {
            std::vector<Effect*> removedEffects;
            std::vector<Effect*>::iterator end;

            std::vector<Effect*>* layerEffects = &effects[layer];

            end = layerEffects->end();
            for (std::vector<Effect*>::iterator it = layerEffects->begin(); it != end; it++)
            {
                if ((*it)->getProgression() >= 1)
                    removedEffects.push_back(*it);

                else
                    (*it)->show();
            }

            end = removedEffects.end();

            for (std::vector<Effect*>::iterator it = removedEffects.begin(); it != end; it++)
            {
                std::vector<Effect*>::iterator it1 = find(layerEffects->begin(), layerEffects->end(), *it);
                Effect* effect = *it1;
                layerEffects->erase(it1);
                delete effect;
            }
        }

        void add(Effect* effect)
        {
            effects[effect->getLayer()].push_back(effect);
        }

    }
}
