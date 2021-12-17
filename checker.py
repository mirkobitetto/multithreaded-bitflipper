import math


def check(numbers):
  for number in numbers:
    root = math.sqrt(number)
    if int(root + 0.5) ** 2 == number:
        print(number, "is a perfect square")
    else:
        print(number, "is not a perfect square")


if __name__ == "__main__":
  numbers = [81,100,121,144,169,196,225,256,289,324,361,400,441,484,529,576,625,676,729,784,841,900,961,1024,1089,1156,1225,1296,1369,1444,1521,1600,1681,1764,1849,1936,2025,2116,2209,2304,2401,2500,2601,2704,2809,2916]
  check(numbers)