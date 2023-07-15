#include "NodeLister.h"

NodeLister::NodeLister() : HyperCircuit(), circuitIn("circuitIn"), nodeNameOut("nodeNameOut"), nodeUniqueNameOut("nodeUniqueNameOut"){
    addInlet(&circuitIn);
    addOutlet(&nodeNameOut);
    addOutlet(&nodeUniqueNameOut);
    setNodeName("NodeLister");

    addNode(&nodeExtractor, "nodeExtractor");
    addNode(&nodeSerializer, "nodeSerializer");
    addNode(&nodeNameExtractor, "nodeNameExtractor");

    circuitIn.plug(&nodeExtractor.circuitIn);
    nodeExtractor.nodesOut.plug(&nodeSerializer.inlet);
    nodeSerializer.outlet.plug(&nodeNameExtractor.nodeIn);
    nodeNameExtractor.nodeNameOut.plug(&nodeNameOut);
    nodeNameExtractor.nodeUniqueNameOut.plug(&nodeUniqueNameOut);
}