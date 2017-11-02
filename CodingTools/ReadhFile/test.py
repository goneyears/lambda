import xlwings as xw
workbook = xw.Book(r'Typical_Maschineninstallation.xlsm')
data_range = workbook.sheets(r'MG1+1').range('A13')
print(workbook.name)
print(data_range.value)