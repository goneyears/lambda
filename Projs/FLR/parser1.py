

def tokenize(s):
    r = s.replace(')',')\n').split('\n')
    while '' in r:
        r.remove('')
    return r




def read_from_tokens(tokens):
    L = []
    def read_helper(tokens):
        if len(tokens)>0:
            t = tokens[0].replace(')',' ').replace('(',' ').split()
            L.append(t)
            tokens.pop(0)
            L.append(read_helper(tokens))

    read_helper(tokens)

    while None in L:
        L.remove(None)

    return L


