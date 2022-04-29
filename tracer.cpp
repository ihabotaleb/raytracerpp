#include <cstdint> 
#include <iostream>
#include <cmath>
#include <fstream> 
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

uint16_t im_size = 512;

struct BMPFileHeader {
    char bitmapSignatureBytes[2];
    uint32_t sizeOfBitmapFile;
    uint32_t reservedBytes;
    uint32_t pixelDataOffset;
};

BMPFileHeader bmpfileheader = {{'B', 'M'}, 54 + im_size * im_size, 0, 54};

struct BMPInfoHeader {
    uint32_t sizeOfThisHeader;
    int32_t width;
    int32_t height;
    uint16_t numberOfColorPlanes;
    uint16_t colorDepth;
    uint32_t compressionMethod;
    uint32_t rawBitmapDataSize;
    int32_t horizontalResolution;
    int32_t verticalResolution;
    uint32_t colorTableEntries;
    uint32_t importantColors;
};

BMPInfoHeader bmpinfoheader = {40,im_size,im_size,1,24,0,0,3780,3780,0,0};

struct Pixel {
	uint8_t b;
	uint8_t g;
	uint8_t r;
};

Pixel p = {100,100,255};

void makeBMP() {
	ofstream fout("output.bmp", ios::binary);
	fout.write((char *) &bmpfileheader, 14);
	fout.write((char *) &bmpinfoheader, 40);
	size_t pc = im_size * im_size;
	for (int i = 0; i < pc; i++) {
        fout.write((char *) &p, 3);
   	}
	fout.close();
}

int main() {
	int img[im_size][im_size][3];
	for (int i = 0; i < im_size; i++) {
		for (int j = 0; j < im_size; j++) {
		img[i][j][2] = 200;
		img[i][j][1] = 0;
		img[i][j][0] = 0;
		}
	}
	makeBMP();
}
