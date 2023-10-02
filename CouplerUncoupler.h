#pragma once

#include "HyperCore.h"
#include "HyperStandard.h"

#include "CouplerUncouplerNodes/NodeGetAndChecker.h"
#include "CouplerUncouplerNodes/IOGetAndChecker.h"
#include "CouplerUncouplerNodes/CoupleButterfly.h"

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
    HyperRepeater<bool> success;        // Transient indicating success
    HyperRepeater<bool> nodeNotFound;   // Transient indicating that a node was not found
    HyperRepeater<bool> inletNotFound;  // Transient indicating that an inlet was not found
    HyperRepeater<bool> outletNotFound; // Transient indicating that an outlet was not found

    CouplerUncoupler();

private:
    NodeGetAndChecker nodeGetAndChecker;
    IOGetAndChecker ioGetAndChecker;
    CoupleButterfly coupleButterfly;
};