#include <iostream>
using namespace std;

#include "graph.h"
#include "vector.h"
#include "transform.h"
#include "line.h"

void print( Vector v ) {
	cout<< v.x << " " << v.y << "\n";
}

int main () {
	/*GRAPH TESTING
	Graph< int, void >* g = new Graph< int, void >();
	int* a = new int(3);
	int* b = new int(4);
	int* c = new int(5);
	int* d = new int(6);
	g->addNode( a );
	g->addNode( b );
	g->addNode( c );
	g->addNode( d );
	g->addNode( a );
	g->link( a, b, NULL );
	g->link( a, c );
	g->unlink( a, b );
	g->getNeighbors( a );
	g->getNeighbors( b );
	g->print();
	*/

	/*VECTOR TESTING
	Vector* v = new Vector();
	Vector* u = new Vector( 4, 5 );
	Vector* w = new Vector( 1, 2 );

	Vector z;
	z = (*u) + (*w);
	print(z);
	z = (*w) * 2;
	print(z);
	*/

	Line* l = new Line( new Vector(1, 1) );

	print( l->evaluate( -1 ) );
	print( l->evaluate( 0 ) );
	print( l->evaluate( 1 ) );

	print( *intersect( new Line( new Vector(1, 1) ), new Line( new Vector(1, -1) ) ) );

	return 0;
}
