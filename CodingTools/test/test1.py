from ctypes import *

great_module = cdll.LoadLibrary('Win32Project1.dll')
print(great_module.great_function(13))
print(great_module.add(13,14))