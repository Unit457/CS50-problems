from cs50 import get_int

height = get_int("Height: ")
while height < 1 or height > 8:
    height = get_int("Height: ")

currentHeight = 1
currentSpaces = height - 1
for i in range(height):
    print(" " * currentSpaces + "#" * currentHeight + "  " + "#" * currentHeight)
    currentHeight+=1
    currentSpaces-=1
