// Copyright [2017] <Ramna Sidharta de Andrade Palma & Edison Cristovão Junior>

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <iostream>
#include "event_list.hpp"
#include "semaphore.hpp"
#include "../data-structures/circular_list.h"

class System {
private:

	int vehicle_passes_;
	int vehicle_created_;
	int vehicle_deleted_;
	int time_simulation_;
	int time_semaphore_;
	int actual_time_;

	CircularList<Runway*>* runway_;

	CircularList<Semaphore*>* semaphores_;

	EventList* events_;
public:
	System(int time_simulation, int time_semaphore);

	void init_component();

	void init_event_create_vehicle();

	void init_event_arrive_semaphore();

	void init_event_open_semaphore();

	void treat_event_chage_runway(Event* event_arrive_semaphore);

	Semaphore* semaphore_location(Runway* runway);

	void treat_event();

	void exe();

	void exit();

};

System::System(int time_simulation, int time_semaphore) {
	time_simulation_ = time_simulation;
	time_semaphore_ = time_semaphore;

	runway_ = new CircularList<Runway*>();
	semaphores_ = new CircularList<Semaphore*>();
	events_ = new EventList();
	actual_time_ = 0;
	vehicle_deleted_ = 0;
	vehicle_created_ = 0;

	init_component();
}

void System::init_component() {

	Runway* s1sul = new Runway(500, 60, -1, 0);
	Runway* s1norte = new Runway(500, 60, 30, 7);

	runway_->push_back(s1sul);
	runway_->push_back(s1norte);

	Runway* s2sul = new Runway(500, 40, -1, 0);
	Runway* s2norte = new Runway(500, 40, 60, 15);

	runway_->push_back(s2sul);
	runway_->push_back(s2norte);

	Runway* l1leste = new Runway(400, 30, -1, 0);
	Runway* l1oeste = new Runway(400, 30, 10, 2);

	runway_->push_back(l1leste);
	runway_->push_back(l1oeste);

	Runway* n2sul = new Runway(500, 40, 20, 5);
	Runway* n2norte = new Runway(500, 40, -1, 0);

	runway_->push_back(n2sul);
	runway_->push_back(n2norte);

	Runway* n1sul = new Runway(500, 60, 20, 5);
	Runway* n1norte = new Runway(500, 60, -1, 0);

	runway_->push_back(n1sul);
	runway_->push_back(n1norte);

	Runway* o1leste = new Runway(2000, 80, 10, 2);
	Runway* o1oeste = new Runway(2000, 80, -1, 0);

	runway_->push_back(o1leste);
	runway_->push_back(o1oeste);

	Runway* c1leste = new Runway(300, 60, 0, 0);
	Runway* c1oeste = new Runway(300, 60, 0, 0);

	runway_->push_back(c1leste);
	runway_->push_back(c1oeste);

	int probabilitys1[3] = { 40, 30, 30 };
	Runway* runwaysDeSaida1[3] = { l1leste, n2norte, s2sul };
	Semaphore* semaphoreC1leste = new Semaphore(true, runwaysDeSaida1, c1leste,
			probabilitys1, time_semaphore_);

	int probabilitys2[3] = { 80, 10, 10 };
	Runway* runwaysDeSaida2[3] = { c1leste, n1norte, s1sul };
	Semaphore* semaphoreO1leste = new Semaphore(true, runwaysDeSaida2, o1leste,
			probabilitys2, time_semaphore_);

	int probabilitys3[3] = { 40, 30, 30 };
	Runway* runwaysDeSaida3[3] = { l1leste, c1oeste, s2sul };
	Semaphore* semaphoreN2sul = new Semaphore(true, runwaysDeSaida3, n2sul,
			probabilitys3, time_semaphore_);

	int probabilitys4[3] = { 80, 10, 10 };
	Runway* runwaysDeSaida4[3] = { c1leste, o1oeste, s1sul };
	Semaphore* semaphoreN1sul = new Semaphore(true, runwaysDeSaida4, n1sul,
			probabilitys4, time_semaphore_);

	int probabilitys5[3] = { 40, 30, 30 };
	Runway* runwaysDeSaida5[3] = { l1leste, s2sul, c1oeste };
	Semaphore* semaphoreS2norte = new Semaphore(true, runwaysDeSaida5, s2norte,
			probabilitys5, time_semaphore_);

	int probabilitys6[3] = { 80, 10, 10 };
	Runway* runwaysDeSaida6[3] = { c1leste, n1norte, o1oeste };
	Semaphore* semaphoreS1norte = new Semaphore(true, runwaysDeSaida6, s1norte,
			probabilitys6, time_semaphore_);

	int probabilitys7[3] = { 40, 30, 30 };
	Runway* runwaysDeSaida7[3] = { n2norte, c1leste, s2sul };
	Semaphore* semaphoreL1oeste = new Semaphore(true, runwaysDeSaida7, l1oeste,
			probabilitys7, time_semaphore_);

	int probabilitys8[3] = { 40, 30, 30 };
	Runway* runwaysDeSaida8[3] = { o1oeste, n1norte, s1sul };
	Semaphore* semaphoreC1oeste = new Semaphore(true, runwaysDeSaida8, c1oeste,
			probabilitys8, time_semaphore_);

	semaphores_->push_back(semaphoreC1leste);
	semaphores_->push_back(semaphoreO1leste);

	semaphores_->push_back(semaphoreN2sul);
	semaphores_->push_back(semaphoreN1sul);

	semaphores_->push_back(semaphoreS2norte);
	semaphores_->push_back(semaphoreS1norte);

	semaphores_->push_back(semaphoreL1oeste);
	semaphores_->push_back(semaphoreC1oeste);

}

