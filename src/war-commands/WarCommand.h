#ifndef WARCOMMAND_H
#define WARCOMMAND_H

#include "../engine/WarEngine.h"
#include "../utilities/json.hpp"

/**
 * @brief War Command Hierarchy.
 *
 * This hierarchy is used by the War Socket / GUI to invoke specific commands on
 * the War Engine in order to change the state of the engine and the simulation
 * being run.
 */
class WarCommand {
   public:
    /**
     * Invokes specific commands on War Engine to change the state of the
     * current simulation being run.
     */
    virtual void execute() = 0;

    /**
     * Returns the description of the current command which can be used for
     * additional output or debugging purposes.
     */
    virtual std::string getDescription() = 0;

    /**
     * Returns the result of the previous command executed. Every command
     * executed on the War Engine will cause a state change in the engine.
     * The results of this change will be returned to be processed as seen
     * fit by the GUI.
     */
    nlohmann::json getResult() const;

    virtual ~WarCommand();

   protected:
    nlohmann::json result;
    WarCommand();
};

#endif  // WARCOMMAND_H