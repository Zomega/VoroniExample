#ifndef GRAPH_H
#define GRAPH_H

/* This specific implementation is designed for very spare graphs (i.e. the Voroni Graph). For denser Graphs, another implementation may have much better asymptotic time. */
#include <vector>

template <class NodeData, class EdgeData>
class EdgeStruct; // Forward declaration for linking purposes

template <class NodeData, class EdgeData>
class NodeStruct {
private:
	NodeData* data;
	std::vector< EdgeStruct< NodeData, EdgeData >* >* edges;
public:
	NodeStruct( NodeData* data ) {
		this->data = data;
		this->edges = new std::vector< EdgeStruct< NodeData, EdgeData >* >();
	}

	~NodeStruct() {
		delete this->data;
		delete this->edges;
	}

	NodeData* getData() {
		return this->data;
	}

	std::vector< EdgeStruct< NodeData, EdgeData >* >* getEdges() {
		return this->edges;
	}

	void addEdge( EdgeStruct< NodeData, EdgeData >* edge ) {
		this->edges->push_back( edge );
	}

	void removeEdge( NodeStruct< NodeData, EdgeData >* end, EdgeData* data ) {
		typename std::vector< EdgeStruct< NodeData, EdgeData >* >::iterator it;
		for ( it = this->edges->begin() ; it < this->edges->end(); it++ ) {
			if( ( (*it)->getEnd() == end ) && ( (*it)->getData() == data ) ) {
				edges->erase( it );
			}
		}
	}

	void purgeEdges( NodeStruct< NodeData, EdgeData >* end ) {
		typename std::vector< EdgeStruct< NodeData, EdgeData >* >::iterator it;
		for ( it = this->edges->begin() ; it < this->edges->end(); it++ ) {
			if( (*it)->getEnd() == end ) {
				edges->erase( it );
			}
		}
	}

	std::vector< NodeData* >* getNeighbors() {
		std::vector< NodeData* >* neighbors = new std::vector< NodeData* >();
		std::vector< EdgeStruct< NodeData, EdgeData >* >* edges = this->getEdges();
		typename std::vector< EdgeStruct< NodeData, EdgeData >* >::iterator it;
		for ( it = edges->begin() ; it < edges->end(); it++ ) {
			neighbors->push_back( (*it)->getEnd()->getData() );
			std::cout<<"\t"<<*( (*it)->getEnd()->getData() )<<"\n";
		}
		return neighbors;
	}
};

template <class NodeData, class EdgeData>
class EdgeStruct {
private:
	EdgeData* data;
	NodeStruct< NodeData, EdgeData >* end;
public:
	EdgeStruct( EdgeData* data, NodeStruct< NodeData, EdgeData >* end ) {
		this->data = data;
		this->end = end;
	}

	~EdgeStruct() {
		delete this->data;
		delete this->edges;
	}

	EdgeData* getData() {
		return this->data;
	}

	NodeStruct< NodeData, EdgeData >* getEnd() {
		return this->end;
	}
};

template <class NodeData, class EdgeData>
class Edge {
public:
	NodeData* start;
	NodeData* end;
	EdgeData* data;
};

template <class NodeData, class EdgeData>
class Graph {
	//TODO: Copy constructor;
	//TODO: Eventually, Graph should be an abstract class with many implementations for different types of asymptotic behavior.
	//TODO: Safetys and Errors.
private:
	bool directed;
	std::vector< NodeStruct< NodeData, EdgeData >* >* nodes;

	/*
	Returns the Node that contains the given data, if there is one. If not, Null is returned.
	*/
	NodeStruct< NodeData, EdgeData >* getNode( NodeData* data ) {
		typename std::vector< NodeStruct< NodeData, EdgeData >* >::iterator it;
		for ( it = this->nodes->begin() ; it < this->nodes->end(); it++ ) {
			if( (*it)->getData() == data ) {
				return (*it);
			}
		}
		return NULL;
	};
public:
	Graph( bool directed = false ) {
		this->directed = directed;
		this->nodes = new std::vector< NodeStruct< NodeData, EdgeData >* >();
	}