void System::init_event_create_vehicle() {
	Runway* runway;
	Event* newEvent;

	int time_inter_control;
	int time_next_event;

	for (int i = 0; i < runway_->size(); i++) {
		runway = runway_->at(i);

		if (runway->font()) {

			time_inter_control = actual_time_;

			while (time_inter_control < time_simulation_) {

				time_next_event = runway->next_vehicle(time_inter_control);
				if (time_next_event <= time_simulation_) {

					newEvent = new Event(time_next_event, 1, new Vehicle(),
							runway);
					events_->insert_sorted(newEvent);
					time_inter_control = time_next_event;

				} else {
					break;  // break do while
				}
			}
		}
	}

}

void System::init_event_arrive_semaphore() {

	Event* newEvent;
	Runway* runway;
	Semaphore* semaphore;

	int time_next_event;
	int time_created;

	for (int i = 0; i < events_->size(); i++) {

		Event* eventAux = events_->at(i);
		if (eventAux->category() == 1) {
			time_created = eventAux->time();
			runway = (Runway*) eventAux->attrib();
			semaphore = (Semaphore*) semaphore_location(runway);

			time_next_event = runway->time_arrived(time_created);

			if (time_next_event <= time_simulation_) {
				newEvent = new Event(time_next_event, 3, semaphore, 0);
				events_->insert_sorted(newEvent);
			}
		}
	}
}

Semaphore* System::semaphore_location(Runway* runway) {

	Semaphore* semaphore;
	for (int i = 0; i < semaphores_->size(); i++) {

		semaphore = semaphores_->at(i);

		if (semaphore->runway_control() == runway) {
			return semaphore;
		}
	}
	return 0;
}

void System::init_event_open_semaphore() {
	int time_inter_control, time_next_event;
	Semaphore* semaphoreAbrira1;
	Semaphore* semaphoreAbrira2;

	Event* novoEvent1;
	Event* novoEvent2;

	for (int i = 0; i < semaphores_->size(); i += 2) {

		time_inter_control = actual_time_ + (i / 2 * time_semaphore_);
		bool fechado = false;

		semaphoreAbrira1 = semaphores_->at(i);
		semaphoreAbrira2 = semaphores_->at(i + 1);

		semaphoreAbrira1->chage_state(time_inter_control); // abriu
		semaphoreAbrira2->chage_state(time_inter_control); // abriu

		while (time_inter_control < time_simulation_) {

			time_next_event = semaphoreAbrira1->set_next_event(
					time_inter_control, fechado);

			if (time_next_event <= time_simulation_) {

				novoEvent1 = new Event(time_next_event, 0, semaphoreAbrira1, 0);
				novoEvent2 = new Event(time_next_event, 0, semaphoreAbrira2, 0);

				events_->insert_sorted(novoEvent1);
				events_->insert_sorted(novoEvent2);
			}

			fechado = !fechado;
			time_inter_control = time_next_event;
		}
	}
}

void System::treat_event_chage_runway(Event* event_oc) {
	Event* event;
	Semaphore* semaforo = (Semaphore*) event_oc->classe();
	actual_time_ = event_oc->time();

	int time_next_event;
	try {
		Runway* runwayDestino = semaforo->chage_vehicle_runway();

		if (runwayDestino == semaforo->runway_control()) {

			if (actual_time_ + 1 < semaforo->next_open()) {
				time_next_event = actual_time_ + 1;
				event = new Event(time_next_event, 3, semaforo, 0);
			} else {
				time_next_event = semaforo->next_open() + 1;
				event = new Event(time_next_event, 3, semaforo, 0);
			}

		} else {

			if (runwayDestino->disappear()) {
				Vehicle* vehicle =
						((Runway*) semaforo->runway_control())->remove_Vehicle();

				runwayDestino->add_Vehicle(vehicle);

				time_next_event = runwayDestino->time_arrived(actual_time_);
				event = new Event(time_next_event, 2, runwayDestino, 0);

			} else {
				Vehicle* vehicle =
						((Runway*) semaforo->runway_control())->remove_Vehicle();

				runwayDestino->add_Vehicle(vehicle);

				time_next_event = runwayDestino->time_arrived(actual_time_);
				event = new Event(time_next_event, 3,
						semaphore_location(runwayDestino), 0);
			}
		}

	} catch (std::exception& e) {

		time_next_event = semaforo->next_open() + 1;
		event = new Event(time_next_event, 3, semaforo, 0);
	}
	if (time_next_event < time_simulation_ && time_next_event > actual_time_) {
		events_->insert_sorted(event);
	}
}

