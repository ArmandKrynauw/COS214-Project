#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include <string>

class WarEngine;

class TUI;

class ControlUnit {
private:
    WarEngine *warEngine;
    TUI *tui;

public:
    ControlUnit(WarEngine *warEngine, TUI *tui);

    std::string getName();
};

#endif  // CONTROLUNIT_H