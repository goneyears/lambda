from __future__ import division
import re


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

str2 = '[ IF [ S(L) ] [ B(1)L(1) ] ]'

str1 = '[ IF [ S(L) ] ]'
print(read_from_tokens(str2))



