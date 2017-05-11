#ifndef RUNWAY_HPP
#define RUNWAY_HPP

#include "vehicle.hpp"
#include "../data-structures/linked_queue.h"
#include <cstdio>


class Runway: public LinkedQueue<Vehicle*> {
private:
	int distance_;  //!< the length of runway

	int velocity_;  //!< velocity of vehicles in runway

	int distance_busy_;

	int frequency_;

	int frequency_vari_ ;

	int vehicle_passes_ ;

	int vehicle_created_;

	int vehicle_deleted_;

	int time_arrived_;

	bool disappear_;

	bool appear_;

public:
	Runway(int distance, int velocity, int frequency, int frequency_vari);

	void distance(int distance);

	int distance();

	void velocity(const int velocity);

	int velocity() const;

	int next_vehicle(int actual_time);

	void add_Vehicle(Vehicle* v);

	Vehicle* remove_Vehicle();

	int time_arrived(int actual_time);

	bool runway_full(Vehicle* v);

	bool font();

	bool disappear();

	int vehicles_created();

	int vehicles_passed();

	int vehicles_deleted();

	int distance_busy();

};

Runway::Runway(int distance, int velocity, int frequency, int frequency_vari) {
	LinkedQueue<Vehicle*>();

	velocity_ = velocity;
	distance_ = distance;

	time_arrived_ = (int) distance / (velocity / 3.6);
	frequency_vari_ = frequency_vari;
	frequency_ = frequency;

	distance_busy_ = 0;
	vehicle_passes_ = 0;
	vehicle_created_ = 0;
	vehicle_deleted_ = 0;

	if (frequency > 0) { //fonte
		appear_ = true;
		disappear_ = false;

	} else if (frequency == 0) { //central
		disappear_ = false;
		appear_ = false;

	} else {	//sumidouro
		disappear_ = true;
		appear_ = false;
	}
}

int Runway::next_vehicle(int actual_time) {
	return (actual_time + (frequency_ - frequency_vari_)
			+ (rand() % (frequency_vari_ * 2)) + 1);
	// verificar conta
}

void Runway::add_Vehicle(Vehicle* v) {
	if ((distance_busy_ + v->size()) <= distance_) {
		enqueue(v);
		distance_busy_ += v->size();
		if (font()) {
			vehicle_created_++;
		}
		if (!font() && !disappear()) {
			vehicle_passes_++;
		}
	}
}

Vehicle* Runway::remove_Vehicle() {
	Vehicle* v = dequeue();
	distance_busy_ -= v->size();
	if(disappear()) {
		vehicle_deleted_++;
	}
	return v;
}

int Runway::time_arrived(int actual_time) {
	return time_arrived_ + actual_time;
}

bool Runway::runway_full(Vehicle* v) {
	return distance_busy_ + v->size() > distance_;
}

bool Runway::font() {
	return appear_;
}

bool Runway::disappear() {
	return disappear_;
}

int Runway::vehicles_created() {
	return vehicle_created_;
}

int Runway::vehicles_passed() {
	return vehicle_passes_;
}

int Runway::vehicles_deleted() {
	return vehicle_deleted_;
}

int Runway::distance_busy() {
	return distance_busy_;
}

int Runway::distance() {
	return distance_;
}

#endif  // RUNWAY_HPP
