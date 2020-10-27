#include "state.h"

State::State(const string& _state, vector<Transition> _transitions, function<void()> _onEnter)
	: state(_state), transitions(_transitions), onEnter(_onEnter)
{;}

State::State() = default;

void State::onEnterCallback() {
	onEnter();
}
