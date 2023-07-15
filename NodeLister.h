#pragma once

#include "HyperCore.h"
#include "HyperStandard.h"

using namespace std;

class NodeLister : public HyperCircuit{
protected:
    NodeExtractor nodeExtractor;
    Serializer<HyperNode*> nodeSerializer;
    NodeNameExtractor nodeNameExtractor;
public:
    HyperRepeater<HyperCircuit*> circuitIn;

    HyperRepeater<string> nodeNameOut;
    HyperRepeater<string> nodeUniqueNameOut;

    NodeLister();
};
