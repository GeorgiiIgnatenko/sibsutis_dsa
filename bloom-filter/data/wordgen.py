import random
import string

def generate_words(num_words, word_length):
    words = []
    for _ in range(num_words):
        word = ''.join(random.choices(string.ascii_lowercase, k=word_length))
        words.append(word)
    return words

def write_to_file(words, filename):
    with open(filename, 'w') as file:
        for word in words:
            file.write(word + '\n')

words = generate_words(5000000, 6)

write_to_file(words, 'out')
