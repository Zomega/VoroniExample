#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "vector.h"
#include <cmath>

class Rotation {
private:
	float angle;
public:
	Rotation() {
		this->angle = 0;
	}

	Rotation( float angle ) {
		this->angle = angle;
	}

	Rotation( const Rotation& rotation ) {
		this->angle = rotation.getAngle();
	}

	Rotation operator=( Rotation rhs ) {
		this->angle = rhs.getAngle();
	}

	Vector operator*( Vector vector ) {
		return Vector(
			cos( this->angle ) * vector.x - sin( this->angle ) * vector.y,
			cos( this->angle ) * vector.y + sin( this->angle ) * vector.x
		);
	}

	Rotation operator*( Rotation rhs ) {
		return Rotation( this->getAngle() + rhs.getAngle() );
	}

	float getAngle() const {
		return this->angle;
	}
};

class Transform {
private:
	Rotation rotation;
	Vector translation;
public:
	Transform() {
		this->rotation = Rotation();
		this->translation = Vector();
	}

	Transform( float rotation, Vector translation ) {
		this->rotation = rotation;
		this->translation = translation;
	}

	Transform( Rotation rotation, Vector translation ) {
		this->rotation = rotation;
		this->translation = translation;
	}

	Transform(const Transform& transform) {
		this->rotation = transform.rotation;
		this->translation = transform.translation;
	}
	Transform operator=( Transform rhs ) {
		this->rotation = rhs.getRotation();
		this->translation = rhs.getTranslation();
	}

	Vector operator*( Vector rhs ) {
		return rotation * rhs + this->translation;
	}

	Transform operator*( Transform rhs ) {
		Rotation rotation = this->getRotation() * rhs.getRotation();
		Vector translation = this->getTranslation() + this->getRotation() * rhs.getTranslation();
		return Transform( rotation, translation );
	}

	Rotation getRotation() {
		return this->rotation;
	}

	Vector getTranslation() {
		return this->translation;
	}
};

Rotation inverse( Rotation rotation ) {
	return Rotation( rotation.getAngle() );
};

Transform inverse( Transform transform ) {
	Rotation invRotation = inverse( transform.getRotation() );
	Vector invTranslation = invRotation * ( transform.getTranslation() * -1 );
	return Transform( invRotation, invTranslation );
};
	
#endif
