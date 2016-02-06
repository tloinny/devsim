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

#include "TriangleNodeVolume.hh"
#include "dsAssert.hh"
#include "TriangleEdgeScalarData.hh"
#include "Region.hh"
#include "EdgeModel.hh"
#include "Edge.hh"

TriangleNodeVolume::TriangleNodeVolume(RegionPtr rp)
    : TriangleEdgeModel("ElementNodeVolume", rp, TriangleEdgeModel::SCALAR)
{
    RegisterCallback("EdgeLength");
    RegisterCallback("ElementEdgeCouple");
}

void TriangleNodeVolume::calcTriangleEdgeScalarValues() const
{
  const Region &r = GetRegion();
  const size_t dimension = r.GetDimension();

  ConstTriangleEdgeModelPtr eec = r.GetTriangleEdgeModel("ElementEdgeCouple");
  dsAssert(eec.get(), "UNEXPECTED");

  ConstEdgeModelPtr elen = r.GetEdgeModel("EdgeLength");
  dsAssert(elen.get(), "UNEXPECTED");

  const EdgeScalarList elens = elen->GetScalarValues();

  TriangleEdgeScalarData evol = TriangleEdgeScalarData(*eec);

  dsAssert(dimension == 2, "UNEXPECTED");

  //// 0.5 * edgecouple * (0.5 * edgelength)
  evol *= 0.25;

  const ConstTriangleList &tl = GetRegion().GetTriangleList();
  std::vector<double> ev(3 * tl.size());

  for (size_t tindex = 0; tindex < tl.size(); ++tindex)
  {

    const Region::TriangleToConstEdgeList_t &ttelist = GetRegion().GetTriangleToEdgeList();
    const ConstEdgeList &edgeList = ttelist[tindex];

    /// teindex is 0,1,2
    for (size_t teindex = 0; teindex < edgeList.size(); ++teindex)
    {
      double vol = elens[edgeList[teindex]->GetIndex()];
      //// TODO: get rid of this messy indexing scheme
      vol *= evol[3*tindex + teindex];

      const size_t oindex = 3*tindex + teindex;
      /// The symmetry that both nodes on an element edge have the same volume may not apply in 3D
      ev[oindex] = vol;
    }
  }

  SetValues(ev);
}

void TriangleNodeVolume::Serialize(std::ostream &of) const
{
  SerializeBuiltIn(of);
}

