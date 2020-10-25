#pragma once

class Transition {
public:
	string event_;
	string targetState;
	function<bool()> guard;

	Transition(string _event, string _targetState, function<bool()> _guard)
		: event_(_event), targetState(_targetState), guard(_guard)
	{
		;
	}

	string getEventName() {
		return event_;
	}

	bool operator() ()
	{
		return guard();
	}
};

