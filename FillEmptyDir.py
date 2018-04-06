import os

def AddGitEmptyFile(curdir):
    dirfile=os.path.join(curdir,'git.empty')
    f = open(dirfile, 'w')
    f.close()
    return

def fillEmptyDir(curdir):
    dirfiles=os.listdir(curdir)
    #print(len(dirfiles))
    if not dirfiles:
        print(r'CREATE git.empty file: '+curdir+r'\git.empty')
        AddGitEmptyFile(curdir)
        return
    else:
        if(os.path.exists(os.path.join(curdir, 'git.empty')) and len(dirfiles)>1 ):
            os.remove(os.path.join(curdir, 'git.empty'))
            print(r'REMOVE git.empty file:'+curdir+r'\git.empty')

    for i in range(0, len(dirfiles)):
        subdir = os.path.join(curdir, dirfiles[i])
        if os.path.isdir(subdir):
            fillEmptyDir(subdir)
    return


fillEmptyDir(os.getcwd())
input("\nPress the ENTER key to exit.")


