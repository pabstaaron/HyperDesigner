#include "CouplerUncoupler.h"

#include "HyperCore.h"
#include "HyperStandard.h"

#include "CouplerUncouplerNodes/NodeGetAndChecker.h"
#include "CouplerUncouplerNodes/IOGetAndChecker.h"
#include "CouplerUncouplerNodes/CoupleButterfly.h"

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
    addOutlet(&outletNotFound);

    // Add nodes
    addNode(&nodeGetAndChecker, "nodeGetAndChecker");
    addNode(&ioGetAndChecker, "ioGetAndChecker");
    addNode(&coupleButterfly, "coupleButterfly");

    // Wire up
    circuitIn.plug(&nodeGetAndChecker.circuitIn);
    inletsNodeName.plug(&nodeGetAndChecker.inletsNodeName);
    inletsName.plug(&nodeGetAndChecker.inletsName);
    outletsNodeName.plug(&nodeGetAndChecker.outletsNodeName);
    outletsName.plug(&nodeGetAndChecker.outletsName);
    couple.plug(&nodeGetAndChecker.couple);

    // nodeGetAndChecker.

    nodeGetAndChecker.inletsNodeOut.plug(&ioGetAndChecker.inletsNodeIn);
    nodeGetAndChecker.inletsNameOut.plug(&ioGetAndChecker.inletsNameIn);
    nodeGetAndChecker.outletsNodeOut.plug(&ioGetAndChecker.outletsNodeIn);
    nodeGetAndChecker.outletsNameOut.plug(&ioGetAndChecker.outletsNameIn);

    ioGetAndChecker.inletOut.plug(&coupleButterfly.inletIn);
    ioGetAndChecker.outletOut.plug(&coupleButterfly.outletIn);
    ioGetAndChecker.coupleOut.plug(&coupleButterfly.coupleIn);

    coupleButterfly.successOut.plug(&success);
}