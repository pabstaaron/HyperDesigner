#pragma once

#include "HyperCore.h"
#include "HyperStandard.h"
#include "HyperCompiler.h"

using namespace std;

/**
 * @brief A HyperCircuit for designing HyperCircuits. 
 */
class HyperDesigner : public HyperExecutable {
private:
    // User IO
    ConsoleWell consoleIn;
    ConsoleDrain<string> consoleOut;

    // Circuit IO
};