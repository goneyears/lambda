import os

def AddGitIgnoreFile(curdir):
    dirfile=os.path.join(curdir,'git.empty')
    f = open(dirfile, 'w')
    f.close()
    return

def fillEmptyDir(curdir):
    dirfiles=os.listdir(curdir)
    #print(len(dirfiles))
    if not dirfiles:
        print('add git.empty file: '+curdir+'\git.empty')
        AddGitIgnoreFile(curdir)
        return
    else:
        if(os.path.exists(os.path.join(curdir, 'git.empty')) and len(dirfiles)>1 ):
            os.remove(os.path.join(curdir, 'git.empty'))
            print('remove git.empty file:'+curdir+'\git.empty')
    list = os.listdir(curdir)  
    for i in range(0, len(list)):
        subdir = os.path.join(curdir, list[i])
        if os.path.isdir(subdir):
            fillEmptyDir(subdir)
    return


fillEmptyDir(os.getcwd())
input("\nPress the enter key to exit.")


