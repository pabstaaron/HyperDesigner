#pragma once

#include "HyperCore.h"
#include "HyperStandard.h"

using namespace std;

class NodeRenamer : public HyperCircuit{
private:
    NodeAccessor nodeAccessor;
    NodeNamer nodeNamer;
    HyperDetector<HyperNode*> nodeDetector;
    HyperGate<string> nodeGate;
    Transitizer tizer;
public:
    HyperRepeater<HyperCircuit*> circuitIn;
    HyperRepeater<string> oldName;
    HyperRepeater<string> newName;

    HyperRepeater<string> nodeNameOut;
    HyperRepeater<bool> notFound;

    NodeRenamer();
};