#include "StateStack.h"


StateStack::StateStack():
     m_states(),
     m_newState(),
     m_isAdding(false),
     m_isReplacing(false),
     m_isRemoving(false)
{

}

void StateStack::AddState(StateRef newState, bool isReplacing)
{
    m_isAdding = true;
    m_isReplacing = isReplacing;

    m_newState = std::move( newState );
}

void StateStack::RemoveState()
{
    m_isRemoving = true;
}

void StateStack::ProcessStateChanges()
{
    if (m_isRemoving && !m_states.empty())
    {
        m_states.pop();

        if (!m_states.empty())
            m_states.top()->Resume();

        m_isRemoving = false;
    }

    if (m_isAdding)
    {
        if (!m_states.empty())
        {
            if (m_isReplacing)
                m_states.pop();
            else
                m_states.top()->Pause();
        }

        m_states.push(std::move(m_newState));
        m_states.top()->Init();
        m_isAdding = false;
    }
}

StateStack::StateRef& StateStack::GetActiveState()
{
    if(m_states.empty())throw std::range_error("Stack is emptey");
    return m_states.top();
}