	~Graph() {
		delete nodes;
	}

	void addNode( NodeData* data ) {
		if( this->getNode( data ) ) {
			std::cout<< "ERROR! This node is already in the Graph. Adding this node was skipped...\n";
			return;
		}
		this->nodes->push_back( new NodeStruct< NodeData, EdgeData >( data ) );
	}

	void link( NodeData* start, NodeData* end, EdgeData* data = NULL ) {
		NodeStruct< NodeData, EdgeData >* startNode = this->getNode( start );
		NodeStruct< NodeData, EdgeData >* endNode = this->getNode( end );
		startNode->addEdge( new EdgeStruct< NodeData, EdgeData >( data, endNode ) );
		if( !( this->directed ) ) {
			endNode->addEdge( new EdgeStruct< NodeData, EdgeData >( data, startNode ) );
		}
	}

	void unlink( NodeData* start, NodeData* end, EdgeData* data = NULL ) {
		NodeStruct< NodeData, EdgeData >* startNode = this->getNode( start );
		NodeStruct< NodeData, EdgeData >* endNode = this->getNode( end );
		startNode->removeEdge( endNode, data );
		if( !( this->directed ) ) {
			endNode->removeEdge( startNode, data );
		}
	}

	void purgeLinks( NodeData* start, NodeData* end ) {
		NodeStruct< NodeData, EdgeData >* startNode = this->getNode( start );
		NodeStruct< NodeData, EdgeData >* endNode = this->getNode( end );
		startNode->purgeEdges( endNode );
		if( !( this->directed ) ) {
			endNode->purgeEdges( startNode );
		}
	}

	std::vector< NodeData* >* getNeighbors( NodeData* data ) {
		NodeStruct< NodeData, EdgeData >* node = this->getNode( data );
		if( node ) {
			return node->getNeighbors();
		}
		return NULL;
	}

	std::vector< NodeData* >* getNodes() {
		std::vector< NodeData* >* nodes = new std::vector< NodeData* >();
		typename std::vector< NodeStruct< NodeData, EdgeData >* >::iterator it;
		for ( it = this->nodes->begin() ; it < this->nodes->end(); it++ ) {
			nodes->push_back( (*it)->getData() );
		}
		return nodes;
	}

	std::vector< Edge< NodeData, EdgeData >* >* getEdges() {
		std::vector< Edge< NodeData, EdgeData >* >* edges = new std::vector< Edge< NodeData, EdgeData >* >();
		typename std::vector< NodeStruct< NodeData, EdgeData >* >::iterator nodeIt;
		for (
			nodeIt = this->nodes->begin();
			nodeIt < this->nodes->end();
			nodeIt++
		) {
			NodeStruct< NodeData, EdgeData >* node = *nodeIt;
			std::vector< EdgeStruct< NodeData, EdgeData >* >* nodeEdges = node->getEdges();
			typename std::vector< EdgeStruct< NodeData, EdgeData >* >::iterator edgeIt;
			for (
				edgeIt = nodeEdges->begin();
				edgeIt < nodeEdges->end();
				edgeIt++
			) {
				Edge< NodeData, EdgeData >* edge = new Edge< NodeData, EdgeData >();
				edge->start = node->getData();
				edge->end = (*edgeIt)->getEnd()->getData();
				edge->data = (*edgeIt)->getData();
				edges->push_back( edge );
			}
			
		}
		return edges;
	}

	//TODO: RM
	void print() {
		std::cout << "Graph Diagnostic Print:\n";

		std::cout << "Nodes:\n";
		typename std::vector< NodeStruct< NodeData, EdgeData >* >::iterator it;
		for ( it = this->nodes->begin() ; it < this->nodes->end(); it++ ) {
			std::cout<<"\t"<<*( (*it)->getData() )<<"\n";
		}
	}
};

#endif


