#ifndef TRANSITION_H
#define TRANSITION_H

#include <string>
#include <functional>

using namespace std;

class Transition {
public:
	string event_;
	string targetState;
	function<bool()> guard;

	Transition(string _event, string _targetState, function<bool()> _guard);
	string getEventName();
	bool operator() ();
};

#endif

