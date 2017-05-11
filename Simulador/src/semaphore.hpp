// Copyright [2017] <Ramna Sidharta de Andrade Palma & Edison Cristovão Junior>

#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

#include <cstdint>
#include "runway.hpp"
#include "../data-structures/array_list.h"

//!
/*
 *
 */
class Semaphore {

private:
	ArrayList<Runway*>* runway_out_; // pistas de saidas

	Runway* runway_control_;  // pista que o semaforo manda

	int time_open_;  // tempo que o semaforo fica aberto

	int* probability_;  // probabilidade para as pistas de destino

	int next_open_; // proxima vez que o semaforo vai abrir

	bool close_;  //  boolean que diz se esta fechado

public:
	Semaphore(bool close_, Runway* runway_out[], Runway* runway_control,
			int* probability, int time_open);

	Runway* chage_vehicle_runway();

	void chage_state(int actual_time);

	int set_next_event(int actual_time, bool close);

	int time_open();

	Runway* runway_control();

	int next_open();

};

Semaphore::Semaphore(bool close, Runway* runway_out[], Runway* runway_control,
		int* probability, int time_open) {
	close_ = close;
	runway_out_ = new ArrayList<Runway*>(3);

	for (int i = 0; i < 3; i++) {
		runway_out_->push_back(runway_out[i]);
	}
	runway_control_ = runway_control;
	probability_ = probability;
	time_open_ = time_open;
	next_open_ = 0;
}

Runway* Semaphore::chage_vehicle_runway() {
	if (close_) {
		throw std::runtime_error("Este semaforo esta fechado");
	}

	Vehicle* vehicle = runway_control_->front();
	int runway_destiny = vehicle->route();
	Runway* destiny;

	if (runway_destiny <= probability_[0]) {
		destiny = runway_out_->at(0);
		if (destiny->runway_full(vehicle)==false) {
			return destiny;
		} else {
			destiny = runway_control_;
			return destiny;
		}
	} else {
		int random = (rand() % 2) + 1;
		destiny = runway_out_->at(random);
		if (destiny->runway_full(vehicle)==false) {
			return destiny;
		} else {
			destiny = runway_control_;
			return destiny;
		}
	}
}

void Semaphore::chage_state(int actual_time) {
	if (!close_) {
		next_open_ = actual_time + time_open_ * 3;
	}
	if (close_) {
		next_open_ = actual_time;
	}
	close_ = !close_;
}

int Semaphore::set_next_event(int actual_time, bool close) {
	if (!close) {
		return actual_time + time_open_ * 3;
	}
	return actual_time + time_open_;
}

int Semaphore::time_open() {
	return time_open_;
}

Runway* Semaphore::runway_control() {
	return runway_control_;
}

int Semaphore::next_open() {
	return next_open_;
}

#endif  // SEMAPHORE_HPP

