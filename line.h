#ifndef LINE_H
#define LINE_H
#include "vector.h"
#include "transform.h"

class Line {
friend Vector intersect( Line, Line );
private:
	Transform transform;
public:
	/*
	Simple constructor, mostly for debugging purposes.
	*/
	Line( Transform transform ) {
		this->transform = transform;
	}

	/*
	Constructor which makes the line such that the given vector is the closest point on the line to the origin. This uniquely defines the line.
	*/
	Line( Vector* closestPoint ) {
		float angle = atan2( closestPoint->y, closestPoint->x );
		Vector offset = *closestPoint;
		this->transform = Transform( angle, offset );
	}

	Line( Vector* start, Vector* end ) {
		this->transform = Transform( ( (*start) - (*end) ).getTheta() - 3.14159/2, *start );
	}

	Line( const Line& line ) {
		this->transform = line.getTransform();
	}

	~Line() {
	}

	Transform getTransform() const {
		return this->transform;
	}

	/*
	Evaluates the line for a given parameter.
	*/
	Vector evaluate( float parameter ) {
		return this->transform * Vector( 0, parameter );
	}
};

Vector intersect( Line line1, Line line2 ) {
	Transform deltaTransform = inverse( line2.getTransform() ) * line1.getTransform();
	float thetaDel = deltaTransform.getRotation().getAngle();
	Vector transDel = deltaTransform.getTranslation();
	return line2.evaluate( transDel.y + transDel.x / tan( thetaDel ) );
};
#endif
