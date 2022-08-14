# mario.py
# by: Charles Mitche

# In this homework assignment, we were aked to create a program that would print out
# half of a pyramid. We did the same assignment using C, but they wanted us to make
# it into a python program as well

from cs50 import get_int

# gets input from user that will be used to give the hight of the pyramid
height = get_int("Height: ")

# continously asks the user for height input if height does not meet conditions
while (height < 1) or (height > 8):
    height = get_int("Height: ")

# his loop prints out the rows, taking in height as a parameter to make sure the height equals number of rows
for i in range(height):

    # this loop prints out the spaces needed to allign the pyramid to the right and decreases by 1 as the row goes down. it's the opposite of the next loop
    for j in range(height - 1, i, -1):
        print(" ", end="")

    # this loop prints out the hashes and increases the number of hashes by 1 as the row goes down. it's the opposite of the loop above
    for k in range(i + 1):
        print("#", end="")
    print("")
