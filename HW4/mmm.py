import sys

def mmm(args):
  smallPos = 100000000
  largeNeg = -100000000
  for arg in args:
    n = int(arg)
    if n > 0 and n < smallPos:
      smallPos = n
    elif n < 0 and n> largeNeg:
      largeNeg = n
  return (smallPos, largeNeg)

(smallPos, largeNeg) = mmm(sys.argv[1:])
print("Smallest positive=%d Largest negative=%d" % (smallPos, largeNeg))
