#include "NodeRenamer.h"

#include "HyperCore.h"
#include "HyperStandard.h"

using namespace std;

NodeRenamer::NodeRenamer() : HyperCircuit(), circuitIn("circuitIn"), oldName("oldName"), newName("newName"), nodeNameOut("nodeNameOut"), notFound("notFound"){
    addInlet(&circuitIn);
    addInlet(&oldName);
    addInlet(&newName);

    addOutlet(&nodeNameOut);
    addOutlet(&notFound);

    setNodeName("NodeRenamer");

    addNode(&nodeAccessor, "nodeAccessor");
    addNode(&nodeNamer, "nodeNamer");
    addNode(&nodeDetector, "nodeDetector");
    addNode(&nodeGate, "nodeGate");
    addNode(&tizer, "tizer");

    circuitIn.plug(&nodeAccessor.circuitIn);
    oldName.plug(&nodeAccessor.nodeNameIn);
    nodeAccessor.nodeOut.plug(&nodeNamer.nodeIn);
    newName.plug(&nodeNamer.nameIn);
    nodeNamer.nodeOut.plug(&nodeDetector.inlet);
    newName.plug(&nodeGate.inlet);
    nodeDetector.detect.plug(&nodeGate.trigger);
    nodeGate.outlet.plug(&nodeNameOut);
    nodeAccessor.notFound.plug(&tizer.booleanIn);
    tizer.transientOut.plug(&notFound);
}