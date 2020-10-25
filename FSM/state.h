#ifndef STATE_H
#define STATE_H

#include <vector>

#include "transition.h"

class State {
public:
	string state;
	vector<Transition> transitions;

	State(string _state, vector<Transition> _transitions);
	State();
};

#endif