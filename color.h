#ifndef COLOR_H
#define COLOR_H

struct Color {
	double r, g, b;
	Color() {
		this->r = 0;
		this->g = 0;
		this->b = 0;
	}
	Color( double r, double g, double b ) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
};

const Color RED		= Color( 1, 0, 0 );
const Color ORANGE	= Color( 1, 0.5, 0 );
const Color YELLOW	= Color( 1, 1, 0 );
const Color GREEN	= Color( 0, 1, 0 );
const Color CYAN	= Color( 0, 1, 1 );
const Color BLUE	= Color( 0, 0, 1 );
const Color PURPLE	= Color( 1, 0, 1 );

// Grey tones.
const Color WHITE	= Color( 1, 1, 1 );
const Color GREY	= Color( 0.5, 0.5, 0.5 );
const Color BLACK	= Color( 0, 0, 0 );

#endif
