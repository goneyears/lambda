from __future__ import division
import re
import math
import operator as op
Symbol = str
List = list
Number = (int, float)

def s_read_from_tokens(tokens):
    def tokenize(s):
        r = s.replace(')', ')\n').split('\n')
        while '' in r:
            r.remove('')
        return r

    L = []

    def read_helper(tokens):
        if len(tokens)>0:
            t = tokens[0].replace(')',' ').replace('(',' ').split()
            L.append(t)
            tokens.pop(0)
            L.append(read_helper(tokens))

    read_helper(tokenize(tokens))

    while None in L:
        L.remove(None)

    return L


def read_from_tokens(tokens):
    def repsb(s):
        pattern = re.compile(r'(\w+)\((\w+)\)')
        ts = ''
        f = pattern.search(s)
        while (f):
            s = s.replace(f.group(0), '[' + f.group(1) + ' ' + f.group(2) + ']')
            f = pattern.search(s)
        return s

    def tokenize(s):
        s = repsb(s)
        return s.replace(']',' ] ').replace('[',' [ ').split()

    def read_helper(tokens):

        if len(tokens)==0: raise SyntaxError('unexpected eof while reading')
        token = tokens.pop(0)
        if token=='[':
            L = []
            while(tokens[0] != ']'):
                L.append(read_helper(tokens))
            tokens.pop(0)
            return L
        elif ']'==token:
            raise SyntaxError('unexpected ]')
        else:
            return token
    return read_helper(tokenize(tokens))

def addbracket(s):
    return '['+s+']'

def L(x):
    print(x)
def R(x):
    print('right'+str(x))
def S(x):
    return True
def standard_env():
    env = Env()
    env.update({
        'L' : L,
        'R' : R,
        'S' : S,
    })
    return env

class Env(dict):
    def __init__(self, parms=(), args=(), outer=None):
        self.update(zip(parms, args))
        self.outer = outer
    def find(self, var):
        return self if (var in self) else self.outer.find(var)

global_env = standard_env()
def multibracket(x):
    return isinstance(x[0],list)

def eval(x, env=global_env):
    if isinstance(x, Symbol):
        return env.find(x)[x]
    if x[0]=='IF':
        print('in if')
        (_, test, conseq) = x
        print('test: ')
        print(test)
        print('conseq: ')
        print(conseq)
        print(eval(test))
        if eval(test):
            print('eval true')
            exp = conseq
        else:
            print('false')
        # exp = (conseq if eval(test,env) else print('false'))
        print(exp)
        eval(exp)
    if multibracket(x):
        for index, lst in enumerate(x):
            print(lst)
            if index < len(x)-1:
                eval(lst)
            else:#return last expression value
                return eval(lst)
    else:
        proc = eval(x[0], env)
        args = x[1:]
        return proc(*args)

str2 = '[ IF [ S(L) ] [ R(1)L(1) ]]'

str1 = '[L(1)R(1)L(3)]'
str3 = '[S(L)]'
str4 = '[ R(1)L(1) ]'
# print(read_from_tokens(addbracket(str1)))
# print(read_from_tokens(str2))
eval(read_from_tokens(str2))


