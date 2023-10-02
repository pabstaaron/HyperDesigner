#pragma once

#include "HyperCore.h"
#include "HyperStandard.h"

class CoupleButterfly : public HyperCircuit {
private:
    SyncDemuxer<IHyperInlet*> inletDemuxer;
    SyncDemuxer<IHyperOutlet*> outletDemuxer;

    Reinterpreter<bool, unsigned int> coupleReinterpreter; // Used to convert the couple signal to an unsigned int

    Coupler coupler;
    Uncoupler uncoupler;

    HyperFunnel<bool> successFunnel;

public:
    // Inlets
    HyperRepeater<IHyperInlet*> inletIn;
    HyperRepeater<IHyperOutlet*> outletIn;

    HyperRepeater<bool> coupleIn;

    // Outlets
    HyperRepeater<bool> successOut;

    // Wire up
    CoupleButterfly(){
        setNodeName("CoupleButterfly");

        addInlet(&inletIn);
        addInlet(&outletIn);
        addInlet(&coupleIn);

        addOutlet(&successOut);

        inletIn.plug(&inletDemuxer.inlet);
        outletIn.plug(&outletDemuxer.inlet);

        coupleIn.plug(&coupleReinterpreter.inlet);
        coupleReinterpreter.outlet.plug(&inletDemuxer.selectInlet);
        coupleReinterpreter.outlet.plug(&outletDemuxer.selectInlet);

        inletDemuxer.outlets.plugBack(&coupler.inletIn);
        inletDemuxer.outlets.plugBack(&uncoupler.inletIn);

        outletDemuxer.outlets.plugBack(&coupler.outletIn);
        outletDemuxer.outlets.plugBack(&uncoupler.outletIn);

        coupler.success.plug(successFunnel.inlets.spawnBack());
        uncoupler.success.plug(successFunnel.inlets.spawnBack());
    }
};