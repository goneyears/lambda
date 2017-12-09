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
def fakeF():
    print('forward'+str('x'))
exes.Fevent.append(fakeF)
def TF():
    print ('testprint')

def L():
    print('left1')
def R():
    print('right1')
def S(x):
    return True

def standard_env():
    env = Env()
    env.update({
        '+': op.add, '-': op.sub, '*': op.mul, '/': op.truediv,
        '>': op.gt, '<': op.lt, '>=': op.ge, '<=': op.le, '==': op.eq,

        'F': exes.F,
        'L': L,
        'R': R,
        'S': S,
        'T': TF,
    })
    return env

class Env(dict):
    def __init__(self, parms=(), args=(), outer=None):
        self.update(zip(parms, args))
        self.outer = outer
    def find(self, var):
        # return self if (var in self) else self.outer.find(var)
        if (var in self):
            return self
        elif self.outer!=None:
            self.outer.find(var)
        else:
            return None


global_env = standard_env()


class Procedure(object):
    def __init__(self, proc, exp, env):
        self.proc, self.exp = proc, exp
        # env[proc] = exp
    def __call__(self):
        return eval(self.exp)
def multibracket(x):
    return isinstance(x[0],list)

def eval(x, env=global_env):
    # print(x)
    if x==None:
        return None
    elif isinstance(x, Symbol):

        return env.find(x)[x]
    elif isinstance(x, Number):
        return x
    elif x[0]=='DEF':
        (_, proc, exp) = x
        env[proc] = Procedure(proc, exp, env)
    elif x[0]=='SET':
        (_, var, exp) = x
        if env.find(var)==None:
            print("var will be defined "+str(var))
            env[var] = eval(exp)
        else:
            env.find(var)[var] = eval(exp)
    elif x[0]=='IF':
        (_, test, conseq) = x
        if eval(test):
            exp = conseq
        else:
            return None
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

_tT = 1
def preproc(x):
    def eqtodef(s):
        pattern = re.compile(r'(.*)=(.*)')
        f = pattern.search(s)
        while (f):
            s = s.replace(f.group(0), '[DEF ' + f.group(1) + ' [' + f.group(2)+ ']]')
            f = pattern.search(s)
        print(s)
        return s
    def whileformat(s):
        global _tT
        pattern = re.compile(r'(\w+)\((\d+)\)')
        f = pattern.search(s)
        while (f):
            s = s.replace(f.group(0), '[SET _I 1][WHILE [<= _I ' + f.group(2) + '][[' + f.group(1) + '][SET _I [+ _I 1]]]]  ')
            s = s.replace('_I', '_I'+str(_tT))
            _tT = _tT + 1
            f = pattern.search(s)
        return s
    return whileformat(eqtodef(x))

def repl(s):
    p1 = preproc(s)
    print(p1)
    p2 = read_from_tokens(p1)
    print(p2)
    p3 = eval(p2)
    return p3

str2 = '[ IF [ S(L) ] [ R(1)[L(1)R(1)]]]'

str1 = '[WHILE[S(L)][R(1)L(1)F(1)]]'
str3 = 'F(3)'

str41 = '[SET I 1]'
str4 = '[SET I 1][WHILE[<= I 3][[SET J 1][WHILE[<= J 2][[T][SET J [+ J 1]]]][SET I [+ I 1]]]]'
str5 = '[SET M 2]'
str6 = '[+ M 1]'
str7b = 'R(2)F(1)R(2)'
str70 = 'B=R(2)T(1)L(2)'
str7s = 'B=R(2)'
str7 = '[DEF B [R(1)F(1)R(2)]]'
str8 = 'B(2)'
str9 = '[SET I 1][WHILE[<= I 2][[B][SET I [+ I 1]]]]'
str10 = '[SET I 1][WHILE[<= I 2][[R(2)F(1)R(2)][SET I [+ I 1]]]]'
s1 = '[DEF B [[SET I 1][WHILE[<= I 2][[T][SET I [+ I 1]]]]]]'
s2 = '[SET I 1][WHILE[<= I 2][[B][SET I [+ I 1]]]]'
s3 = '[B]'
# m1 = preproc(str70)
# print(m1)
# eval(read_from_tokens(m1))
# m2 = preproc(str8)
# eval(read_from_tokens(m2))
stra = 'IF[S(L)][R(1)]'
repl(stra)
# repl(str8)
# eval(read_from_tokens(s1))
# eval(read_from_tokens(s3))
