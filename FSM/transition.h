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
	function<void()> transitionAction;

	Transition(
		const string& _event,
		const string& _targetState,
		function<bool()> _guard,
		function<void()> _transitionAction=nullptr
	);
	string getEventName();
	bool operator() ();
};

#endif

