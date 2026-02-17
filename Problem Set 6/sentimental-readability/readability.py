from cs50 import get_string

input = get_string("Text: ")
inputUpper = input.upper()

words = 0
sentences = 0
letters = 0

# Para cada letra em inputUpper
for i in inputUpper:
    # Se for espaço:
    if i == " ":
        words+=1
    # Se for terminador de frase:
    elif i in [".", "!", "?"]:
        sentences+=1
    # Se for alfabético:
    elif i.isalpha():
        letters+=1
words+=1

# Calcula o grade
averageL = (letters/words) * 100
averageS = (sentences/words) * 100
index = round(0.0588 * averageL - 0.296 * averageS - 15.8)

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
