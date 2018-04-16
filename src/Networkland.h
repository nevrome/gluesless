#pragma once

#include "Snap.h"

//! Real world represented with a network - ABM environment
/*!
 Could represent a spatial, cultural etc. network.
 */

class Networkland {

    public:
    Networkland(const TStr& pajek_file_path);
    Networkland(PUNGraph newgraph);

    private:
    PUNGraph graph;
};

