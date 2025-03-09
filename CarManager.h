#include "Car.h"

#ifndef CARMANAGER_H
#define CARMANAGER_H

class CarManager
{
public:
	int addCar(Car* car);
	int updateCar(Car* car);
	int deleteCar(Car* car);
	Car* getCar(int carID);
	Car* getCar(std::string plateNo);
	Car* getCars();
	Car* getCars(int minCapacity);
	Car* getCars(double maxPrice);
};

#endif