void System::treat_event() {

	Event* event;
	for (int i = 0; i < events_->size(); ++i) {

		event = events_->at(i);

		if (actual_time_ >= time_simulation_) {
			break;
		}
		switch (event->category()) {

		case 0: {  //Mudar Semáforo
			//std::cout << "Semaphore Troca Cor -> Tempo [" << event->tempo() << "]" << std::endl;
			Semaphore* semaforoDoEvent = (Semaphore*) event->classe();
			semaforoDoEvent->chage_state(actual_time_);
			actual_time_ = event->time();
			break;

		}
		case 1: {  //Criar Carro
			//std::cout << "Carro Criado -> Tempo [" << event->tempo() << "]" << std::endl;
			Runway* runwayEvent = (Runway*) event->attrib();
			Vehicle* vehicleEvent = (Vehicle*) event->classe();

			runwayEvent->add_Vehicle(vehicleEvent);

			actual_time_ = event->time();
			break;

		}
		case 2: {  //Deletar Carro
			//std::cout << "Carro Deletado -> Tempo [" << event->tempo() << "]" << std::endl;
			Runway* runwayEvent = (Runway*) event->classe();
			runwayEvent->remove_Vehicle();
			actual_time_ = event->time();
			break;

		}
		case 3: {  //Chegada no semaforo
			//std::cout << "Chegada no Smafaro -> Tempo [" << event->tempo() << "]" << std::endl;
			treat_event_chage_runway(event);

			break;
		}
		default: {
		}
		}
	}
}

void System::exit() {
	Runway* runway;
	int espacoCarros = 0;
	for (int i = 0; i < runway_->size(); ++i) {
		runway = runway_->at(i);

		if (runway->font() == true && runway->disappear() == false) {
			std::cout << "---- Runway [" << i << "] ---- " << std::endl;
			std::cout << "---- Fonte ---- " << std::endl;

			std::cout << "Tamanho :" << runway->distance() << std::endl;
			std::cout << "Carros criados :" << runway->vehicles_created()
					<< std::endl;
			std::cout << "Carros passando :" << runway->vehicles_passed()
					<< std::endl;
			std::cout << "Espaco usado :" << runway->distance_busy()
					<< std::endl;
			espacoCarros = 0;

			vehicle_deleted_ += runway->vehicles_deleted();
			vehicle_created_ += runway->vehicles_created();
			vehicle_passes_ += runway->vehicles_passed();

		} else if (runway->disappear() == true && runway->font() == false) {
			std::cout << "---- Runway [" << i << "] ---- " << std::endl;
			std::cout << "---- sumidouro ---- " << std::endl;

			std::cout << "Tamanho :" << runway->distance() << std::endl;
			std::cout << "Carros apagados :" << runway->vehicles_deleted()
					<< std::endl;
			std::cout << "Carros passando :" << runway->vehicles_passed()
					<< std::endl;
			std::cout << "Espaco usado :" << runway->distance_busy()
					<< std::endl;
			espacoCarros = 0;

			vehicle_deleted_ += runway->vehicles_deleted();
			vehicle_created_ += runway->vehicles_created();
			vehicle_passes_ += runway->vehicles_passed();


		} else {
			std::cout << "---- Runway [" << i << "] ---- " << std::endl;
			std::cout << "---- Rua central ---- " << std::endl;

			std::cout << "Tamanho :" << runway->distance() << std::endl;
			std::cout << "Carros passando :" << runway->vehicles_passed()
					<< std::endl;
			std::cout << "Espaco usado :" << runway->distance_busy()
					<< std::endl;
			espacoCarros = 0;

			vehicle_deleted_ += runway->vehicles_deleted();
			vehicle_created_ += runway->vehicles_created();
			vehicle_passes_ += runway->vehicles_passed();

		}
		std::cout << "----------------------------" << std::endl;
	}

	std::cout << "Carros apagados :" << vehicle_deleted_ << std::endl;
	std::cout << "Carros passando :" << vehicle_passes_ << std::endl;
	std::cout << "Carros criados :" << vehicle_created_ << std::endl;
}

void System::exe() {
	init_event_create_vehicle();

	int x = events_->size();
	std::cout << "Events criação carro: " << x << std::endl;

	init_event_arrive_semaphore();

	int y = events_->size();
	std::cout << "Events chegada no semáforo " << events_->size() - x
			<< std::endl;

	init_event_open_semaphore();

	std::cout << "Events abertura semáforo " << events_->size() - y
			<< std::endl;

	treat_event();

	exit();
}

#endif  // SYSTEM_HPP_

