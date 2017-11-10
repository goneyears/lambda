import re

str = 'c1 st1 z1 up f3,z2 down f4'
stN = re.compile(r'.*[sS]t(\d+).*').match(str).group(1)
print(stN)
strl=str.lower()
strnr1 = re.sub(r',+|(\s+)',r' ',strl)
stnr = re.sub(r'\sz(\d+)',r', z\1',strnr1)
stnr =stnr + ','
print(stnr)
pattern = re.compile(r'\bz\d.*?,')
print(pattern.findall(stnr))
