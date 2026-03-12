## Reflection

**1. What is the invariant structure of your game?**
The invariant structure is the main game loop managed by the `RunSession` class. It strictly follows a fixed sequence: 
dealing cards-> getting player input-> calculating the score->applying rewards or penalties->and opening the shop. 
This exact order repeats every round and never changes.

**2. What parts are mutable?**
The mutable parts are the specific mechanics and formulas inside the worker classes. For example, how the cards are randomized (`HandGenerator`), how poker hands are evaluated and scored (`ScoringSystem`), and how the money is calculated after a round (`RewardRule`). These rules can be modified without touching the main loop.

**3. If you wanted to add a new feature, which class would change?**
It depends on the feature, but the `RunSession` class will remain untouched. If I want to add a new poker hand combination or change the damage multiplier, I will only change the `ScoringSystem` class. If I want to add new items to buy, I will change the `ShopSystem` class. 

**4. If you changed the loop order, what would break?**
The game's logic and data flow would break. For example, if the system tries to calculate the score before the player inputs their cards, the damage will be zero. If the shop phase happens before the reward phase, the player will not be able to use the money they just earned from surviving the wave.