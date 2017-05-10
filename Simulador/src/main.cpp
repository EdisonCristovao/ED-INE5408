//============================================================================
// Name        : Simulador.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "system.hpp"

int main() {
	int tempoSemaforoFicaraAberto, tempoDeSimulacao;

	std::cout << "Informe o tempo da simulação (s) : " << std::endl;
	std::cin >> tempoDeSimulacao;

	std::cout << "Informe o tempo que os semáforos ficam abertos (s) : " << std::endl;
	std::cin >> tempoSemaforoFicaraAberto;

	System* s1 = new System(tempoDeSimulacao, tempoSemaforoFicaraAberto);
	s1->exe();
}
