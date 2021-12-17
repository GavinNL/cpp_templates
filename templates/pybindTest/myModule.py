#!/usr/bin/env python3

def callMe(d):
    print("Python Function callMe: " + str(d));

def helloFromPython():
    print("helloFromPython()")
    callMe(333)
    return "hello world"

def callMeToo(x):
    return x*2


# this is executed if we call this script from the command line
if __name__ == "__main__":
    callMe(2)
    helloFromPython()
