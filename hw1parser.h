#ifndef HW1_PARSER_H
#define HW1_PARSER_H

#include <vector>

using std::vector;

struct Hw1Normal {
	double x;
	double y;
	double z;
	/**
	 * Default constructor - should not be used. Added for technical reasons (compiler issue).
	 */
	Hw1Normal() : x(0.0), y(0.0), z(0.0) {}
	Hw1Normal(double x, double y, double z) : x(x), y(y), z(z) {}
};

class Hw1Vertex {
	double x;
	double y;
	double z;
	Hw1Normal normal;
	bool hasNormal_;

	/**
	 * Private copy constructor.
	 */
	Hw1Vertex(const Hw1Vertex& v) {}
	Hw1Vertex& operator=(const Hw1Vertex& v) {}
public:
	Hw1Vertex(double x, double y, double z) : x(x), y(y), z(z),
		normal(18.18, 18.18, 18.18), hasNormal_(false) {}
	Hw1Vertex(double x, double y, double z, double normalX, double normalY, double normalZ) :
	    x(x), y(y), z(z), normal(normalX, normalY, normalZ), hasNormal_(true) {}
	// TODO: Destructor.
	double getX() {
		return x;
	}
	double getY() {
		return y;
	}
	double getZ() {
		return z;
	}
	bool hasNormal() {
		return hasNormal_;
	}
	/**
	 * Call this only when hasNormal() returns true.
	 */
	Hw1Normal getNormal() {
		return normal;
	}
};

class Hw1Polygon {
	vector<Hw1Vertex*>* vertices;
	Hw1Normal normal;

	// Center coordinates.
	double centerX;
	double centerY;
	double centerZ;
	void calculateCenter() {
		// TODO: Calculate center.
	}
	Hw1Normal calculateNormal() {
		// TODO: Calculate real normal.
		// TODO: delete this placeholder code:
		Hw1Normal normal(0.0, 0.0, 0.0);
		return normal;
	}
	// TODO: private copy constructor and operator=.
public:
	// TODO: Destructor.
	Hw1Polygon(vector<Hw1Vertex*>* vertices) : vertices(vertices) {
		normal = calculateNormal();
	}
	Hw1Polygon(vector<Hw1Vertex*>* vertices, double normalX, double normalY,
		double normalZ) : vertices(vertices), normal(normalX, normalY, normalZ) {}
	void draw();
};

class Hw1Object {
	double colorR;
	double colorG;
	double colorB;
	vector<Hw1Polygon*>* polygons;
	// TODO: Privates... same as above.
public:
	// TODO: Destructor.
	Hw1Object(vector<Hw1Polygon*>* polygons) : polygons(polygons),
	// Default color: white?
		colorR(1.0), colorG(1.0), colorB(1.0) {}
	Hw1Object(vector<Hw1Polygon*>* polygons, double colorR, double colorG, double colorB) :
		polygons(polygons), colorR(colorR), colorG(colorG), colorB(colorB) {}
	void draw();
};

#endif  // HW1_PARSER_H