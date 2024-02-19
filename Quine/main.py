#test 
import math

def f(x):
    return (math.expm1(x))/x

def t(x):
    return (math.expm1(x))/math.exp(math.log(x))

def g(x):
    return (math.expm1(x))/math.log(math.exp(x))

def gdiff(x):
    return (math.exp(x)-1)/math.log(math.exp(x))

print("Using (e^x-1)/x :",f(1e-15))

print("Using (e^x-1)/e^(ln x) :",t(1e-15))

print("Using (e^x-1)/ln(e^x) :",g(1e-15))

print("Using (e^x-1)/ln(e^x) :",gdiff(1e-15))
