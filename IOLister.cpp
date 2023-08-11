#include "IOLister.h"

IOLister::IOLister(){
    addInlet(&circuitIn);
    addInlet(&nodeNameIn);
    addOutlet(&inletOut);
    addOutlet(&outletOut);
    setNodeName("IOLister");

    addNode(&accessor, "accessor");
    addNode(&extractor, "extractor");

    circuitIn.plug(&accessor.circuitIn);
    nodeNameIn.plug(&accessor.nodeNameIn);
    accessor.nodeOut.plug(&extractor.nodeIn);
    extractor.inletsOut.plug(&inletOut);
    extractor.outletsOut.plug(&outletOut);
}