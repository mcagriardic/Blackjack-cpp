#include "FSM.h"

FSM::FSM(map<string, State> _states)
	: states(_states)
{
	;
}

FSM::FSM() = default;

void FSM::addState(string stateTag, State state)
{
	states[stateTag] = state;
}

void FSM::setCurState(string stateName)
{
	curState = stateName;
}

string FSM::evaluate(string activateState, string event)
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