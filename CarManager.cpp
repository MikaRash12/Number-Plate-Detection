#include "DatabaseConnection.h"
#include "CarManager.h"

void transform(sql::ResultSet* rs, Car* car)
{
	car->carID = rs->getInt("CarID");
	car->plateNo = rs->getString("PlateNo");
	car->model = rs->getString("Model");
	car->capacity = rs->getInt("Capacity");
	car->price = rs->getDouble("Price");
	car->transmission = rs->getInt("Transmission");
}

int CarManager::addCar(Car* car)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO Car (PlateNo, Model, Capacity, Price, Transmission) VALUES (?, ?, ?, ?, ?)");

	ps->setString(1, car->plateNo);
	ps->setString(2, car->model);
	ps->setInt(3, car->capacity);
	ps->setDouble(4, car->price);
	ps->setInt(5, car->transmission);

	int numRowsAffected = ps->executeUpdate();

	ps->close();

	delete ps;

	return numRowsAffected;
}

int CarManager::updateCar(Car* car)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("UPDATE Car SET PlateNo = ?, Model = ?, Capacity = ?, Price = ?, Transmission = ? WHERE CarID = ?");

	ps->setString(1, car->plateNo);
	ps->setString(2, car->model);
	ps->setInt(3, car->capacity);
	ps->setDouble(4, car->price);
	ps->setInt(5, car->transmission);
	ps->setInt(6, car->carID);

	int numRowsAffected = ps->executeUpdate();

	ps->close();

	delete ps;

	return numRowsAffected;
}

int CarManager::deleteCar(Car* car)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM Car WHERE CarID = ?");

	ps->setInt(1, car->carID);

	int numRowsAffected = ps->executeUpdate();

	ps->close();

	delete ps;

	return numRowsAffected;
}

Car* CarManager::getCar(int carID)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Car WHERE CarID = ?");

	ps->setInt(1, carID);

	sql::ResultSet* rs = ps->executeQuery();
	Car* car = NULL;

	if (rs->next())
	{
		car = new Car();
		transform(rs, car);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return car;
}

Car* CarManager::getCar(std::string plateNo)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Car WHERE PlateNo = ?");

	ps->setString(1, plateNo);

	sql::ResultSet* rs = ps->executeQuery();
	Car* car = NULL;

	if (rs->next())
	{
		car = new Car();
		transform(rs, car);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return car;
}

Car* CarManager::getCars()
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Car");
	sql::ResultSet* rs = ps->executeQuery();
	Car* car = NULL;
	Car* head = NULL;

	while (rs->next())
	{
		if (car == NULL)
		{
			car = new Car();
			head = car;
		}
		else
		{
			car->next = new Car();
			car = car->next;
		}
		
		transform(rs, car);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Car* CarManager::getCars(int minCapacity)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Car WHERE Capacity >= ?");

	ps->setInt(1, minCapacity);

	sql::ResultSet* rs = ps->executeQuery();
	Car* car = NULL;
	Car* head = NULL;

	while (rs->next())
	{
		if (car == NULL)
		{
			car = new Car();
			head = car;
		}
		else
		{
			car->next = new Car();
			car = car->next;
		}

		transform(rs, car);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Car* CarManager::getCars(double maxPrice)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Car WHERE Price <= ?");

	ps->setDouble(1, maxPrice);

	sql::ResultSet* rs = ps->executeQuery();
	Car* car = NULL;
	Car* head = NULL;

	while (rs->next())
	{
		if (car == NULL)
		{
			car = new Car();
			head = car;
		}
		else
		{
			car->next = new Car();
			car = car->next;
		}

		transform(rs, car);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}