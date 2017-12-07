from __future__ import division
import re
import time
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
    def addbrackets(s):
        return '[' + s + ']'

    def repsb(s):
        pattern = re.compile(r'(\w+)\((\w+)\)')
        ts = ''
        f = pattern.search(s)
        while (f):
            s = s.replace(f.group(0), '[' + f.group(1) + ' ' + f.group(2) + ']')
            f = pattern.search(s)
        return addbrackets(s)

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
            return atom(token)
    return read_helper(tokenize(tokens))

def atom(token):
    try: return int(token)
    except ValueError:
        try: return float(token)
        except ValueError:
            return Symbol(token)
class Exes:
    def __init__(self):
        self.Fevent = []
        self.Levent = []
        self.Revent = []
        self.Sevent = []


    def F(self, x):
        [n(x) for n in self.Fevent]
exes = Exes()
def fakeF(x):
    print('forward'+str(x))
exes.Fevent.append(fakeF)
def T():
    print ('testprint')

def L(x):
    print('left'+str(x))
def R(x):
    print('right'+str(x))
def S(x):
    return True
def standard_env():
    env = Env()
    env.update({
        '+': op.add, '-': op.sub, '*': op.mul, '/': op.truediv,
        '>': op.gt, '<': op.lt, '>=': op.ge, '<=': op.le, '=': op.eq,

        'F': exes.F,
        'L': L,
        'R': R,
        'S': S,
        'T': T,
        'I': 1,
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
    if x==None:
        return None
    elif isinstance(x, Symbol):

        return env.find(x)[x]
    elif isinstance(x, Number):
        return x
    elif x[0]=='SET':
        (_, var, exp) = x
        env.find(var)[var] = eval(exp)
    elif x[0]=='IF':
        (_, test, conseq) = x
        if eval(test):
            exp = conseq
        else:
            return None
        # exp = (conseq if eval(test,env) else print('false'))
        eval(exp)
    elif x[0]=='WHILE':
        (_, test, dos) = x
        while eval(test):
            time.sleep(0.5)
            eval(dos)
    elif multibracket(x):
        for index, lst in enumerate(x):
            if index < len(x)-1:
                eval(lst)
            else:#return last expression value
                return eval(lst)
    else:
        proc = eval(x[0], env)
        #args = x[1:] # do not eval args this time for S[L]

        args = [eval(exp) for exp in x[1:]]
        return proc(*args)

str2 = '[ IF [ S(L) ] [ R(1)[L(1)R(1)]]]'

str1 = '[WHILE[S(L)][R(1)L(1)F(1)]]'
str3 = 'F(3)'
str4 = 'WHILE[<= I 3][[T][SET I [+ I 1]]]'
str5 = '[SET I [+ I 1]]'
# print(read_from_tokens(addbracket(str1)))
# print(read_from_tokens(str2))
eval(read_from_tokens(str4))


