#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include "line.h"

class LineSegment {
private:
	Line* line;
	double start, end;
public:
	LineSegment( Vector* start, Vector* end ) {
		this->line = new Line( start, end );
		this->start = 0;
		this->end = -1 * length( ( *start ) - ( *end ) );
	}

	LineSegment( Line* line, double start, double end ) {
		this->line = line;
		this->start = start;
		this->end = end;
	}

	Vector getStart() {
		return this->line->evaluate( this->start );
	}
	Vector getEnd() {
		return this->line->evaluate( this->end );
	}	
};

#endif
