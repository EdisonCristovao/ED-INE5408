// Copyright [2017] <Ramna Sidharta de Andrade Palma & Edison Cristovão Junior>

#ifndef VEHICLE
#define VEHICLE


class Vehicle {
 private:
 	int size_;  //tamanho do carro
	int route_;  //destino do carro

 public:
 	Vehicle();

	void generate_size();

  	void generate_route();

  	int size();

  	int route();
};

Vehicle::Vehicle() {
	generate_size();
	generate_route();
}

void Vehicle::generate_size() {
	size_ = (int) (rand() % 4) + 2 + 3;
}

void Vehicle::generate_route() {
	route_ = (rand() % 100) + 1;
}

int Vehicle::size() {
	return size_;
}

int Vehicle::route() {
	return route_;
}

#endif  // VEHICLE_HPP

