/*
 * event_list.hpp
 *
 *  Created on: 9 de mai de 2017
 *      Author: joker
 */

#ifndef SRC_EVENT_LIST_HPP_
#define SRC_EVENT_LIST_HPP_

#include "event.hpp"
#include "../data-structures/circular_list.h"

//!  Classe herdada da estrutura de dado: ListaEnc<T>.
/*!  Estrutura de dado do tipo Lista Encadeade com o método de
 *	 de comparação maior(T dado1, T dado2) alterado  para comparar
 *	 dados do tipo Evento, em função do seu tempo.
 * 	 \author Bruno Marques do Nascimento & Salomão Rodrigues Jacinto
 * 	 \since 10/05/2016
 * 	 \version 1.0
 */
class EventList : public CircularList<Event*> {
 public:
//!  Função maior, retorna se o tempo de um evento é maior que outro.
/*!
 *   \param evento1 argumento do tipo Evento*, que será comparado com evento2.
 *   \param evento2 argumento do tipo Evento*, que será comparado com evento1.
 *   \return um boolean que informa se o tempo do evento1 é maior que evento2.
 */
 	bool maior(Event* event1, Event* event2);
};

bool EventList::maior(Event* event1, Event* event2) {
	return event1->time() > event2->time();
}



#endif /* SRC_EVENT_LIST_HPP_ */
