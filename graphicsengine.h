#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

/*** System Includes ***/
#include <GL/glut.h>
#include <vector>

/*** Ninjinuity Includes ***/
#include "vector.h"
#include "color.h"
#include "linesegment.h"
#include "triangle.h"
#include "polygon.h"
#include "transform.h"
#include "graph.h"

class GraphicsEngine {
private:
	enum GraphicsType {
		POINT,
		TRIANGLE,
		POLYGON,
		LINE,
		LINESEGMENT,
		GRAPH,
	};

	class GraphicsObject {
	public:
		GraphicsObject( void* data, GraphicsType type, Color color ) {
			this->data = data;
			this->type = type;
			this->color = color;
		};
		GraphicsType type;
		Color color;
		void* data;
	};

	static std::vector< GraphicsObject* >* objects;
	static Transform camera;

	void static render();
	static void renderPoint( Vector* );
	static void renderTriangle( Triangle* );
	static void renderPolygon( Polygon* );
	static void renderLine( Line* );
	static void renderLineSegment( LineSegment* );
	static void renderGraph( Graph< Vector, void >* );

	static void Vertex2f( Vector point );
	static void setColor( Color );

public:
	static int Width();
	static int Height();

	static const double scale = .01;

	static void initiate();
	static void run() {
		glutMainLoop();
	}

	static void add( Vector*, Color );
	static void add( Triangle*, Color );
	static void add( Polygon*, Color );
	static void add( Line*, Color );
	static void add( LineSegment*, Color );
	static void add( Graph< Vector, void >*, Color );
};

#include "graphicsengine.cpp"

#endif
