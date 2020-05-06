# langtons-ant
Langton's ant is a kind of cellular automata invented by Chris Langton. It is similar to the Game of Life by John Horton Conway.
It follows a hypothetical "ant" that adheres to a set of directional rules. Eventually, the ant produces interesting emergent (symmetrical) properties.
In a way, it is a complex system born from just a few simple rules; and as it turns out, Langton's ant is a 2D universal Turing machine.  

The classical ruleset is RL, two simple rules with cyclic behavior, represented by colors (say, white [0] and black [1]).  
The rules of RL, therefore, are as follows:  
* R: On white [0] turn the ant R [clockwise 90 deg], flip color to black [1], march forwards.  
* L: On black [1] turn the ant L [counter-clockwise 90 deg], flip color to white [0], march forwards.  

In the classical ruleset, the ant begins building a "bridge" around step 10,000. It will continue building the bridge seemingly forever.
The simulator is currently extended to 138 colors, allowing up to 138 rules. Try different combinations and discover something amazing!

## Building
SFML 2.5.1 and TGUI 0.8 libraries required to build. >GCC 4.9 Required. Run *make* in source directory to build.
