# Sierpinski-generator
This is a cpp program written in SDL2. It generates a fractal, the Sierpinski triangle. It uses a simple algorithm that relies on chaos theory and geometric attractors. From more info and inspiration I suggest you to watch this video from Numberphile (https://www.youtube.com/watch?v=kbKtFN71Lfs).

# Algorith step by step
 1) Draw three random points on the screen, they will be the vertices of a triangle.
 2) Choose a random point, the pivot. I have chosen, to make things easier, the middle point of the screen
 3) Now roll a three-face dice (generate a random int from the interval [1,3])
 4) If the result is 1 move the pivot half way to the first vertex, if it's 2 just move it half way to the second, if it's 3 just           move it to the third.
 5) Draw the new position of the pivot on the screen
 6) Iterate steps from 3 to 5 at least 10000 times
A fractal will appear on the screen. How amazing is that? :)

![Alt text](/home/omykhron/Pictures/Screenshot_20180909_125124.png?raw=true "Sierpinski triangle")
