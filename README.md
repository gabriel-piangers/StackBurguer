# Dado Burger

Dado Burger is a card-based burger restaurant game developed as the final project for the **INF01203 - Data Structures** course (2026/2), under Professor Dennis Giovani Balreira, at the Federal University of Rio Grande do Sul (UFRGS).

The project is written in C++ using [raylib](https://www.raylib.com/) and demonstrates how several data structures can solve different problems in a real-time graphical game. It implements the course structures directly instead of relying on standard-library containers such as `std::queue` or `std::map`.

## How to Play

1. Open **New Game** from the main menu.
2. Drag ingredient cards from the shop on both sides of the table onto the card table.
3. Prepare ingredients:
   - Stack raw meat, bacon, or egg cards on a grill card.
   - Stack tomato or onion cards on a cutting board card.
   - Cooking and cutting require real time.
4. Build a burger by dragging a card or an entire stack onto another stack.
5. To remove only part of a stack, pick up a card from the middle. The selected card and everything above it will be picked up together.
6. Drag the finished stack onto a customer. The delivery is valid only when the stack exactly matches the customer's recipe and contains no spoiled ingredients.
7. Serve all nine customers before the match ends. Each successful delivery adds to your score based on the customer's difficulty.

Customers begin with a happy expression, become normal and then angry as their patience decreases, and leave without payment if they wait too long.

### Controls and Features

- **Left mouse button:** drag cards, stacks, shop items, and UI buttons.
- **Escape:** pause the game during a match.
- **Right mouse button:** debug information is available for a hovered card.
- **Shop:** 13 ingredients are available; the shop is on both sides of the table.
- **Preparation stations:** two grills and one cutting board are available at the start.
- **History:** finished matches are appended to `data/historico.txt` and can be sorted by name or score in both directions.
- **Recipes:** customers display their required ingredients beside them.
- **Spoilage:** cooked or prepared perishable ingredients can become rotten and invalidate a delivery.
- **Progression:** the nine customers are ordered by increasing difficulty: 3 easy, 3 medium, 2 hard, and 1 very hard.

## Data Structures

| Structure | Implementation | Purpose |
| --- | --- | --- |
| Dynamic vector | `dynamic_vector.h` | Stores the history, heap elements, shop items, and pop-ups. Capacity doubles when full and shrinks when usage falls below half of the capacity. |
| AVL tree | `avl.h`, `avl.cpp` | Stores and searches recipes by calculated difficulty. Supports insertions, balanced rotations, closest-value lookup, height, and metrics. |
| Hash table | `hash_table.h` | Acts as a cache for AVL lookups and maps card IDs to nodes in the card-order list. Uses separate chaining and automatically grows and rehashes as needed. |
| Singly linked list | `recipe.h`, `recipe.cpp` | Represents a customer's recipe as a bottom-to-top sequence of prepared ingredients. |
| Doubly linked stack | `cards.h`, `cards.cpp` | Represents a burger as a stack of cards. It supports efficient insertion and removal of a card plus everything above it. |
| Card z-order list + hash table | `CardList` in `cards.h` | Combines a doubly linked list with a hash table so the top card or stack can be moved to the front of the drawing and interaction order quickly. |
| Queue | `queue.h` | Manages waiting customers with constant-time insertion and removal. |
| Minimum heap | `heap.h`, `event_system.h`, `event_system.cpp` | Stores timed events such as customer arrivals and ingredient spoilage by absolute event time. |
| Quicksort | `DynamicVector::sort` | Sorts history records in place by name or score, with median-of-three pivot selection and an optional secondary sorting criterion. |

The card stack is unusual for a stack implementation: it is a doubly linked chain instead of an array-based stack because a player can pick a card in the middle and remove the entire sub-stack above it.

### How `CardList` manages card overlap

`CardList` is separate from the doubly linked structure that represents one burger stack. It manages the visual and interaction order of **cards currently on the table**:

- Every displayed card is wrapped in a `CardNode` containing `next` and `prev` pointers.
- The doubly linked list runs from `first` (furthest back) to `last` (front/top). It is therefore the z-order used to decide which cards are drawn and clicked over which others.
- `CardList::insert` creates a node and appends it to `last`.
- A `CardNode*` is stored in a `HashTable<int, CardNode*>` using the card's unique ID. The hash table lets the game find a card node directly instead of traversing the whole list.
- `CardList::remove(id)` uses that hash lookup to find the node, updates its neighbours' `next` and `prev` pointers, updates `first` or `last` when necessary, and removes the hash entry.
- `CardList::insertAfter(card, previousId)` inserts a card just after a known card. When it is dropped without an overlap target, the card is appended again and becomes the top card.

A card has two kinds of pointers: `Card::next`/`Card::prev` form the burger stack, while `CardNode::next`/`CardNode::prev` form the table's z-order list. Both refer to the same `Card` object, but they serve different purposes.

When a player picks up a card from the middle of a burger, `Card::pickup` separates the burger stack at that point. The code removes each card in the selected sub-stack from `CardList` in turn, using its ID. When the sub-stack is placed:

- A valid drop onto another stack calls `Card::insert`, which attaches the sub-stack to the target and updates the size of every affected stack entry.
- A valid drop on a customer compares the stack against the recipe and rejects it if the ingredients or preparation state do not match exactly.
- An invalid drop rewires the burger stack and z-order list back to their previous positions.
- Drawing traverses z-order from front to back so that the top card is drawn last. Mouse updates traverse it backward so that the visually topmost card receives the click first.

Finding and removing or inserting a node is O(1) when the hash lookup is successful and the neighbour node is known. Moving a stack of `k` cards costs O(k), while it does not require an O(n) search through every card on the table.

## Compile and Run

The executable must be run from the project root so that it can find `assets/`, `data/`, and the supplied data files.

> **raylib is not bundled in this repository.** The `raylib/` directory is ignored by Git and must be downloaded or installed separately from the [official raylib website](https://www.raylib.com/) or the [raylib GitHub repository](https://github.com/raysan5/raylib).

### Linux

#### Dependencies

1. Download or build raylib 5.0 or newer for desktop Linux using the instructions at [raylib.com](https://www.raylib.com/).
2. Install the C++ compiler and system development packages. On Debian/Ubuntu-based distributions:

```bash
sudo apt update
sudo apt install build-essential libx11-dev libgl1-mesa-dev libglu1-mesa-dev
```

3. Make sure `libraylib.a` or `libraylib.so`, and the raylib headers, are available to the compiler. The project does not include or download raylib automatically.

If raylib was built locally, one common layout is `raylib/src/libraylib.a`. In that case, the compiler may need to reference it directly instead of using `-lraylib`.

#### Build

After raylib is installed system-wide, run this from the project root:

```bash
bash compile.sh
```

The script compiles the files in `src/` and creates `game`. If raylib is installed in a custom location, update the include and library paths in `compile.sh` before building.

If raylib was built locally at `raylib/src/libraylib.a`, you can compile from the project root with:

```bash
g++ src/*.cpp -o game -I./src -I./raylib/src ./raylib/src/libraylib.a -lm -lpthread -ldl -lrt -lX11
```

For a system-wide raylib installation, the equivalent command is:

```bash
g++ src/*.cpp -o game -I./src -lraylib -lm -lpthread -ldl -lrt -lX11
```

#### Run

```bash
./game
```

The game can use custom input files:

```bash
./game data/pedidos.txt data/historico.txt
```

### Windows

The supplied batch script expects raylib and w64devkit to be available at:

```text
C:\raylib\raylib
C:\raylib\w64devkit\bin
```

1. Download the Windows raylib package or source from [raylib.com](https://www.raylib.com/) and place the raylib directory at `C:\raylib\raylib` if you use the supplied script unchanged.
2. Install w64devkit and place it at `C:\raylib\w64devkit`.
3. Open **Command Prompt** in the project root.
4. Run:

```bat
compile.bat
```

The script creates `game.exe`.

Alternatively, open `main.code-workspace` in VS Code and use the configured build tasks:

- **build debug**
- **build release**

Then run:

```bat
game.exe
```

Custom input files can be supplied as arguments:

```bat
game.exe data\pedidos.txt data\historico.txt
```

If the windowed executable does not find an asset or data file, return to the project root before launching it. The default paths are relative to the current working directory.

## Metrics

The application tracks AVL load and search metrics, hash-table hits/misses/collisions, history loading, and sorting information. Metrics are saved when the program exits to:

```text
data/metrics.log
```

They are not currently displayed inside the graphical interface.

## Command-Line Arguments

| Argument | Default | Description |
| --- | --- | --- |
| 1: `ordersPath` | `data/pedidos.txt` | Recipe data loaded into the AVL tree before the menu opens. |
| 2: `historyPath` | `data/historico.txt` | Score history loaded before the menu opens and updated after a match. |

Example:

```bash
./game /path/to/pedidos.txt /path/to/historico.txt
```

## Known Issues and Limitations

- The **How to Play** menu screen is not implemented; controls and gameplay instructions are described in this README.
- The game has no implemented currency or coin system, although ingredient rarity is also represented as a price in the source data.
- The game is designed for desktop-sized windows and may not scale correctly on small or unusually shaped screens.
- Loading a large `pedidos.txt` can take noticeable time because the AVL is populated and each difficulty is calculated and randomized during initialization.
- The metrics report is written only to `data/metrics.log` and is not shown in the UI.
- The hash cache may have a low hit rate with randomized real-valued difficulties, as there is no guaranteed repeat of a discretized cache key during one session.