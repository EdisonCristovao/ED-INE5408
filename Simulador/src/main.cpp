
#include <iostream>
#include "system.hpp"

int main() {
	int time_simulation, time_semaphore_open;

	std::cout << "Tempo de simulação (Em segundos) : " << std::endl;
	std::cin >> time_simulation;

	std::cout << "Tempo em que o semaforo esta aerto (Em segundos) : " << std::endl;
	std::cin >> time_semaphore_open;

	System* s1 = new System(time_simulation, time_semaphore_open);
	s1->exe();
}
