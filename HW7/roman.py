#!/usr/bin/python3

import sys

#Arrays to hold roman equivalents of arabic numerals
ones = ("", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX")
tens = ("", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC")
hundreds = ("", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM")
thousands = ("", "M", "MM", "MMM")


def decToRoman(number):
    """
        decToRoman(number)

        Takes a number in arabic numerals and returns a conversion to roman numerals, or the string "Error" if the number is out of range

        Arguments:
            number: An integer to represent in roman numerals
    """
    #Deal with numbers out of range
    if number <= 0 or number > 3999:
        return "Error"
    #Convert each place to an index in the respective array for each number place
    thouPlace = number // 1000
    hunPlace = (number % 1000) // 100
    tenPlace = (number % 100) // 10
    onePlace = (number % 10)
    #Construct and return the string
    return thousands[thouPlace] + hundreds[hunPlace] + tens[tenPlace] + ones[onePlace]

for i in sys.argv[1:]:
    print(i + " is " + decToRoman(int(i)))
