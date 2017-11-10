import re

# str = ' c332 st123  z132  up  f1200 '
#c1 st1 z1 up f2, z2 forward f3
#case2 st2 z3 down f4, z4 left f5
#c3 b1 t123
# eg.
# c3 st1 b1 t1 f7
# c4 st1 z2 down f3, z3 down f5
# c5 st1 z1 forward f1
# c6 st1 z2 up f4, z3 up f6, z1 back f6


class ZLine:

    def __init__(self,_zline):
        self.Str=_zline
        self.StN = 'xxx'
        self.ZN = ['xxx']
        self.Motion = ['xxx']
        self.Fehler = ['xxx']
        self.Case = 'xxx'

        self.extract(_zline)

    def regular(self, str):
        strl = str.lower()
        strnr1 = re.sub(r',+|(\s+)', r' ', strl)
        stnr = re.sub(r'\sz(\d+)', r', z\1', strnr1)
        stnr = stnr + ','

    def extract(self, str):
        str = self.regular(str)
        self.stN = re.compile(r'.*[sS]t(\d+).*').match(str).group(1)

        zstrls=re.compile(r'\bz\d.*?,').findall(str)

        i = 0
        for zstr in zstrls:
            zmatch = re.compile(r'.*z(?P<ZN>\d+)\s+(?P<Motion>\w+)').match(str)
            self.ZN[i] = zmatch.group('ZN')

            self.Motion[i] = zmatch.group('Motion')
            self.Motion[i] = re.sub(r'^(up|down|left|right)$',r'\1ward', self.Motion)

            fmatch = re.compile(r'.*f(ehler)?\s*(?P<Fehler>\d+)').match(str)
            if fmatch:
                self.Fehler = fmatch.group('Fehler')

            cmatch = re.compile(r'.*c(ase)?\s*(?P<Case>\d+)').match(str)
            if cmatch(str):
                self.Case = cmatch.group('Case')
 
        
    def neg_motion(self, motion):
        dict = {'forward':'backward', 'backward':'forward', 'upward' : 'downward', 'leftward' : 'rightward',
                'rightward': 'leftward', 'open': 'close', 'close': 'open'}

        return dict[motion]
    # case 3:
    # if (M_.MaStepEn)
    #     {
    #     if (E_St10_B1_4_good_parts_ejector_in_front & & !E_St10_B1_2_good_parts_ejector_back )
    #     {
    #         Step[SEQ] + +;
    #     }
    #     }
    #
    #     // Main Air Off
    #     MainAir[MainAirValve] = false;
    #
    #     // Assign outputs
    #     A.St10_Y1_2_good_parts_ejector_backward = false;
    #     A.St10_Y1_4_good_parts_ejector_forward = true;
    #
    #     // Assign errors
    #     if (M_Error_Search)
    #         {
    #         if (!E_St10_B1_4_good_parts_ejector_in_front | | E_St10_B1_2_good_parts_ejector_back) Fehler(PRG1, ErrorNum, 1, 0);
    #         }
    #         break;
    def formatted_code(self, zbins, nbins, zouts):
        cstr1  = 'case' + self.Case + ':'
        cstr2  = '   St' + self.StN + ' Z' + self.ZN + ' ' + self.Motion
        cstr3 = 'if(' +\
                zbins.search(self.StN, self.ZN, self.Motion).Var + '&&' +\
                zbins.search(self.StN, self.ZN, self.neg_motion(self.Motion)).Var +\
                ') \n'
        print(self.neg_motion(self.Motion))
        print(zbins.search(self.StN, self.ZN, self.neg_motion(self.Motion)).Var)

        cstr4 = zouts.search(self.StN, self.ZN, self.Motion).Var + '= true; \n' +\
                zouts.search(self.StN, self.ZN, self.neg_motion(self.Motion)).Var + '= false; \n'
        cstr5  = 'f:' + self.Fehler
        return cstr1 + '\n' + cstr2 + '\n' + cstr3 + '\n' + cstr4 + '\n' + cstr5

    def display(self):
        return 'self.Str: ' + self.Str+' self.StN: ' + self.StN + ' self.CylinderN: ' + self.ZN +\
               ' self.Motion:' + self.Motion + ' self.Fehler: ' + self.Fehler + ' self.Case: ' + self.Case