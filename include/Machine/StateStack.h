#pragma once

#include <memory>
#include <stack>

#include "State.h"

/* Manager states */
class StateStack
{
public:
    typedef std::shared_ptr<State> StateRef;
public:
    StateStack();
    ~StateStack() = default;

    void AddState( StateRef, bool = true );
    void RemoveState();

    void ProcessStateChanges();
    bool isEmpty();

    StateRef& GetActiveState();

private:
    std::stack< StateRef > m_states;
    StateRef m_newState;

    bool m_isRemoving;
    bool m_isAdding;
    bool m_isReplacing;

};
