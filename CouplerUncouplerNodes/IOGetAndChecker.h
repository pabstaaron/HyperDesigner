#pragma once

#include "HyperCore.h"
#include "HyperStandard.h"

class IOGetAndChecker : public HyperCircuit {
private:
    InletAccessor inletAccessor;
    OutletAccessor outletAccessor;

    Noter<bool> inletNotFoundInverter;
    Noter<bool> outletNotFoundInverter;

    Ander<bool> inletNotFoundAnd;
    Transitizer inletGateResetter;
    HyperGate<IHyperInlet*> inletGate;
    Transitizer onInletNotFound;

    Ander<bool> outletNotFoundAnd;
    Transitizer outletGateResetter;
    HyperGate<IHyperOutlet*> outletGate;
    Transitizer onOutletNotFound;

    Ander<bool> inletAndOutletFoundAnd;
    Transitizer onInletAndOutletFound;

    SyncGate<bool> coupleGate;

public:
    // Inlets
    HyperRepeater<HyperNode*> inletsNodeIn;
    HyperRepeater<string> inletsNameIn;

    HyperRepeater<HyperNode*> outletsNodeIn;
    HyperRepeater<string> outletsNameIn;

    HyperRepeater<bool> coupleIn;

    // Outlets
    HyperRepeater<IHyperInlet*> inletOut;
    HyperRepeater<IHyperOutlet*> outletOut;
    HyperRepeater<bool> coupleOut;

    HyperRepeater<bool> inletNotFound;
    HyperRepeater<bool> outletNotFound;

    IOGetAndChecker() : inletsNodeIn("inletsNodeIn"), 
                        inletsNameIn("inletsNameIn"),
                        outletsNodeIn("outletsNodeIn"), 
                        outletsNameIn("outletsNameIn"),
                        coupleIn("coupleIn"),
                        inletOut("inletOut"), 
                        outletOut("outletOut"), 
                        coupleOut("coupleOut"),
                        inletNotFound("inletNotFound"), 
                        outletNotFound("outletNotFound") {
        setNodeName("IOGetAndChecker");

        // Add Inlets
        addInlet(&inletsNodeIn);
        addInlet(&inletsNameIn);
        addInlet(&outletsNodeIn);
        addInlet(&outletsNameIn);
        addInlet(&coupleIn);

        // Add Outlets
        addOutlet(&inletOut);
        addOutlet(&outletOut);
        addOutlet(&coupleOut);

        addOutlet(&inletNotFound);
        addOutlet(&outletNotFound);

        // Add nodes
        addNode(&inletAccessor, "inletAccessor");
        addNode(&outletAccessor, "outletAccessor");
        addNode(&inletNotFoundInverter, "inletNotFoundInverter");
        addNode(&outletNotFoundInverter, "outletNotFoundInverter");
        addNode(&inletNotFoundAnd, "inletNotFoundAnd");
        addNode(&outletNotFoundAnd, "outletNotFoundAnd");
        addNode(&inletGateResetter, "inletGateResetter");
        addNode(&outletGateResetter, "outletGateResetter");
        addNode(&inletGate, "inletGate");
        addNode(&outletGate, "outletGate");
        addNode(&onInletNotFound, "onInletNotFound");
        addNode(&onOutletNotFound, "onOutletNotFound");
        addNode(&inletAndOutletFoundAnd, "inletAndOutletFoundAnd");
        addNode(&onInletAndOutletFound, "onInletAndOutletFound");
        addNode(&coupleGate, "coupleGate");

        // Wire up
        inletsNodeIn.plug(&inletAccessor.nodeIn);
        inletsNameIn.plug(&inletAccessor.inletNameIn);

        outletsNodeIn.plug(&outletAccessor.nodeIn);
        outletsNameIn.plug(&outletAccessor.outletNameIn);

        inletAccessor.notFound.plug(&inletNotFoundInverter.inlet);
        outletAccessor.notFound.plug(&outletNotFoundInverter.inlet);

        inletNotFoundInverter.outlet.plug(inletNotFoundAnd.inlets.spawnBack());
        outletAccessor.notFound.plug(inletNotFoundAnd.inlets.spawnBack());
        inletNotFoundAnd.outlet.plug(&inletGateResetter.booleanIn);
        inletGateResetter.transientOut.plug(&inletGate.reset);

        outletNotFoundInverter.outlet.plug(outletNotFoundAnd.inlets.spawnBack());
        inletAccessor.notFound.plug(outletNotFoundAnd.inlets.spawnBack());
        outletNotFoundAnd.outlet.plug(&outletGateResetter.booleanIn);
        outletGateResetter.transientOut.plug(&outletGate.reset);

        inletAccessor.inletOut.plug(&inletGate.inlet);
        outletAccessor.outletOut.plug(&outletGate.inlet);

        inletNotFoundInverter.outlet.plug(inletAndOutletFoundAnd.inlets.spawnBack());
        outletNotFoundInverter.outlet.plug(inletAndOutletFoundAnd.inlets.spawnBack());
        inletAndOutletFoundAnd.outlet.plug(&onInletAndOutletFound.booleanIn);
        inletAndOutletFoundAnd.outlet.plug(&coupleGate.allow);

        onInletAndOutletFound.transientOut.plug(&inletGate.trigger);
        onInletAndOutletFound.transientOut.plug(&outletGate.trigger);

        coupleIn.plug(&coupleGate.inlet);

        inletGate.outlet.plug(&inletOut);
        outletGate.outlet.plug(&outletOut);
    }
};