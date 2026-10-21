# \# Wayfarer's Oath

# 

# \*\*A 2D fantasy RPG prototype built from the ground up with C++20 and SFML.\*\*

# 

# Wayfarer's Oath is an ongoing personal game development project inspired by classic \*Final Fantasy\* games and tabletop RPGs such as \*Dungeons \& Dragons\*. The goal is to bring together character creation, exploration, resource gathering, inventory management, crafting, saving/loading, and eventually turn-based combat in one cohesive game.

# 

# I'm developing the game without a full game engine to gain hands-on experience designing, debugging, testing, and integrating gameplay systems in C++.

# 

# > \*\*Project status:\*\* Active development / prototype. Some systems are complete as standalone logic but are not yet integrated into the playable game.

# 

# \## Gameplay preview

# 

# <!-- Add your screenshots or gameplay GIFs here. Example:

# !\[Forest exploration](docs/images/forest-exploration.png)

# !\[Inventory](docs/images/inventory.png)

# !\[Crafting](docs/images/crafting.png)

# \-->

# 

# \*Gameplay screenshots and footage coming soon.\*

# 

# \## Features

# 

# | System | Current functionality | Status |

# | --- | --- | --- |

# | \*\*Character creation\*\* | Name, race, class, six attributes, attribute allocation and validation | Implemented |

# | \*\*Exploration\*\* | Top-down movement, camera, collisions, forest generation and resource gathering | Implemented |

# | \*\*Inventory\*\* | Material quantities, selection, scrolling, item details and sprite-sheet icons | Implemented |

# | \*\*Crafting\*\* | Recipe browsing, material requirements and craftability checks | UI refinement / crafting interaction in progress |

# | \*\*Save / load\*\* | JSON serialization for character and game-state data, including inventory and world persistence | Implemented; ongoing improvements |

# | \*\*Turn-based combat\*\* | Initiative, turn ordering and combat actions | Core system developed; gameplay integration planned |

# | \*\*Audio and menus\*\* | Dedicated screens, keyboard navigation, background music and UI sounds | Implemented; ongoing polish |

# 

# \### Character creation

# 

# Players can create a character by selecting a race and class, entering a name, and allocating attributes. Race and class definitions are read from external data files, making them easier to extend without hardcoding every option.

# 

# \### Exploration and gathering

# 

# The playable world includes a procedurally generated forest with trees, rocks and bushes. Players can move through the environment, collide with obstacles, and gather nearby resources. Environmental objects are rendered with vertical layering to help convey depth in a top-down view.

# 

# The forest uses deterministic generation, which supports reconstructing the world when loading saved progress.

# 

# \### Inventory

# 

# Collected materials are stored with quantities rather than duplicated as separate entries. The inventory screen supports scrolling, item selection, material details, and icons selected from a shared sprite sheet using material-specific row and column values.

# 

# \### Crafting

# 

# The crafting interface lists recipes and shows the materials and quantities needed for the selected recipe. Players can inspect recipes even when they lack the necessary materials. The underlying crafting logic checks the inventory to determine whether requirements are met.

# 

# Visual feedback for uncraftable recipes and the final crafting interaction are being refined.

# 

# \### Save and load

# 

# The game uses JSON to preserve progress, including character information, inventory data, player position, and gathered resources. Gathered world objects are tracked by ID so the forest can be regenerated and previously collected objects removed during loading.

# 

# \### Combat direction

# 

# The project includes an existing turn-based combat system with initiative and combat actions. The plan is to integrate it into the SFML game while keeping a classic \*Final Fantasy\*-inspired battle feel and drawing on D\&D-style mechanics for the underlying calculations.

# 

# \## Technology stack

# 

# | Technology | Usage |

# | --- | --- |

# | \*\*C++20\*\* | Gameplay and systems programming |

# | \*\*SFML 2.6.2\*\* | Graphics, input, windowing and audio |

# | \*\*CMake\*\* | Build configuration |

# | \*\*Visual Studio\*\* | Development and debugging |

# | \*\*nlohmann/json\*\* | JSON save files |

# | \*\*Catch2\*\* | Unit testing |

# | \*\*CSV\*\* | External gameplay data |

# | \*\*Git / GitHub\*\* | Version control |

# 

# \## Getting started

# 

# \### Prerequisites

