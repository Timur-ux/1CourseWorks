from random import randint

with open('input.txt', 'w') as file:
    for i in range(1, 26):
        file.write(f'Item{randint(1, 999)} {i}\n')


