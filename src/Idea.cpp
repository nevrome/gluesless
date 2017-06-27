#include "Idea.h"

#include <algorithm>

#include "global.h"

Idea::Idea(Networkland* real) {
  //this->identity = create_random_string(30);
  this->identity = randunifrange(0, 100);

  this->realworld = real;

  vertex_desc randpos = randunifrange(
    0, (realworld->get_number_of_vertices() - 1)
    );

  this->vertices.push_back(randpos);
}

int Idea::get_identity() {
  return identity;
}

std::vector<vertex_desc> Idea::get_vertices() {
  return this->vertices;
}

void Idea::infect() {

  std::vector<vertex_desc> adjacentvecs;
  vertex_desc victim;
  double mindist;
  bool check = false;

  // iterate through all vertices occupied by the idea
  for (auto& p1 : vertices) {
    // get neighbouring vertices of the current vertex
    adjacentvecs = realworld->get_adjacent_vertices(p1);
    // iterate through all neighbouring vertices of the current vertex
    for (auto& p2 : adjacentvecs) {
      // check, if current neighbouring vertex is not already part of the idea
      // if it's part, then skip, else:
      if (!(find(vertices.begin(), vertices.end(), p2) !=
          vertices.end())) {
        // get the distance value between the two vertices
        double tempdist = realworld->get_distance_between_two_vertices(p1, p2);
        // search for victim with smalles distance
        if (!check) {
          mindist = tempdist;
          victim = p2;
          check = true;
        } else if (tempdist <= mindist) {
          mindist = tempdist;
          victim = p2;
        }
      }
    }
  }

  // if the previous loop found a victim (could for example fail,
  // if the idea is already everywhere), it can become part of the idea
  if (check) {
    // get probability decision about where an idea actually grows
    // dependend on the edge distance value of the victim node
    if (randunifrange(0, 101) > mindist*100) {
      vertices.push_back(victim);
    }
  }
}


// http://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
// std::string create_random_string(size_t length) {
//   auto randchar = []() -> char {
//     const char charset[] =
//       //"0123456789"
//       //"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//       //"abcdefghijklmnopqrstuvwxyz";
//       "abc";
//     const int max_index = (sizeof(charset) - 2);
//     return charset[randunifrange(0, max_index)];
//   };
//   std::string str(length, 'a');
//   std::generate_n(str.begin(), length, randchar);
//   return str;
// }

// size_t compare_ideas(Idea* a, Idea* b) {
//   std::string s0 = a->get_identity();
//   std::string s1 = b->get_identity();
//
//   size_t res = compare_strings(s0, s1);
//
//   Rcout << "distance between " << s0 << " and " << s1 << " : "
//         << res << std::endl;
//
//   return res;
// }

// https://rosettacode.org/wiki/Levenshtein_distance#C.2B.2B
// size_t compare_strings(const std::string &s1, const std::string &s2) {
//   const size_t m(s1.size());
//   const size_t n(s2.size());
//
//   if (m==0) return n;
//   if (n==0) return m;
//
//   size_t *costs = new size_t[n + 1];
//
//   for(size_t k=0; k<=n; k++) costs[k] = k;
//
//   size_t i = 0;
//   for (std::string::const_iterator it1 = s1.begin(); it1 != s1.end(); ++it1, ++i) {
//     costs[0] = i+1;
//     size_t corner = i;
//
//     size_t j = 0;
//     for (std::string::const_iterator it2 = s2.begin(); it2 != s2.end(); ++it2, ++j) {
//       size_t upper = costs[j+1];
//       if( *it1 == *it2 ) {
//         costs[j+1] = corner;
//       } else {
//         size_t t(upper<corner?upper:corner);
//         costs[j+1] = (costs[j]<t?costs[j]:t)+1;
//       }
//
//       corner = upper;
//     }
//   }
//
//   size_t result = costs[n];
//   delete [] costs;
//
//   return result;
// }
