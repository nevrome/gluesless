  #include <iostream>                  
  #include <boost/graph/graph_traits.hpp>
  #include <boost/graph/adjacency_list.hpp>
  #include <algorithm>    // std::random_shuffle
  #include <vector>       // std::vector
  #include <ctime>        // std::time
  #include <cstdlib>      // std::rand, std::srand

  using namespace boost;
  
  // vertex struct to store some properties in vertices
  struct Vertex {
    std::string name;
  };

  // random number generator function
  int myrandom (int i) { 
    return std::rand()%i;
  }

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

    // initialize pseudo random number generator
    std::srand(unsigned (std::time(0)));

    // create offset vector
    std::vector<int> myvector;
    for (int i=0; i<3; ++i) {
      myvector.push_back(i);
    }

    // using myrandom to shuffle offset vector
    std::random_shuffle(myvector.begin(), myvector.end(), myrandom);
    
    // keep vp.first at the start 
    vp = vertices(g);

    // iterate over the vertices effectively shuffled by the offset
    vertex_iter dummy_iter;
    for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it) {
      dummy_iter = vp.first + *it;
      std::cout << g[*dummy_iter].name <<  " ";
    }
    std::cout << std::endl;

    return 0;
  }
