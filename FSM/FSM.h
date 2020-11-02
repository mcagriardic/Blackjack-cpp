#ifndef FSM_H
#define FSM_H

using namespace std;

#include <map>
#include <queue>
#include "state.h"

class FSM {
public:
	string activeState;
	queue<string> eventQueue;
	map<string, State> states;

	FSM(map<string, State>& _states);
	FSM();
	void addState(const string& stateName, const State& state);
	void setCurState(const string& stateName);
	void callbackOnEnter();
	void postEventToQueue(const string& event);
	void evaluate(const string& event);
	void processQueuedEvents();
};

#endif
