#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

//TODO: Make Vector general dimension?
// Represents a member of R^2.
// Not to be confused with the STL vector class,
// which is an expandable array.
class Vector {
friend std::ostream& operator<<(std::ostream& output, const Vector& vector);
public:
	float x, y;

	Vector() {
		this->x = 0;
		this->y = 0;
	}

	Vector( float x, float y ) {
		this->x = x;
		this->y = y;
	}

	Vector( const Vector& vector ) {
		this->x = vector.x;
		this->y = vector.y;
	} 

	~Vector() {
	}

	Vector operator+(const Vector& rhs) 
	{
		Vector result;
		result.x = this->x + rhs.x;
		result.y = this->y + rhs.y;
		return result;
	}

	Vector operator-(const Vector& rhs) 
	{
		Vector result;
		result.x = this->x - rhs.x;
		result.y = this->y - rhs.y;
		return result;
	}

	Vector operator*(const float& rhs) 
	{
		Vector result;
		result.x = this->x * rhs;
		result.y = this->y * rhs;
		return result;
	}

	double getTheta() {
		return atan2( this->y, this->x );
	}
};

std::ostream& operator<<(std::ostream& output, const Vector& vector) {
    output << "<" <<  vector.x << ", " << vector.y <<">";
    return output;
}

double length( Vector v ) {
	return sqrt( v.x * v.x + v.y * v.y );
}

#endif
		
		
