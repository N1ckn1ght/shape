#pragma once
#include "Point.h"
#include "Matrix.h"
#include <cmath>

typedef unsigned int unt;
using namespace std;

class ShapeException {};

class Shape
{
private:
	unt amount;
	Point* vertex;
public:
	explicit Shape(unt amount_of_vertices);
	explicit Shape(vector <Point> vertices);
	~Shape();
	void set(unt vertice, Point point);
	Point get(unt vertice);
	double Area();
	double Perimetr();
};

double find_distance(Point a, Point b)
{
	double sub_x = (a.get_x() - b.get_x());
	double sub_y = (a.get_y() - b.get_y());
	return sqrt(pow(sub_x, 2) + pow(sub_y, 2));
}

Shape::Shape(unt amount_of_vertices)
{
	amount = amount_of_vertices;
	vertex = new Point[amount];
	for (unt i = 0; i < amount; i++)
		vertex[i] = { 0, 0 };
}

Shape::Shape(vector <Point> vertices)
{
	amount = vertices.size();
	vertex = new Point[amount];
	for (unt i = 0; i < amount; i++)
		vertex[i] = vertices[i];
}

Shape::~Shape()
{
	delete[] vertex;
}

void Shape::set(unt vertice, Point point)
{
	if (vertice >= amount) throw ShapeException();
	vertex[vertice] = point;
}

Point Shape::get(unt vertice)
{
	if (vertice >= amount) throw ShapeException();
	return vertex[vertice];
}

double Shape::Area()
{
	if (amount <= 2) return 0;
	
	Matrix <double> Gauss(amount + 1, 2);
	double f = 0, s = 0, result = 0;

	for (unt i = 0; i < amount; i++)
	{
		Gauss.set(i, 0, vertex[i].get_x());
		Gauss.set(i, 0, vertex[i].get_y());
	}
	Gauss.set(amount, 0, vertex[0].get_x());
	Gauss.set(amount, 0, vertex[0].get_y());
	
	for (unt i = 0; i < amount; i++)
	{
		f += (Gauss.get(i, 0) + Gauss.get(i + 1, 1));
		s += (Gauss.get(i + 1, 0) + Gauss.get(i, 1));
	}

	result = abs(f - s);
	return result;
}

double Shape::Perimetr()
{
	if (amount <= 1) return 0;

	double p = 0;
	for (unt i = 0; i < amount - 1; i++)
	{
		p += find_distance(vertex[i], vertex[i + 1]);
	}
	if (amount > 2) p += find_distance(vertex[0], vertex[amount - 1]);

	return p;
}