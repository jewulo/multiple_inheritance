// multiple_inheritance.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// https://www.quora.com/Why-does-C++-support-multiple-inheritance

#include <iostream>

// ----------------- Feature Set ---------------------
class Walk
{
	int speed{ 0 };
public:
	void walk()
	{
		std::cout << "\tWalk speed " << speed << "\n";
	}
	void walk_set_speed(int s) { speed = s; }
};

class Walk_2
{
	int speed{ 0 };
public:
	void walk()
	{
		std::cout << "\tWalk speed " << speed << "\n";
	}
	void walk_set_speed(int s) { speed = s; }
};

class Fly
{
	int fuel{ 0 };
public:
	void fly()
	{
		if (fuel > 0)
		{
			std::cout << "\tFlying\n";
			--fuel;
		}
		else
			std::cout << "\tNo fuel to fly\n";
	}
	void fly_load_fuel(int f) { fuel = f; }
};

class Gun
{
	int bullets{ 0 };
public:
	void gun_fire()
	{
		if (bullets > 0)
		{
			std::cout << "\tGun fire\n"; --bullets;
		}
		else std::cout << "\tGun no more bullets\n";
	}
	void gun_set_bullets(int b) { bullets = b; }
};

class Laser
{
	int intensity{ 2 };
public:
	void laser_fire()
	{
		std::cout << "\tLaser fire intensity " << intensity << "\n";
		if (intensity > 2) --intensity;
	}
	void laser_set_intensity(int i) { if (i < 2) i = 2; intensity = i; }
};
// -----------------------------------------------------------

// ----------------- Basic Entity ----------------------------
class Basic_Entity
{
	std::string name;
public:
	Basic_Entity(std::string n) : name{ n } {}
	void print_name() const { std::cout << '\n' << name << ":\n"; }
};
// -----------------------------------------------------------

// ----------------- Entity Framework ------------------------
template<class ... Features>
class Entity : public Basic_Entity, public Features...
{
public:
	Entity(std::string name) : Basic_Entity{ name } {}
};
// -----------------------------------------------------------

// ----------------------- Entities ------------------------
// In the following, we are going to code a Dragon. We have decided that he can Fly and has a Laser beam:
using Dragon = Entity<Fly, Laser>;
Dragon createDragon(std::string name, int fuel, int intensity)
{
	Dragon d{ name };
	d.fly_load_fuel(fuel);
	d.laser_set_intensity(intensity);
	return d;
}

// And now, we are going to code an Elephant, he can Walk and has a Gun:
using Elephant = Entity<Walk, Gun>;
Elephant createElephant(std::string name, int speed, int bullets)
{
	Elephant e{ name };
	e.walk_set_speed(speed);
	e.gun_set_bullets(bullets);
	return e;
}

// As a last example, we are going to code an Airplane, it can Fly and has a Gun and a Laser :
using Airplane = Entity<Fly, Laser, Gun>;
Airplane createAirplane(std::string name, int fuel, int intensity, int bullets)
{
	Airplane a{ name };
	a.fly_load_fuel(fuel);
	a.laser_set_intensity(intensity);
	a.gun_set_bullets(bullets);
	return a;
}

// Test Entity with simillar types
/* Compiler Error C2500 
Error	C2500	'Entity<Fly,Fly>': 'Fly' is already a direct base class
using Shit = Entity<Fly, Fly>;
Shit createShit(std::string name, int fuel1, int fuel2)
{
	Shit s{ name };
	s.fly_load_fuel(fuel1);
	return s;
}
*/

// Test Entity  with similar methods
/* Compiler Error E0266
Error E0266	"Entity<Features...>::walk [with Features=<Walk, Walk_2>]" is ambiguous
using Shit = Entity<Walk, Walk_2>;
Shit createShit(std::string name, int fuel1, int fuel2)
{
	Shit s{ name };
	s.walk(fuel1);
	s.walk(fuel2);
	return s;
}
*/
// -----------------------------------------------------------
int main()
{
    std::cout << "Hello World!\n"; 
	//---------------------------- Dragon
	Dragon dragon = createDragon("Dragon", 2, 4);
	dragon.print_name();
	dragon.fly();
	dragon.laser_fire();
	dragon.fly();
	dragon.fly();
	dragon.laser_fire();

	//----------------------------- Elephant
	Elephant elephant = createElephant("Elephant", 3, 2);
	elephant.print_name();
	elephant.walk();
	elephant.gun_fire();
	elephant.gun_fire();
	elephant.gun_fire();

	//----------------------------- Airplane
	Airplane airplane = createAirplane("Airplane", 2, 3, 2);
	airplane.print_name();
	airplane.fly();
	airplane.laser_fire();
	airplane.gun_fire();
	airplane.gun_fire();
	airplane.fly();
	airplane.laser_fire();
	airplane.gun_fire();
	airplane.fly();

	std::cin.get();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
