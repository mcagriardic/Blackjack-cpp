#pragma once

#include "FSM/transitions.h"
#include "FSM/state.h"

class FSM {
public:
	string curState;
	map<string, State> states;

	FSM (map<string, State> _states)
		: states(_states)
	{ ;	}

	FSM() = default;

	void addState(string stateTag, State state)
	{
		states[stateTag] = state;
	}

	void setCurState(string stateName)
	{
		curState = stateName;
	}

	string evaluate(string activateState, string event)
	{
		for (Transition& transition : states[activateState].transitions) {
			if (
					transition.event_.compare(event) == 0 
						&& 
					(
						!transition.guard
						||
						transition.guard()
					)
				)
			{
				return transition.targetState;
			}
		}
	}

};
