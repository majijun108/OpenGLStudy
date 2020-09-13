#pragma once

class PlanetStrip
{
public:
	PlanetStrip();
	~PlanetStrip();
	void Render();
private:
	Model* planet;
	Model* rock;
	Shader* shader;
};

PlanetStrip::PlanetStrip()
{
	planet = &Model("../Models/Planet/planet.obj");
	rock = &Model("../Models/Rock/rock.obj");
	shader = &Shader("planet.vs", "planet.fs");
}

inline void PlanetStrip::Render()
{

}

PlanetStrip::~PlanetStrip()
{
}
