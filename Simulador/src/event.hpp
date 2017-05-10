/*
 * event.hpp
 *
 *  Created on: 9 de mai de 2017
 *      Author: joker
 */

#ifndef SRC_EVENT_HPP_
#define SRC_EVENT_HPP_

#include "../data-structures/circular_list.h"

class Event {
 private:
 	int time_;
 	int category_;
 	void* classe_;
 	void* attrib_;

 public:
 	Event(int time, int category, void* classe, void* attrib);
	int time();
	int category();
	void* classe();
	void* attrib();
};

Event::Event(int time, int category, void* classe, void* attrib) {
    time_ = time;
    category_ = category;
    classe_ = classe;
    attrib_ = attrib;
}

int Event::time() {
  return time_;
}

int Event::category() {
  return category_;
}

void* Event::classe() {
  return classe_;
}

void* Event::attrib() {
  return attrib_;
}





#endif /* SRC_EVENT_HPP_ */
