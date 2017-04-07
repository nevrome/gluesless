#include <Rcpp.h>
#include <vector>

#include "Timeline.h"
#include "Aether.h"

using namespace Rcpp;
using namespace std;

Timeline::Timeline(Aether* start) {
  this->ideanumber.push_back(start->get_ideanumber());
}

void Timeline::develop(Aether* current) {
  this->ideanumber.push_back(current->get_ideanumber());
  this->ideas.push_back(current->get_ideas());
  this->idea_vertices.push_back(current->get_idea_vertices());

  current->develop();

  Rcout << "Zeitschritt vorwärts! " << endl;
}

// R-exporter
SEXP Timeline::export_as_R_list() {
  List res;

  NumericVector ideanumber_nv(ideanumber.begin(), ideanumber.end());

  NumericVector timestep;
  NumericVector id;
  NumericVector vert;

  int count = 0;
  vector< vector<int> >::iterator it_id_1=ideas.begin();

  for (vector< vector< vector<Vertexdesc> > >::iterator it_vert_1=idea_vertices.begin();
       it_vert_1!=idea_vertices.end(); ++it_vert_1) {

    vector<int>::iterator it_id_2=(*it_id_1).begin();

    for (vector< vector<Vertexdesc> >::iterator it_vert_2=(*it_vert_1).begin();
         it_vert_2!=(*it_vert_1).end(); ++it_vert_2) {

      for (vector<Vertexdesc>::iterator it_vert_3=(*it_vert_2).begin();
           it_vert_3!=(*it_vert_2).end(); ++it_vert_3) {

        timestep.push_back(count);
        id.push_back(*it_id_2);
        vert.push_back(*it_vert_3);

      }

    it_id_2++;

    }

  it_id_1++;
  count++;

  }

  res["number_of_ideas"] = ideanumber_nv;
  res["idea_exp"] = DataFrame::create(
    _["timestep"] = timestep,
    _["ideas"] = id,
    _["vertices"] = vert
    );

  return res;
}