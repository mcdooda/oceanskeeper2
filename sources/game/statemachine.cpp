#include <cstdlib>
#include "statemachine.h"

namespace game
{

    StateMachine::StateMachine()
    {
        m_state = NULL;
    }

    StateMachine::~StateMachine()
    {
        if (m_state != NULL)
            delete m_state;
    }

    states::State* StateMachine::getState()
    {
        return m_state;
    }

    void StateMachine::setState(states::State* state)
    {
        if (m_state != NULL)
            delete m_state;

        m_state = state;
    }

    void StateMachine::loop()
    {
        m_state->loop();
    }

}
