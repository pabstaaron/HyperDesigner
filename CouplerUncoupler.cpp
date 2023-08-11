#include "CouplerUncoupler.h"

#include "HyperCore.h"
#include "HyperStandard.h"

CouplerUncoupler::CouplerUncoupler() : HyperCircuit(),
                                       circuitIn("circuitIn"),
                                        inletsNodeName("inletsNodeName"),
                                        inletsName("inletsName"),
                                        outletsNodeName("outletsNodeName"),
                                        outletsName("outletsName"),
                                        couple("couple"),
                                        success("success"),
                                        nodeNotFound("nodeNotFound"){
    addInlet(&circuitIn);
    addInlet(&inletsNodeName);
    addInlet(&inletsName);
    addInlet(&outletsNodeName);
    addInlet(&outletsName);
    addInlet(&couple);

    addOutlet(&success);
    addOutlet(&nodeNotFound);
    addOutlet(&inletNotFound);

    addNode(&inletsNodeAccessor, "inletsNodeAccessor");
    addNode(&outletsNodeAccessor, "outletsNodeAccessor");
    addNode(&inletsNodeNameDetector, "inletsNodeNameDetector");
    addNode(&outletsNodeNameDetector, "outletsNodeNameDetector");
    addNode(&inletsNodeGate, "inletsNodeGate");
    addNode(&outletsNodeGate, "outletsNodeGate");
    addNode(&tizerA, "tizerA");
    addNode(&tizerB, "tizerB");
    addNode(&inletsNodeDetector, "inletsNodeDetector");
    addNode(&outletsNodeDetector, "outletsNodeDetector");
    addNode(&inletDetector, "inletDetector");
    addNode(&outletDetector, "outletDetector");
    addNode(&inletsNameGate, "inletsNameGate");
    addNode(&outletsNameGate, "outletsNameGate");
    addNode(&inletAccessor, "inletAccessor");
    addNode(&outletAccessor, "outletAccessor");
    addNode(&inletDemuxer, "inletDemuxer");
    addNode(&outletDemuxer, "outletDemuxer");
    addNode(&coupler, "coupler");
    addNode(&uncoupler, "uncoupler");
    addNode(&successFunnel, "successFunnel");
    addNode(&nodeNotFoundFunnel, "nodeNotFoundFunnel");
    addNode(&coupleReinterpreter, "coupleReinterpreter");

    circuitIn.plug(&inletsNodeAccessor.circuitIn);
    circuitIn.plug(&outletsNodeAccessor.circuitIn);
    
    inletsNodeName.plug(&inletsNodeAccessor.nodeNameIn);
    outletsNodeName.plug(&outletsNodeAccessor.nodeNameIn);

    inletsNodeAccessor.nodeOut.plug(&inletsNodeNameDetector.inlet);
    outletsNodeAccessor.nodeOut.plug(&outletsNodeNameDetector.inlet);
    inletsNodeAccessor.notFound.plug(&tizerA.booleanIn);
    outletsNodeAccessor.notFound.plug(&tizerB.booleanIn);

    inletsNodeNameDetector.outlet.plug(&inletsNodeGate.inlet);
    inletsNodeNameDetector.detect.plug(&outletsNodeGate.trigger);

    outletsNodeNameDetector.outlet.plug(&outletsNodeGate.inlet);
    outletsNodeNameDetector.detect.plug(&inletsNodeGate.trigger);

    tizerA.transientOut.plug(&inletsNodeGate.reset);
    tizerB.transientOut.plug(&outletsNodeGate.reset);
    tizerA.transientOut.plug(nodeNotFoundFunnel.inlets.spawnBack()); 
    tizerB.transientOut.plug(nodeNotFoundFunnel.inlets.spawnBack());

    inletsNodeGate.outlet.plug(&inletsNodeDetector.inlet);
    outletsNodeGate.outlet.plug(&outletsNodeDetector.inlet);
    inletsNodeDetector.detect.plug(&coupleGateA.trigger);
    nodeNotFoundFunnel.outlet.plug(&coupleGateA.reset); 

    inletsNodeDetector.outlet.plug(&inletAccessor.nodeIn);
    outletsNodeDetector.outlet.plug(&outletAccessor.nodeIn);
    inletsNodeDetector.detect.plug(&inletsNameGate.trigger);
    outletsNodeDetector.detect.plug(&outletsNameGate.trigger);

    nodeNotFoundFunnel.outlet.plug(&inletsNameGate.reset);
    nodeNotFoundFunnel.outlet.plug(&outletsNameGate.reset);

    inletsNameGate.outlet.plug(&inletAccessor.inletNameIn);
    outletsNameGate.outlet.plug(&outletAccessor.outletNameIn);

    inletAccessor.inletOut.plug(&inletDemuxer.inlet);
    outletAccessor.outletOut.plug(&outletDemuxer.inlet);

    inletDemuxer.outlets.plugBack(&coupler.inletIn);
    inletDemuxer.outlets.plugBack(&uncoupler.inletIn);
    outletDemuxer.outlets.plugBack(&coupler.outletIn);
    outletDemuxer.outlets.plugBack(&uncoupler.outletIn);

    couple.plug(&coupleGateA.inlet);
    coupleGateA.outlet.plug(&coupleGateB.inlet);
    coupleGateB.outlet.plug(&coupleReinterpreter.inlet);
    coupleReinterpreter.outlet.plug(&inletDemuxer.selectInlet);
    coupleReinterpreter.outlet.plug(&outletDemuxer.selectInlet);

    coupler.success.plug(successFunnel.inlets.spawnBack());
    uncoupler.success.plug(successFunnel.inlets.spawnBack());

    successFunnel.outlet.plug(&success);

    nodeNotFoundFunnel.outlet.plug(&nodeNotFound);

    inletAccessor.notFound.plug(&inletNotFound);
    outletAccessor.notFound.plug(&outletNotFound);
}