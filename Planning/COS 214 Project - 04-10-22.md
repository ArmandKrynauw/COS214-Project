# COS 214 Project - 04/10/22

# War Engine
Basic war engine to model a war.
```c++
while (war in progress) {
	// Update values for theatres in the war
	country1.makeDecisions();
	country2.makeDecisions();

	battle();

	// After each turn give user a summary of battles which occurred
	displayResults();
	turn++;
}

makeDecisions() {
	// Income Phase
	displayIncomeAndResources();

	// Production Phase
	// Transport units to theatres
	buyUnits();

	// Battle Phase
	for (each theatre) {
		pickStrategy();
	}
}

battle() {
	// Compare strategies for theatres and apply modifiers
	// Kill troops, take over regions, and update state of war
}
```

# Components of War

### 5.2.1 - Theatres
Regions where the war between countries or alliances will take place. The region
states are binary. Either a country or alliance has control of a region or they
don't. If a country or alliance have captured all the regions then the war ends.
At start of game/simulation majority of theatres will be uncontrolled. Each
country or alliance of countries will have a *home* region.

### 5.2.2 - Transportation
Countries will be able to transport units, troops, services from their base/home
region to specific regions in which warfare has to take place in. Transport can
also occur between regions. Transport can be sabotaged or attacked while in
progress. This can be modelled by reducing the amount of units, troops
or services in transport by a specific percentage.

### 5.2.3 - Entities
Model different types of units for land, sea, and air. That is, light, medium
and heavy. Units can be sent to various regions or battle fields to partake in
the war. Entities can have different states. For example, in transport,
stationed, fighting, injured and dead. Countries or groups of countries can have
and army of battalions and each battalion is made up of units and troops.

Specification also mentions medics, refugees, citizens and there different
states like unlisted, fighting, or returned, etc. It has not really been
discussed how this can be modelled.

### 5.2.4 - Phases of War
- War Phases
Implement some sort of escalation strategy. War state can be escalated as the
war progresses. Early, middle, and late stages of war. Can adjust economies of
countries involved accordingly. Can also implement more specific states such as
a seize fire between countries.
- Turn Phases
Income, production and battle phase, cycle through these phases every round.
Income phase handles the income and resources after a turn has taken place and
before the next turn starts. Production phase handles the acquisition of units
and troops to send to various regions or battle fields. Lastly, Battle phase
handles the actual battles taking place between countries in a region. The
Battle phase has multiple strategies which a country can pick from. For example,
plan, attack, and counter.

### 5.2.5 - Changes to War Engine
Countries will be able to join or leave alliances as the war progresses.
Countries will also be change sides or retreat from the war completely.
Countries or group of countries will be able build and develop a small tech tree
of sorts. This will enable countries to spend a portion of their income in order
to research various skills. These skills will add additional strength to
countries as war progresses.

# 5.3 - War Simulations
Current plan is to model the war as a turned base *game*. Snapshots can be taken
of the various turns in a war. If needed snapshots can also be taken of the
phases inside of every turn. This will allow us to *write* or play simulations.
Theses snapshots can be parsed as structured JSON data to be stored as full
simulations and individual snapshots can used by the TUI to easily represent the
data to the user. 

# GUI/TUI
Want to implement a user interface in order showcase and interact with war
simulations more intuitively. Every war simulation will have a vast amount of
various aspects which will easily get cluttered if console output alone is used.
Want to keep it simple, but as usable as possible. Need to be able to easily
navigate through and adjust war simulations as necessary in design mode. For
example, skip between rounds and adjust country armies.
![Example](Pre-Initial%20TUI%20Example.png)


# Potential Patterns
- `Template Method` - Units can have template methods attack/defend. Each unit
  implements their own primitive operations for attack/defend. (5.2.3)

- `Abstract Factory` - Creation of of the different battle units. Three
  categories. Light, medium, heavy. Will correspond to each of the three
  different units of each type. e.g. Land unit factory method for the Heavy
  factory will generate a Tank. (5.2.3)

- `Factory` - Creation of different theatres regions. (5.2.1)

- `Prototype` -  Make clones of entities, regions, etc.

- `Strategy` - Each country can make use of a list of different strategies to use
  in battle. These are strategies like, Plan, Attack, Counter. (5.2.4)

- `State` - Can be used to model the different battle phases. Can also be used to model the states of the units and troops. (5.2.3)(5.2.4)

- `Composite` - Model the armies and battalions of each country. For example,
  Armies and battalions are composites where troops and units are leafs. (5.2.3)
  Model alliances between countries. (5.2.5)

- `Memento` - Store snapshots for the the war simulations. (5.3)

- `Observer` - Can probably be used somewhere else. However, first thing that came to mind was to use it with the GUI. The user interface has to notify the war engine that changes was made by the user.

- `Singleton` - There should only ever be one war engine in existence.