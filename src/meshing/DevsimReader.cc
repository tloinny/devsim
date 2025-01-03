/***
DEVSIM
Copyright 2013 DEVSIM LLC

SPDX-License-Identifier: Apache-2.0
***/

#include "DevsimReader.hh"
#include "DevsimLoader.hh"

namespace dsDevsimParse {
int meshlineno;
dsMesh::DevsimLoaderPtr  DevsimLoader;
dsMesh::MeshRegionPtr    MeshRegion;
dsMesh::MeshContactPtr   MeshContact;
dsMesh::MeshInterfacePtr MeshInterface;
dsMesh::SolutionPtr      Sol;
dsMesh::EquationPtr      Equation;
std::string errors;
}

namespace dsDevsimParse
{
void DeletePointers()
{
    MeshRegion.reset();
    MeshContact.reset();
    MeshInterface.reset();
    Sol.reset();
    Equation.reset();
}
}

