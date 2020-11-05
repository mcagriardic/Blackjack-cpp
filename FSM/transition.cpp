#include "transition.h"

Transition::Transition(
	const string& _event, 
	const string& _targetState, 
	function<bool()> _guard,
	function<void()> _transitionAction
)
	: event_(_event), targetState(_targetState), guard(_guard), transitionAction(_transitionAction)
{;}

string Transition::getEventName() {
	return event_;
}

bool Transition::operator() ()
{
	return guard();
}

