#ifndef FSM_H
#define FSM_H

using namespace std;

#include <map>
#include "state.h"

class FSM {
public:
	string activeState;
	map<string, State> states;

	FSM(map<string, State>& _states);
	FSM();
	void addState(const string& stateName, const State& state);
	void setCurState(const string& stateName);
	void triggeronEnterCallback();
	void evaluate(const string& event);
};

#endif
