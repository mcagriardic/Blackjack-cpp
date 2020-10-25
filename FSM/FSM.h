#ifndef FSM_H
#define FSM_H

using namespace std;

#include <map>
#include "state.h"

class FSM {
public:
	string curState;
	map<string, State> states;

	FSM(map<string, State> _states);
	FSM();
	void addState(string stateTag, State state);
	void setCurState(string stateName);
	string evaluate(string activateState, string event);
};

#endif
