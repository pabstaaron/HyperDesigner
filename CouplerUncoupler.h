#pragma once

#include "HyperCore.h"
#include "HyperStandard.h"

class CouplerUncoupler : public HyperCircuit {
public:
    // Inlets
    HyperRepeater<HyperCircuit*> circuitIn;

    HyperRepeater<string> inletsNodeName;
    HyperRepeater<string> inletsName;

    HyperRepeater<string> outletsNodeName;
    HyperRepeater<string> outletsName;

    HyperRepeater<bool> couple; // True for couple, false for uncouple

    // Outlets
    HyperRepeater<bool> success; // Transient indicating success
    HyperRepeater<bool> nodeNotFound; // Transient indicating that a node was not found
    HyperRepeater<bool> inletNotFound; // Transient indicating that an inlet was not found
    HyperRepeater<bool> outletNotFound; // Transient indicating that an outlet was not found

    CouplerUncoupler();

private:
    NodeAccessor inletsNodeAccessor;
    NodeAccessor outletsNodeAccessor;

    HyperDetector<HyperNode*> inletsNodeNameDetector;
    HyperDetector<HyperNode*> outletsNodeNameDetector;

    // Gates for stopping flow if one of the nodes ot ports is not found
    HyperGate<HyperNode*> inletsNodeGate;
    HyperGate<HyperNode*> outletsNodeGate;
    Transitizer tizerA;
    Transitizer tizerB;

    HyperDetector<HyperNode*> inletsNodeDetector;
    HyperDetector<HyperNode*> outletsNodeDetector;

    HyperDetector<IHyperInlet*> inletDetector;
    HyperDetector<IHyperOutlet*> outletDetector;

    HyperGate<string> inletsNameGate;
    HyperGate<string> outletsNameGate;

    InletAccessor inletAccessor;
    OutletAccessor outletAccessor;

    SyncDemuxer<IHyperInlet*> inletDemuxer;
    SyncDemuxer<IHyperOutlet*> outletDemuxer;

    Coupler coupler;
    Uncoupler uncoupler;

    HyperFunnel<bool> successFunnel;
    HyperFunnel<bool> nodeNotFoundFunnel;

    HyperGate<bool> coupleGateA; // Used to gate the couple signal on a node not being found
    HyperGate<bool> coupleGateB; // Used to gate the couple signal on an inlet or outlet not being found
    Reinterpreter<bool, unsigned int> coupleReinterpreter; // Used to convert the couple signal to an unsigned int
};