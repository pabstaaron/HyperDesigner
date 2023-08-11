#pragma once

#include <vector>

#include "HyperCore.h"
#include "HyperStandard.h"

using namespace std;

/**
 * @brief A HyperCircuit for listing the inlets and outlets of a node in a circuit 
 */
class IOLister : public HyperCircuit{
private:
    NodeAccessor accessor;
    IOExtractor extractor;  

public:
    HyperRepeater<HyperCircuit*> circuitIn;
    HyperRepeater<string> nodeNameIn;

    HyperRepeater<vector<IHyperInlet*>> inletOut;
    HyperRepeater<vector<IHyperOutlet*>> outletOut;

    IOLister();
};