# Blackjack: Road to the VIP Table

A C++ console Blackjack game built around the concepts and code style in the supplied C++ lab notes.

## Features

- Three progression levels: Beginner, High Roller and VIP.
- Increasing minimum bets, chip targets and level-completion rewards.
- Player betting and a chip balance.
- Hit, Stand and Double Down.
- Dealer shows the upcard, keeps the hole card hidden until the reveal, and draws until 17.
- Blackjack hand totals, including Aces counting as 1 or 11.
- Natural Blackjack pays 3:2 (rounded down to a whole chip for odd bets).
- Win, loss, push and Blackjack tracking.
- Current and best win streak, rounds played and win rate.
- Automatic save after each completed round, plus a save-and-return option.
- Load saved progress from `blackjack_save.txt`.
- Factory pattern for creating each level.
- Abstract `Participant` base class with `Player` and `Dealer` implementations.
- Input validation for menu choices, bets and gameplay decisions.

## Build

The project uses basic C++11 features. Compile all `.cpp` files together.

### g++

```bash
g++ -std=c++11 -Wall -Wextra -pedantic main.cpp Card.cpp Deck.cpp Hand.cpp Participant.cpp Player.cpp Dealer.cpp Level.cpp Levels.cpp LevelFactory.cpp SaveManager.cpp BlackjackGame.cpp -o blackjack
```

Run:

```bash
./blackjack
```

On Windows, the output executable can be named `blackjack.exe` instead.

### Visual Studio

Create a C++ Console App, add all the `.cpp` files to the project, and keep the `.h` files in the same project folder. Build and run the project using Visual Studio.

## Save file

The game writes `blackjack_save.txt` into the program's working directory. It stores:

1. Chip balance and current level
2. Wins, losses, pushes and natural Blackjacks
3. Total rounds, current win streak and best win streak

Progress is automatically saved after each round. The save manager also accepts the four-number save format from the first project version. A completed campaign is stored as level 4 so the champion result can be loaded later.

## Project files

Each class is split into a header (`.h`) and implementation (`.cpp`) file, following the separate-compilation examples in the course notes. `main.cpp` contains the title menu and starts the game.

## Class overview

- `Card`: one playing card and its console display.
- `Deck`: creates, shuffles and deals cards.
- `Hand`: stores cards and calculates totals, Aces, busts and natural Blackjacks.
- `Participant`: abstract base class shared by player and dealer.
- `Player`: accepts player input, places bets and updates chips.
- `Dealer`: follows the dealer's automatic turn rules.
- `Level`: abstract base class for casino levels.
- `BeginnerLevel`, `HighRollerLevel`, `VIPLevel`: concrete level classes.
- `LevelFactory`: creates a level based on its number.
- `SaveManager`: saves and loads progress using basic file streams.
- `BlackjackGame`: controls rounds, results, statistics and progression.

## OOP and design pattern mapping

- **Encapsulation:** class data is private/protected and accessed through methods.
- **Inheritance:** `Player` and `Dealer` inherit from `Participant`; the three level classes inherit from `Level`.
- **Abstraction:** `Participant` and `Level` contain pure virtual functions and cannot be instantiated directly.
- **Polymorphism:** the game calls `TakeTurn()` through `Participant*` pointers; the player's and dealer's overrides run.
- **Factory pattern:** `LevelFactory::CreateLevel()` creates the correct concrete level and returns it as a `Level*`.
- **Composition:** the game contains its player, dealer, deck and save manager as member objects; hands contain cards by value.

## Rules and deliberate limits

- The game uses one 52-card deck, shuffled at the start of each round.
- The dealer stands on all 17 totals, including soft 17.
- A natural Blackjack is an Ace and a 10-value card in the first two cards, and pays 3:2.
- Double Down is available on the first two cards if the player's chip balance can cover the doubled bet. The player receives one card and then stands.
- A tie is a push. Splitting, insurance and surrender are not included in this coursework version.
- The game uses integer chips, so a 3:2 payout on an odd-numbered bet is rounded down to a whole chip.
