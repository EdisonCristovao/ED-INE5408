#ifndef SRC_EVENT_LIST_HPP_
#define SRC_EVENT_LIST_HPP_

#include "event.hpp"
#include "../data-structures/circular_list.h"

class EventList : public CircularList<Event*> {
 public:
	bool maior(Event* event1, Event* event2);
	bool menor(Event* event1, Event* event2);
};

bool EventList::maior(Event* event1, Event* event2) {
	return event1->time() > event2->time();
}

bool EventList::menor(Event* event1, Event* event2) {
	return event1->time() < event2->time();
}


#endif /* SRC_EVENT_LIST_HPP_ */
