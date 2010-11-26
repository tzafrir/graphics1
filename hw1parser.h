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
	void normalize() {
		double size = sqrt(x*x + y*y + z*z);
		x /= size;
		y /= size;
		z /= size;
	}
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

public:
	// "Global" variable (Hw1Polygon::normalScale)
	static double normalScale;
	static double normalScaleDefault;
private:

	void calculateCenter() {
		double x = 0.0;
		double y = 0.0;
		double z = 0.0;
		int count = 0;
		for (vector<Hw1Vertex*>::iterator it = vertices->begin();
			 it != vertices->end();
			 ++it) {
			Hw1Vertex* v = *it;
			count++;
			x += v->getX();
			y += v->getY();
			z += v->getZ();
		}
		x /= (double)count;
		y /= (double)count;
		z /= (double)count;
		centerX = x;
		centerY = y;
		centerZ = z;
	}
	Hw1Normal calculateNormal() {
		double x = 0.0;
		double y = 0.0;
		double z = 0.0;
		if (vertices->size() > 1) {
			// Cross first two vertices:
			Hw1Vertex* v1 = vertices->at(0);
			Hw1Vertex* v2 = vertices->at(1);
			double x1 = v1->getX();
			double y1 = v1->getY();
			double z1 = v1->getZ();
			double x2 = v2->getX();
			double y2 = v2->getY();
			double z2 = v2->getZ();

			x = y1*z2 - z1*y2;
			y = z1*x2 - x1*z2;
			z = x1*y2 - y1*x2;
		}
		Hw1Normal normal(x, y, z);
		normal.normalize();
		return normal;
	}
	void initialize() {
		calculateCenter();
		normal.normalize();
	}
	Hw1Polygon(const Hw1Polygon& poly) {}
	Hw1Polygon& operator=(const Hw1Polygon& poly) {}
public:
	~Hw1Polygon() {
	  for (vector<Hw1Vertex*>::iterator it = vertices->begin();
	       it != vertices->end();
	       ++it) {
      delete(*it);
	  }
	  delete(vertices);
	}
	Hw1Polygon(vector<Hw1Vertex*>* vertices) : vertices(vertices) {
		normal = calculateNormal();
		initialize();
	}
	Hw1Polygon(vector<Hw1Vertex*>* vertices, double normalX, double normalY,
			double normalZ) : vertices(vertices), normal(normalX, normalY, normalZ) {
		initialize();
	}
	void draw();
	void drawNormals(bool showNormals, bool drawVertexNormals);
};

class Hw1Object {
	double colorR;
	double colorG;
	double colorB;
	vector<Hw1Polygon*>* polygons;
	Hw1Object(const Hw1Object& obj) {}
	Hw1Object& operator=(const Hw1Object& obj) {}
public:
	~Hw1Object() {
	  for (vector<Hw1Polygon*>::iterator it = polygons->begin();
	       it != polygons->end();
	       ++it) {
      delete(*it);
	  }
	  delete(polygons);
	}
	Hw1Object(vector<Hw1Polygon*>* polygons) : polygons(polygons),
	// Default color: white?
		colorR(1.0), colorG(1.0), colorB(1.0) {}
	Hw1Object(vector<Hw1Polygon*>* polygons, double colorR, double colorG, double colorB) :
		polygons(polygons), colorR(colorR), colorG(colorG), colorB(colorB) {}
	void draw();
	void drawNormals(bool showNormals, bool drawVertexNormals) {
		for (vector<Hw1Polygon*>::iterator it = polygons->begin();
			    it != polygons->end();
				++it) {
			(*it)->drawNormals(showNormals, drawVertexNormals);
		}
	}
};

#endif  // HW1_PARSER_H
