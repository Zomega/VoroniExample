std::vector< GraphicsEngine::GraphicsObject* >* GraphicsEngine::objects = new std::vector< GraphicsEngine::GraphicsObject* >();

Transform GraphicsEngine::camera = Transform();

double angle = 0;

void GraphicsEngine::render() {

	glClear(GL_COLOR_BUFFER_BIT);

	GraphicsEngine::camera = Transform( angle, Vector() );
	angle += 0.001;

	std::vector< GraphicsEngine::GraphicsObject* >::iterator current;
	for (
		current = GraphicsEngine::objects->begin();
		current < GraphicsEngine::objects->end();
		current++
	) {
		GraphicsObject* object = *current;
		GraphicsEngine::setColor( object->color );
		switch( object->type ) {
		case POINT:
			GraphicsEngine::renderPoint( (Vector*) object->data );
			break;
		case TRIANGLE:
			GraphicsEngine::renderTriangle( (Triangle*) object->data );
			break;
		case POLYGON:
			GraphicsEngine::renderPolygon( (Polygon*) object->data );
			break;
		case LINE:
			GraphicsEngine::renderLine( (Line*) object->data );
			break;
		case LINESEGMENT:
			GraphicsEngine::renderLineSegment( (LineSegment*) object->data );
			break;
		case GRAPH:
			GraphicsEngine::renderGraph( (Graph< Vector, void >*) object->data );
			break;
		}
	}
	glFlush();
	glutPostRedisplay();//Start drawing again
}

void GraphicsEngine::renderPoint( Vector* point ) {
	float pointsize = 0.05;
	GraphicsEngine::renderPolygon( regularPolygon( *point, pointsize, 20 ) );
	GraphicsEngine::Vertex2f( *point );
}

void GraphicsEngine::renderTriangle( Triangle* triangle ) {
	glBegin(GL_TRIANGLES);
	GraphicsEngine::Vertex2f( triangle->point1 );
	GraphicsEngine::Vertex2f( triangle->point2 );
	GraphicsEngine::Vertex2f( triangle->point3 );
	glEnd();
}

void GraphicsEngine::renderPolygon( Polygon* polygon ) {

	glBegin(GL_POLYGON);//Start drawing a polygon
	std::vector< Vector >::iterator current;
	for (
		current = polygon->vertices->begin();
		current < polygon->vertices->end();
		current++
	) {
		GraphicsEngine::Vertex2f( *current );
	}
	glEnd();
	
}

void GraphicsEngine::renderLineSegment( LineSegment* segment ) {
	glBegin(GL_LINES);
	GraphicsEngine::Vertex2f( segment->getStart() );
	GraphicsEngine::Vertex2f( segment->getEnd() );
	glEnd();
}

void GraphicsEngine::renderLine( Line* line ) {
	glBegin(GL_LINES);
	GraphicsEngine::Vertex2f( line->evaluate( -100 ) );
	GraphicsEngine::Vertex2f( line->evaluate( 100 ) );
	glEnd();
}

void GraphicsEngine::renderGraph( Graph< Vector, void >* graph ) {

	std::vector< Edge< Vector, void >* >* edges = graph->getEdges();
	typename std::vector< Edge< Vector, void >* >::iterator edgeIt;
	for (
		edgeIt = edges->begin();
		edgeIt < edges->end();
		edgeIt++
	) {
		LineSegment* segment =  new LineSegment( (*edgeIt)->start, (*edgeIt)->end );
		GraphicsEngine::renderLineSegment( segment );
		delete segment;
	}

	// Render Nodes.
	std::vector< Vector* >* nodes = graph->getNodes();
	typename std::vector< Vector* >::iterator nodeIt;
	for (
		nodeIt = nodes->begin();
		nodeIt < nodes->end();
		nodeIt++
	) {
		GraphicsEngine::renderPoint( *nodeIt );
	}
};

void GraphicsEngine::Vertex2f( Vector point ) {
	Vector transformed = GraphicsEngine::camera * point;
	glVertex2f( transformed.x, transformed.y );
}

void GraphicsEngine::setColor( Color color ) {
	glColor3f( color.r, color.g, color.b );
}

int GraphicsEngine::Width() {
	return glutGet(GLUT_WINDOW_WIDTH);
}

int GraphicsEngine::Height() {
	return glutGet(GLUT_WINDOW_HEIGHT);
}

void GraphicsEngine::initiate() {
	glutInitWindowSize( 800, 600 );//define the window size
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);//Define the drawing mode
	glutCreateWindow("Graphics Engine Test");//Create our window
	Color background = BLACK;
	glClearColor( background.r, background.g, background.b, 0 );
	gluOrtho2D( -GraphicsEngine::Width()*scale, GraphicsEngine::Width()*scale, -GraphicsEngine::Height()*scale, GraphicsEngine::Height()*scale );
	glutDisplayFunc( GraphicsEngine::render );
};

void GraphicsEngine::add( Vector* vector, Color color = WHITE ) {
	GraphicsEngine::objects->push_back(
		new GraphicsObject(
			(void*)vector,
			POINT,
			color
		)
	);
};

void GraphicsEngine::add( Triangle* triangle, Color color = WHITE ) {
	GraphicsEngine::objects->push_back(
		new GraphicsObject(
			(void*)triangle,
			TRIANGLE,
			color
		)
	);
};

void GraphicsEngine::add( Polygon* polygon, Color color = WHITE ) {
	GraphicsEngine::objects->push_back(
		new GraphicsObject(
			(void*)polygon,
			POLYGON,
			color
		)
	);
};

void GraphicsEngine::add( LineSegment* segment, Color color = WHITE ) {
	GraphicsEngine::objects->push_back(
		new GraphicsObject(
			(void*)segment,
			LINESEGMENT,
			color
		)
	);
};

void GraphicsEngine::add( Line* line, Color color = WHITE ) {
	GraphicsEngine::objects->push_back(
		new GraphicsObject(
			(void*)line,
			LINE,
			color
		)
	);
};

void GraphicsEngine::add( Graph< Vector, void >* graph, Color color = WHITE ) {
	GraphicsEngine::objects->push_back(
		new GraphicsObject(
			(void*)graph,
			GRAPH,
			color
		)
	);
};