# 

# \- A C++20-compatible compiler

# \- CMake 3.20 or newer

# \- SFML 2.6.2

# \- Visual Studio or another compatible CMake development environment

# \- Any additional dependencies referenced by the project's CMake configuration

# 

# The project is currently developed primarily on \*\*Windows\*\*.

# 

# \### Build from source

# 

# 1\. Clone the repository:

# 

# &#x20;  ```bash

# &#x20;  git clone https://github.com/AbakaFrostscale/RPG-System.git

# &#x20;  ```

# 

# 2\. Open the repository in Visual Studio as a CMake project.

# 3\. Configure the project and ensure SFML and other required dependencies are available.

# 4\. Build the `RPGGameSystem` target.

# 5\. Run the executable with the required `Assets` and `DataBases` resources available in its working directory.

# 

# > \*\*Note:\*\* This is a development project rather than a packaged release. Dependency configuration and runtime resource paths may need adjustment on another machine.

# 

# \## How to play

# 

# 1\. Launch the game and choose \*\*New Game\*\* from the main menu.

# 2\. Create your character by selecting a race, class and attributes.

# 3\. Explore the forest and gather materials from nearby objects.

# 4\. Open the \*\*Inventory\*\* screen to inspect your resources.

# 5\. Open the \*\*Crafting\*\* screen to browse recipes and check their requirements.

# 6\. Use the save/load functionality to preserve and restore progress.

# 

# \*\*Controls:\*\* Keyboard controls and shortcuts will be documented here once the input mappings are finalised.

# 

# \## Project structure

# 

# The project separates core gameplay logic from player-facing screens.

# 

# | Area | Responsibility |

# | --- | --- |

# | `Character` | Character data and statistics |

# | `Creation` | Character creation logic |

# | `Combat` | Turn-based combat logic |

# | `Inventory` | Materials, inventory and crafting logic |

# | `Core` | Shared types, utilities and data loading |

# | `Save \& Load` | Serialization and restoration of game state |

# | UI screens | Main menu, character creation, gameplay, inventory and crafting |

# 

# External data files define information such as materials, races and classes, while JSON stores saved game state.

# 

# \## What I'm learning

# 

# This project is as much about \*\*integrating systems\*\* as it is about implementing individual features. Some of the most useful engineering challenges have included:

# 

# \- Managing character data consistently across multiple screens.

# \- Separating gameplay logic from UI rendering.

# \- Designing save/load data structures and validating external data.

# \- Reconstructing procedural world state from saved information.

# \- Keeping data-driven item definitions separate from inventory quantities.

# \- Debugging CMake resource copying and runtime asset paths.

# 

# \## Roadmap

# 

# \- \[x] Character creation

# \- \[x] Top-down exploration and forest generation

# \- \[x] Resource gathering and inventory management

# \- \[x] Inventory UI and item sprite-sheet icons

# \- \[x] Crafting recipe browser and requirement checking

# \- \[x] JSON save/load foundation

# \- \[x] Standalone turn-based combat system

# \- \[ ] Finalise crafting interactions and uncraftable-recipe feedback

# \- \[ ] Integrate combat into the playable game

# \- \[ ] Add enemies and combat encounters

# \- \[ ] Expand equipment, items and world resources

# \- \[ ] Design character progression and levelling

# \- \[ ] Continue UI, audio and gameplay polish

# 

# \*The roadmap may change as development progresses.\*

# 

# \## About the developer

# 

# I'm \*\*Kaden Mann\*\*, an aspiring gameplay and systems programmer based in South Africa. I'm building Wayfarer's Oath to develop my C++ skills and demonstrate how I approach game systems, debugging and software architecture.

# 

# \- \[GitHub](https://github.com/AbakaFrostscale)

# \- \[LinkedIn](https://www.linkedin.com/in/kadenmann5)

# 

# \## Credits and licences

# 

# Wayfarer's Oath is inspired by classic role-playing games, including \*Final Fantasy\* and \*Dungeons \& Dragons\*.

# 

# Third-party artwork, music, fonts and other assets belong to their respective creators and remain subject to their applicable licences. \*\*Specific asset credits and licences should be added before public distribution.\*\*

# 

# <!-- Add a LICENSE file and link it here if you decide to license the project's source code. -->

# 
