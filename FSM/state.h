#pragma once

class State {
public:
	string state;
	vector<Transition> transitions;

	State(string _state, vector<Transition> _transitions)
		: state(_state), transitions(_transitions)
	{;}

	State() = default;

};