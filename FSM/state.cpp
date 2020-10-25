#include "state.h"

State::State(string _state, vector<Transition> _transitions)
	: state(_state), transitions(_transitions)
{
	;
}

State::State() = default;
