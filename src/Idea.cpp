#include <Rcpp.h>
#include <string>
#include <algorithm>

#include "Idea.h"
#include "global.h"
#include "Networkland.h"

using namespace Rcpp;
using namespace std;

// constructor
Idea::Idea(Networkland* real) {
  this->identity = create_random_string(30);

  this->realworld = real;

  Vertexdesc randpos = randunifrange(0, (realworld->get_number_of_vertices() - 1));

  this->vertices.push_back(randpos);
}

// getter
string Idea::get_identity() {
  return identity;
}

vector<Vertexdesc> Idea::get_vertices() {
  return this->vertices;
}

// developer
void Idea::infect() {

  vector<Vertexdesc> adjacentvecs;
  Vertexdesc victim;
  double mindist;
  bool check = false;

  for (vector<Vertexdesc>::iterator p1=vertices.begin(); p1!=vertices.end(); ++p1) {
    adjacentvecs = realworld->get_adjacent_vertices(*p1);
    for (vector<Vertexdesc>::iterator p2=adjacentvecs.begin(); p2!=adjacentvecs.end(); ++p2) {
      if (find(vertices.begin(), vertices.end(), *p2) != vertices.end()) {
        break;
      } else {
        double tempdist = realworld->get_distance_between_two_vertices(*p1, *p2);
        if (!check) {
          mindist = tempdist;
          victim = *p2;
          check = true;
        } else if (tempdist <= mindist) {
          mindist = tempdist;
          victim = *p2;
        }
      }
    }
  }

  if (check) {
    vertices.push_back(victim);
  }
}


// http://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
std::string create_random_string(size_t length) {
  auto randchar = []() -> char {
    const char charset[] =
      //"0123456789"
      //"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
      //"abcdefghijklmnopqrstuvwxyz";
      "abc";
    const int max_index = (sizeof(charset) - 2);
    return charset[randunifrange(0, max_index)];
  };
  std::string str(length, 'a');
  std::generate_n(str.begin(), length, randchar);
  return str;
}

size_t compare_ideas(Idea* a, Idea* b) {
  std::string s0 = a->get_identity();
  std::string s1 = b->get_identity();

  size_t res = compare_strings(s0, s1);

  Rcout << "distance between " << s0 << " and " << s1 << " : "
        << res << std::endl;

  return res;
}

// https://rosettacode.org/wiki/Levenshtein_distance#C.2B.2B
size_t compare_strings(const std::string &s1, const std::string &s2) {
  const size_t m(s1.size());
  const size_t n(s2.size());

  if (m==0) return n;
  if (n==0) return m;

  size_t *costs = new size_t[n + 1];

  for(size_t k=0; k<=n; k++) costs[k] = k;

  size_t i = 0;
  for (std::string::const_iterator it1 = s1.begin(); it1 != s1.end(); ++it1, ++i) {
    costs[0] = i+1;
    size_t corner = i;

    size_t j = 0;
    for (std::string::const_iterator it2 = s2.begin(); it2 != s2.end(); ++it2, ++j) {
      size_t upper = costs[j+1];
      if( *it1 == *it2 ) {
        costs[j+1] = corner;
      } else {
        size_t t(upper<corner?upper:corner);
        costs[j+1] = (costs[j]<t?costs[j]:t)+1;
      }

      corner = upper;
    }
  }

  size_t result = costs[n];
  delete [] costs;

  return result;
}
