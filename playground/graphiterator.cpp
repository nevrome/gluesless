  #include <iostream>                  
  #include <boost/graph/graph_traits.hpp>
  #include <boost/graph/adjacency_list.hpp>

  using namespace boost;
  
	// vertex struct to store some properties in vertices
  struct Vertex {
  	std::string name;
	};

  int main(int,char*[]) {
    // create a typedef for the graph type
    typedef adjacency_list<vecS, vecS, undirectedS, Vertex> Graph;

    // declare a graph object
    Graph g(3);

		// prepare iteration 
    typedef graph_traits<Graph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;

		// add some property data to the vertices
		vp = vertices(g);
		g[*vp.first].name = "A";
		g[*(++vp.first)].name = "B";
		g[*(++vp.first)].name = "C";

		// iterate over the vertices
    for (vp = vertices(g); vp.first != vp.second; ++vp.first)     
			std::cout << g[*vp.first].name <<  " ";
    std::cout << std::endl;

    return 0;
  }

