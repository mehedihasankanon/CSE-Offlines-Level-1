#include <iostream>
#include <cstring>

using namespace std;

class Planet
{
    char *name;   // Pointer for the name of the planet
    int distance; // Distance from the sun in millions of kilometers

public:
    Planet()
    {
        name = new char[1];
        name[0] = '\0';
        distance = 0;
    }

    Planet(const char *planetName, int dist)
    {
        name = new char[strlen(planetName) + 1];
        strcpy(name, planetName);
        distance = dist;
    }

    Planet(const Planet &other)
    {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        distance = other.distance;
    }

    ~Planet()
    {
        delete[] name;
    }

    void display()
    {
        cout << "Planet: " << name << ", Distance: " << distance << " million km\n";
    }

    // Method to get the planet name
    const char *getName()
    {
        return name;
    }

    friend Planet operator+(int num, const Planet &pl);
    Planet operator+(int);
    Planet operator+(const Planet &);
    Planet &operator=( const Planet &);
    bool operator<(const Planet);
};

Planet operator+(int num, const Planet &pl)
{
    return ((Planet)pl + num);
}

Planet &Planet::operator=(const Planet &pl)
{
    if (this != &pl)
    {
        delete[] name;
        name = new char[strlen(pl.name) + 1];
        strcpy(name, pl.name);
        distance = pl.distance;
    }
    return *this;
}


Planet Planet::operator+(int x)
{
    return Planet(this->name, x + this->distance);
}

Planet Planet::operator+(const Planet &pl)
{
    return Planet("Combined", pl.distance + this->distance);
}

bool Planet::operator<(const Planet pl)
{
    return this->distance < pl.distance;
}

class SolarSystem
{
    Planet planets[10];
    int planetCount;

public:
    SolarSystem()
    {
        planetCount = 0;
    }

    // Add a planet to the solar system
    void addPlanet(const char *name, int distance)
    {
        if (planetCount < 10)
        {
            Planet p(name, distance);
            planets[planetCount] = p;
            planetCount++;
        }
        else
        {
            cout << "Solar system is full. Can't add more planets.\n";
        }
    }

    Planet &operator[](int);
    Planet &operator[](const char *);
};

Planet &SolarSystem::operator[](int idx)
{
    return planets[idx];
}

Planet &SolarSystem::operator[](const char *name)
{
    for (int i = 0; i < planetCount; i++)
    {
        if (strcmp(planets[i].getName(), name) == 0)
            return planets[i];
    }
    return planets[0];
}

int main()
{
    SolarSystem solarSystem;

    // Add planets to the solar system
    solarSystem.addPlanet("Invalid", -1);
    solarSystem.addPlanet("Sun", 0);
    solarSystem.addPlanet("Earth", 150);
    solarSystem.addPlanet("Mars", 228);

    // Display all planets in the solar system
    solarSystem[1].display();
    solarSystem[2].display();
    solarSystem[3].display();

    solarSystem[3] = (140 + solarSystem[3]);
    solarSystem[3].display();

    Planet p = solarSystem["Earth"] + solarSystem["Mars"];
    p.display();

    if (solarSystem[2] < solarSystem[3])
    {
        cout << "Earth is closer to the Sun than Mars\n";
    }
    else
    {
        cout << "Mars is closer to the Sun than Earth\n";
    }

    p = solarSystem[1];
    p.display();

    return 0;
}
