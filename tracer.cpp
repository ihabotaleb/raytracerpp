#include <cstdint> 
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

class Vector {
	public:
	double x;
	double y;
	double z;
	Vector(double a = 0, double b = 0, double c = 0) {
		x = a;
		y = b;
		z = c;
	}
};

// Print overide for Vector class
std::ostream& operator<< (std::ostream &out, Vector const& data) {
    out << "\n" << data.x << ':';
    out << data.y << ':';
    out << data.z; 
    return out;
}


Vector operator+(Vector a, Vector b) {
	return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector operator-(Vector a, Vector b) {
	return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
}


Vector operator*(Vector v, double f) {
	return Vector(v.x * f, v.y * f, v.z * f);
}

Vector operator*(Vector v, Vector w) {
	return Vector(v.x * w.x, v.y * w.y, v.z * w.z);
}

double norm(Vector v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector normalize(Vector v) {
	double n = norm(v);
	return Vector(v.x / n, v.y / n, v.z / n);
}

class Ray {
	public: 
		Vector start;
		Vector dir;
		Ray(Vector s, Vector d) {
			start = s;
			dir = d;
		};
		Ray() {
			start = Vector();
			dir = Vector();
		};
};

class Hit {
	public:
		Vector intersect;
		Ray ray;
		Hit(Vector i, Ray r) {
			intersect = i;
			ray = r;
		}
};

class Primitive {
	public:
		virtual Hit intersect(Ray r) = 0;
		virtual Vector shade(Hit h) = 0;
};

uint16_t im_size = 256;

struct Pixel {
	uint8_t b;
	uint8_t g;
	uint8_t r;
};

Pixel p = {100,100,255};

int main() {
	uint8_t im[im_size][im_size];
	for (int i = 0; i < im_size; i++) {
		for (int j = 0; j < im_size; j++) {
			im[i][j] = i * j;
		}
	}

	ofstream myfile;
	myfile.open("o.ppm");
	myfile << "P3 " << im_size << " " << im_size << " 255";
	for (int i = 0; i < im_size; i++) {
		myfile << "\n";
		for (int j = 0; j < im_size; j++) {
			myfile << unsigned(im[i][j]) << " "; 
			myfile << unsigned(im[i][j]) << " "; 
			myfile << unsigned(im[i][j]) << " "; 
		}
	}
	myfile.close();
	return 0;
}
