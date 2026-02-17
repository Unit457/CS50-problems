from cs50 import get_int
from sys import exit

# Pega card
card = get_int("Number: ")

# Pega a length de card
cardLength = len(str(card))

# Se a length não for nem 13, nem 15, nem 16:
if cardLength not in [13, 15, 16]:
    # Cartão inválido
    print("INVALID")
    exit(1)

# Agora vamos colocar cada dígito do cartão em uma array
# Porém, ao contrário, para enxergamos com mais facilidade quais números devem e não devem ser multiplicados
cardStr = str(card)
cardReverse = cardStr[::-1]

doubleChoice = False
checksum = 0

# Para cada número no cartão
for i in cardReverse:
    num = int(i)
    # Se deve ser duplicado:
    if doubleChoice:
        # Se for maior que nove (tiver dois dígitos)
        if num*2 > 9:
            # Subtrai 9 e adiciona na checksum (O número 13 adicionaria 4 a checksum. 13-9 = 4) 
            checksum+=num*2-9
        # se não tiver dois dígitos
        else:
            # Adiciona na checksum
            checksum+=num*2
        # O próximo dígito não deve ser duplicado
        doubleChoice = False
    else:
        # Adiciona na checksum
        checksum+=num
        # O próximo número deve ser duplicado
        doubleChoice = True

# Se o último dígito não for 0, é inválido
if checksum % 10 != 0:
    print("INVALID")
    exit(1)

# Se o tamanho do cartão for 13 e seu primeiro dígito for 4, é VISA
if cardLength == 13 and int(cardStr[0]) == 4:
    print("VISA")

# Se o tamanho do cartão for 15
elif cardLength == 15:
    # Se seu primeiro dígito for 3 e o segundo dígito for 4 ou 7, é AMEX
    if int(cardStr[0]) == 3 and int(cardStr[1]) in [4, 7]:
        print("AMEX")
    # Se não, é inválido
    else:
        print("INVALID")

# Se o tamanho do cartão for 16
elif cardLength == 16:
    # Se o primeiro dígito for 4, é VISA
    if int(cardStr[0]) == 4:
        print("VISA")
    # Se o primeiro dígito for 5 e o segundo dígito estiver entre 0 e 6, é MASTERCARD
    elif int(cardStr[0]) == 5 and int(cardStr[1]) in [1, 2, 3, 4, 5]:
        print("MASTERCARD")
    # Se não, é inválido
    else:
        print("INVALID")
