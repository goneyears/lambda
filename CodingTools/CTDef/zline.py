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
        self.ZNs = []
        self.Motions = []
        self.Fehler = []
        self.Case = 'xxx'
        self.extract(_zline)

    def regular(self, str):
        strl = str.lower()
        strnr1 = re.sub(r',+|(\s+)', r' ', strl)
        stnr = re.sub(r'\sz(\d+)', r', z\1', strnr1)
        stnr = stnr + ','
        return stnr

    def extract(self, str):
        str = self.regular(str)
        print('000---'+ str)
        self.StN = re.compile(r'.*[sS]t(\d+).*').match(str).group(1)
        print('stn---'+self.StN)
        cmatch = re.compile(r'.*c(ase)?\s*(?P<Case>\d+)').match(str)
        if cmatch:
            self.Case = cmatch.group('Case')

        zstrls=re.compile(r'\bz\d.*?,').findall(str)

        for zstr in zstrls:
            print('zstr---',zstr)
            zmatch = re.compile(r'.*z(?P<ZN>\d+)\s+(?P<Motion>\w+)').match(zstr)
            self.ZNs.append(zmatch.group('ZN'))

            self.Motions.append(re.sub(r'^(up|down|left|right|back)$',r'\1ward', zmatch.group('Motion')))

            fmatch = re.compile(r'.*f(ehler)?\s*(?P<Fehler>\d+)').match(zstr)
            if fmatch:
                self.Fehler.append(fmatch.group('Fehler'))
            else:
                self.Fehler.append('xxx')

        print(self.Fehler)
        
    def neg_motion(self, motion):
        dict = {'forward':'backward', 'backward':'forward', 'upward' : 'downward', 'downward' : 'upward',
                'leftward' : 'rightward', 'rightward': 'leftward', 'open': 'close', 'close': 'open'}
        print('motion----->'+motion)
        return dict[motion]
    # case 3:
    # if (M_.MaStepEn)
    #     {
    #       if (E_St10_B1_4_good_parts_ejector_in_front && !E_St10_B1_2_good_parts_ejector_back )
    #       {
    #            Step[SEQ] + +;
    #       }
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
        bpairs=[]
        zpairs=[]

        i=0
        for z in self.ZNs:
            if zouts.search(self.StN, z, self.Motions[i]).Ztype == 'not gripper':
                #bp[0]:type, gripper or not gripper
                #bp[1]:positive motion if not girrper or time on if is griiper
                #bp[2]:negative motion or noting if is gripper
                #bp[3]:fehler number if not gripper or nothing if is gripper
                bpair=['not gripper']
                bpair.append(zbins.search(self.StN, z, self.Motions[i]).Var)
                bpair.append(zbins.search(self.StN, z, self.neg_motion(self.Motions[i])).Var)
                bpair.append(self.Fehler[i])
                bpairs.append(bpair)

                zpair=['not gripper']
                zpair.append(zouts.search(self.StN, z, self.Motions[i]).Var)
                zpair.append(zouts.search(self.StN, z, self.neg_motion(self.Motions[i])).Var)
                zpairs.append(zpair)

            elif zouts.search(self.StN, z, self.Motions[i]).Ztype == 'gripper':
                #zp[0]:type, gripper or not gripper
                #zp[1]:positive motion
                #zp[2]:negative motion
                #zp[3]:Isettimer if is gripper or nothing if not gripper
                timevar = 'T_St' + self.StN + '_Z' + z + '_' + zouts.search(self.StN, z, self.Motions[i]).ZName
                bpair=['gripper']
                bpair.append('Time('+timevar+')')
                bpair.append(self.Fehler[i])
                bpairs.append(bpair)

                zpair=['gripper']
                zpair.append(zouts.search(self.StN, z, self.Motions[i]).Var)
                zpair.append(zouts.search(self.StN, z, self.neg_motion(self.Motions[i])).Var)
                zpair.append('ISetTimer('+timevar + ', M_.MaRun && Step[SEQ]== ' + self.Case + ');')
                zpairs.append(zpair)

            i = i+1
        eincond=''
        ainout=''
        einfehler=''

        i = 1
        for bp in bpairs:
            if i==len(bpairs):
                if bp[0]=='gripper':
                    eincond =eincond+ bp[1]
                else:
                    eincond =eincond+ bp[1] + ' && !' + bp[1]
                    einfehler = einfehler + '         if(!' + bp[1] + '||' + bp[2] +') Fehler(PRG1, ErrorNum, ' + bp[3] + ', 0);\n'

            else:
                if bp[0]=='gripper':
                    eincond =eincond+ bp[1] + ' &&\n' + '            '
                else:
                    eincond =eincond+ bp[1] + ' && !' + bp[2] + ' &&\n' + '            '
                    einfehler = einfehler + '         if(!' + bp[1] + '||' + bp[2] +') Fehler(PRG1, ErrorNum, ' + bp[3] + ', 0);\n'


            i = i+1

        for zp in zpairs:
            if zp[0]=='gripper':
                ainout = ainout + zp[1] + ' = true; \n      ' + zp[2] + ' = false;\n\n' + '      '
                ainout = ainout +zp[3] +' \n\n      '
            else:
                ainout = ainout + zp[1] + ' = true; \n      ' + zp[2] + ' = false;\n' + '      '


        ccode  = '   case ' + self.Case + ':' + '\n' +\
                '      if (M_.MaStepEn)\n' +\
                '      {\n' +\
                '         if(' + eincond +')\n         {\n'+'            Step[SEQ]++;\n         }\n' +\
                '      }\n\n' +\
                '      MainAir[MainAirValve] = false;\n\n' +\
                '      '+ainout +'\n' +\
                '      if (M_Error_Search)\n      {\n' +\
                einfehler +\
                '      }\n\n'

        return ccode

    def formate_Z(self, zbins, nbins, zouts):
        pass

    def formate_B(self, zbins, nbins, zouts):
        pass
    
    def display(self):
        return 'self.Str: ' + self.Str+' self.StN: ' + self.StN + ' self.CylinderN: ' + self.ZN +\
               ' self.Motion:' + self.Motion + ' self.Fehler: ' + self.Fehler + ' self.Case: ' + self.Case