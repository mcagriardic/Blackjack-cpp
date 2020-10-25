#include "transition.h"

Transition::Transition(string _event, string _targetState, function<bool()> _guard)
	: event_(_event), targetState(_targetState), guard(_guard)
{
	;
}

string Transition::getEventName() {
	return event_;
}

bool Transition::operator() ()
{
	return guard();
}