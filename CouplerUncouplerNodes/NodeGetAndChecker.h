#pragma once

#include "HyperCore.h"
#include "HyperStandard.h"

class NodeGetAndChecker : public HyperCircuit {
public:
    // Inlets
    HyperRepeater<HyperCircuit*> circuitIn;

    HyperRepeater<string> inletsNodeName;
    HyperRepeater<string> inletsName;

    HyperRepeater<string> outletsNodeName;
    HyperRepeater<string> outletsName;

    HyperRepeater<bool> couple; 

    // Outlets
    HyperRepeater<HyperNode*> inletsNodeOut;
    HyperRepeater<HyperNode*> outletsNodeOut;
    HyperRepeater<string> inletsNameOut;
    HyperRepeater<string> outletsNameOut;
    HyperRepeater<bool> coupleOut;


    NodeGetAndChecker() : HyperCircuit(true) {
        setNodeName("NodeGetAndChecker");

        addInlet(&circuitIn);
        addInlet(&inletsNodeName);
        addInlet(&inletsName);
        addInlet(&outletsNodeName);
        addInlet(&outletsName);
        addInlet(&couple);

        addOutlet(&inletsNodeOut);
        addOutlet(&outletsNodeOut);
        addOutlet(&inletsNameOut);
        addOutlet(&outletsNameOut);
        addOutlet(&coupleOut);

        // addOutlet(&inletsNodeNotFound);
        // addOutlet(&outletsNodeNotFound);

        // Add nodes
        addNode(&inletsNodeAccessor, "inletsNodeAccessor");
        addNode(&outletsNodeAccessor, "outletsNodeAccessor");

        addNode(&inletNodeNotFoundInverter, "inletNodeNotFoundInverter");
        addNode(&outletNodeNotFoundInverter, "outletNodeNotFoundInverter");

        addNode(&inletGateResetAnd, "inletGateResetAnd");
        addNode(&outletGateResetAnd, "outletGateResetAnd");
        addNode(&inletGateResetTransitizer, "inletGateResetTransitizer");
        addNode(&outletGateResetTransitizer, "outletGateResetTransitizer");

        addNode(&nodeNotFoundAnd, "nodeNotFoundAnd");
        addNode(&onNodeFound, "onNodeFound");

        addNode(&inletsNodeNotFound, "inletsNodeNotFound");
        addNode(&outletsNodeNotFound, "outletsNodeNotFound");

        addNode(&inletsNodeGate, "inletsNodeGate");
        addNode(&outletsNodeGate, "outletsNodeGate");
        addNode(&inletsNameGate, "inletsNameGate");
        addNode(&outletsNameGate, "outletsNameGate");
        addNode(&coupleGate, "coupleGate");

        // Wire up
        circuitIn.plug(&inletsNodeAccessor.circuitIn);
        circuitIn.plug(&outletsNodeAccessor.circuitIn);
        inletsNodeName.plug(&inletsNodeAccessor.nodeNameIn);
        outletsNodeName.plug(&outletsNodeAccessor.nodeNameIn);

        inletsNodeAccessor.notFound.plug(&inletNodeNotFoundInverter.inlet);
        outletsNodeAccessor.notFound.plug(&outletNodeNotFoundInverter.inlet);

        inletsNodeAccessor.nodeOut.plug(&inletsNodeGate.inlet);
        outletsNodeAccessor.nodeOut.plug(&outletsNodeGate.inlet);

        inletsName.plug(&inletsNameGate.inlet);
        outletsName.plug(&outletsNameGate.inlet);
        couple.plug(&coupleGate.inlet);

        // inlet reset circuitry
        inletNodeNotFoundInverter.outlet.plug(inletGateResetAnd.inlets.spawnBack());
        outletsNodeAccessor.notFound.plug(inletGateResetAnd.inlets.spawnBack());
        inletGateResetAnd.outlet.plug(&inletGateResetTransitizer.booleanIn);
        inletGateResetTransitizer.transientOut.plug(&inletsNodeGate.reset);

        // outlet reset circuitry
        outletNodeNotFoundInverter.outlet.plug(outletGateResetAnd.inlets.spawnBack());
        inletsNodeAccessor.notFound.plug(outletGateResetAnd.inlets.spawnBack());
        outletGateResetAnd.outlet.plug(&outletGateResetTransitizer.booleanIn);
        outletGateResetTransitizer.transientOut.plug(&outletsNodeGate.reset);

        inletNodeNotFoundInverter.outlet.plug(nodeNotFoundAnd.inlets.spawnBack());
        outletNodeNotFoundInverter.outlet.plug(nodeNotFoundAnd.inlets.spawnBack());
        nodeNotFoundAnd.outlet.plug(&onNodeFound.booleanIn);
        nodeNotFoundAnd.outlet.plug(&inletsNameGate.allow);
        nodeNotFoundAnd.outlet.plug(&outletsNameGate.allow);
        nodeNotFoundAnd.outlet.plug(&coupleGate.allow);

        onNodeFound.transientOut.plug(&inletsNodeGate.trigger);
        onNodeFound.transientOut.plug(&outletsNodeGate.trigger);

        inletsNodeAccessor.notFound.plug(&inletsNodeNotFound.booleanIn);
        outletsNodeAccessor.notFound.plug(&outletsNodeNotFound.booleanIn);

        // Outlets
        inletsNodeGate.outlet.plug(&inletsNodeOut);
        outletsNodeGate.outlet.plug(&outletsNodeOut);
        inletsNameGate.outlet.plug(&inletsNameOut);
        outletsNameGate.outlet.plug(&outletsNameOut);
        coupleGate.outlet.plug(&coupleOut);

        // inletsNodeNotFound.transientOut.plug(&inle);
        // outletsNodeNotFound.transientOut.plug(&outletsNodeNotFound);
    }   

private:
    NodeAccessor inletsNodeAccessor;
    NodeAccessor outletsNodeAccessor;

    Negater<bool> inletNodeNotFoundInverter;
    Negater<bool> outletNodeNotFoundInverter;

    Ander<bool> inletGateResetAnd;
    Ander<bool> outletGateResetAnd;
    Transitizer inletGateResetTransitizer;
    Transitizer outletGateResetTransitizer;

    Ander<bool> nodeNotFoundAnd;
    Transitizer onNodeFound;

    Transitizer inletsNodeNotFound;
    Transitizer outletsNodeNotFound;

    // Gates for stopping flow if one of the nodes ot ports is not found
    HyperGate<HyperNode*> inletsNodeGate;
    HyperGate<HyperNode*> outletsNodeGate;
    SyncGate<string> inletsNameGate;
    SyncGate<string> outletsNameGate;
    SyncGate<bool> coupleGate;
};