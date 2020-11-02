#include "FSM.h"
#include <iostream>

FSM::FSM( map<string, State>& _states)
	: states(_states)
{;}

FSM::FSM() = default;

void FSM::addState(const string& stateName, const State& state)
{
	states[stateName] = state;
}

void FSM::setCurState(const string& stateName)
{
	activeState = stateName;
}

void FSM::callbackOnEnter() {
	states[activeState].onEnterCallback();
}

void FSM::postEventToQueue(const string& event) {
	eventQueue.push(event);
}

void FSM::evaluate(const string& event)
{
	for (Transition& transition : states[activeState].transitions) {
		if (
			transition.event_.compare(event) == 0
			&&
			(
				!transition.guard
				||
				transition.guard()
				)
			)
		{
			setCurState(transition.targetState);
			callbackOnEnter();
			// evaluate needs to append to queue
		}
	}
}

void FSM::processQueuedEvents() {
	while (!eventQueue.empty()) {
		evaluate(eventQueue.front());
		eventQueue.pop();
	}
}


//postEvent
//processedQueuedEvents - will call evaluate until the queue is empty
//dev purposes - log transitions and print them (logging should be done inside evaluate). This is a standard technique.

// state machine should only have the event
// this method should trigger the callback

// 3 callbacks:
// 1-on exit - destructor (e.g. close the screen)
// 2-on transition
// 3-on enter - constructor (you can display a screen)
