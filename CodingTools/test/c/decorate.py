

def memorize(f):
    cache = {}
    def Helper(x):
        if x in cache:
            return cache[x]
        else:
            cache[x] = f(x)
            return cache[x]

    return Helper

def trace(f):
    def Helper(x):
        print('function start'+ str(x))
        return f(x)
        print('function end')
    return Helper

@memorize
@trace
def fib(n):
    if n in (0,1):
        return n
    else:
        return fib(n-1)+fib(n-2)

# fib = memorize(fib)
# print(fib(202))
#fib(202)

# def mtest(f):
#     return f
#
# def fun(x):
#     return x+1
#
# print('mtest:')
# print(mtest(fun)(2))