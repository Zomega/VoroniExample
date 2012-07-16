/* Compile with:
g++ -lGL -lGLU -lglut graphics.cpp -o graphics.o
*/

#include <iostream>
#include <ctime>

#include "graphicsengine.h"

double unifRand() {
	return 2.0 * rand() / double(RAND_MAX) - 1.0;
}

void choose2( int size, int &first, int &second ) {
	first = rand () % size;
	second = rand () % (size - 1);
	if (second >= first) {
		second++;
	}
}

int main(int argc, char ** argv)
{
	glutInit( &argc, argv );
	GraphicsEngine::initiate();
	srand(time(0));

	std::vector< Vector* >* nodes = new std::vector< Vector* >();
	for(
		int i = 0;
		i < 100;
		i++
	) {
		nodes->push_back( new Vector( 4 * unifRand(), 4 * unifRand() ) );
	}

	Graph< Vector, void >* g = new Graph< Vector, void >();

	std::vector< Vector* >::iterator vectItr;
	for (
		vectItr = nodes->begin();
		vectItr < nodes->end();
		vectItr++
	) {
		g->addNode( *vectItr );
	}

	for (
		int j = 0;
		j < 1000;
		j++
	) {
		int A, B;
		choose2( 100, A, B );
		g->link( *(nodes->begin() + A ), *(nodes->begin() + B ) );
	}

	/*
	GraphicsEngine::add( regularPolygon( Vector(), 3, 1000 ), WHITE );
	GraphicsEngine::add( regularPolygon( Vector(), 3, 8 ), PURPLE );
	GraphicsEngine::add( regularPolygon( Vector(), 3, 7 ), BLUE );
	GraphicsEngine::add( regularPolygon( Vector(), 3, 6 ), CYAN );
	GraphicsEngine::add( regularPolygon( Vector(), 3, 5 ), GREEN );
	GraphicsEngine::add( regularPolygon( Vector(), 3, 4 ), YELLOW );
	GraphicsEngine::add( regularPolygon( Vector(), 3, 3 ), RED );
	*/

	//GraphicsEngine::add( g, PURPLE );

	Line* lineA = new Line( new Vector(), new Vector( 1, 1 ) );
	Line* lineB = new Line( new Vector(), new Vector( 100, -100 ) );
	Line* lineC = new Line( new Vector(2,1) );

	GraphicsEngine::add( lineA, YELLOW );
	GraphicsEngine::add( lineB, RED );
	GraphicsEngine::add( lineC, BLUE );

	GraphicsEngine::add( new Vector( intersect( *lineA, *lineB ) ), ORANGE );
	GraphicsEngine::add( new Vector( intersect( *lineA, *lineC ) ), GREEN );
	GraphicsEngine::add( new Vector( intersect( *lineB, *lineC ) ), PURPLE );
	GraphicsEngine::add( new Vector( intersect( *lineC, *lineA ) ), GREEN );
	GraphicsEngine::add( new Vector( intersect( *lineC, *lineB ) ), PURPLE );
	GraphicsEngine::run();

	delete g;
	return 0;
}
