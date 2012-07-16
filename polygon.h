//TODO Write this class properly, or remove it completely.

struct Polygon {
	std::vector< Vector >* vertices;
};

Polygon* regularPolygon( Vector center, double size, double numSides ) {

	Transform transform = Transform( 2 * 3.14159 / numSides, Vector() );
	Vector pointOnPolygon = Vector( 0, size );

	Polygon* polygon = new Polygon();
	polygon->vertices = new std::vector< Vector >();
	for( int i = 0; i < numSides; i++ ) {
		polygon->vertices->push_back( pointOnPolygon + center );
		pointOnPolygon = transform * pointOnPolygon;
	}

	return polygon;
}
