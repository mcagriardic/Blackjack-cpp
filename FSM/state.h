#ifndef STATE_H
#define STATE_H

#include <vector>

#include "transition.h"

class State {
public:
	string state;
	vector<Transition> transitions;
	function<void()> onEnter;
	function<void()> onExit;

	State(const string& _state, vector<Transition> _transitions, function<void()> _onEnter);
	State();
	void onEnterCallback();
};

#endif

