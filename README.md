# Sierpinski-generator
# This is a cpp programm in SDL2  that generates a fractal image
# The fractal generated is the famous Sierpinski Triangle
# The algorithm used is simple and based on chaos theory
# Just draw the three vertices of a triangle. Choose a random pivot point (I used the middle one).
# Roll a three-face dice (generate a random int in the interval ]0,3] )
# if the resul is 1 just move the pivot half way from the first vertex
# if the result is two move the pivot half way from the second vertex
# if the result is three move the pivot half way from the third vertex
# Iterate this process at least 10000 times and you'll have a fractal!
# how amazing is that?

