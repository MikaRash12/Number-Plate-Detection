#ifndef CAR_H
#define CAR_H

class Car
{
public:
	int carID;
	std::string plateNo, model;
	int capacity;
	double price;
	int transmission;
	Car* next;
};

#endif