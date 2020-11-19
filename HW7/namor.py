#!/usr/bin/python3

import sys

#Dicts to hold roman equivalents of arabic numerals. I copied from roman.py, and decided not to reverse by hand. 
#Instead, we'll just reverse when it's time to iterate through the list
ones = {"":0, "I":1, "II":2, "III":3, "IV":4, "V":5, "VI":6, "VII":7, "VIII":8, "IX":9}
tens = {"":0, "X":10, "XX":20, "XXX":30, "XL":40, "L":50, "LX":60, "LXX":70, "LXXX":80, "XC":90}
hundreds = {"":0, "C":100, "CC":200, "CCC":300, "CD":400, "D":500, "DC":600, "DCC":700, "DCCC":800, "CM":900}
thousands = {"":0,"M":1000, "MM":2000, "MMM":3000}
#Tuple so we can iterate through dictionaries
dicts = (thousands, hundreds, tens, ones)

def romanToDec(number):
    """
        decToRoman(number)

       Takes a string representing a number in roman numerals and return an integer representation of that same number, or -1 if the number passed is not valid 

        Arguments:
            number: A string representing a number in roman numerals 
    """
    #Initialize the total and uppercase the number so we don't have to do it several times later
    total = 0
    number = number.upper()

    #Iterate through our tuple of dictionaries
    for currDict in dicts:
        #Reverse the items in current dictionary and iterate through 
        for currItem in reversed(currDict.items()):
            #If the number starts with the current key...
            if number.startswith(currItem[0]):
                #... Then add the value for it to the total
                total += currItem[1]
                #Trim the number to remove the current match from the beginning and then exit the inner loop
                number = number[len(currItem[0]):]
                break
    #If the number is not empty by now, then that means it contained more than one match for at least one of the dictionaries
    #In that case, the number isn't valid, so we overwrite the total with -1
    if len(number) != 0:
        total = -1
    return total

#Loop through the arguments, then convert and print each one. Convert to uppercase when printing just to be pretty
for i in sys.argv[1:]:
    print(i.upper() + " is " + str(romanToDec(i)))
