/***
DEVSIM
Copyright 2013 Devsim LLC

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
***/

#ifndef VECTOR_TETRAHEDRON_EDGE_FROM_EDGE_MODEL_HH
#define VECTOR_TETRAHEDRON_EDGE_FROM_EDGE_MODEL_HH
#include "TetrahedronEdgeModel.hh"
class VectorTetrahedronEdgeModel : public TetrahedronEdgeModel {
    public:
        //// Out naming convention is that the name given is the edge model
        //// The element edge model is edgemodel_ex, edgemodel_ey
        VectorTetrahedronEdgeModel(const std::string &, RegionPtr);

        void Serialize(std::ostream &) const;

    private:
        void calcTetrahedronEdgeScalarValues() const;

        const std::string elementEdgeModelName;
        std::string       y_ModelName;
        std::string       z_ModelName;
};
#endif
