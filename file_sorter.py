import os
import shutil as su

filetodlt = os.listdir("D:/C++/Capstone/Programs/filetoberead/selfmadefiles")
for file in filetodlt:
    os.remove(f"D:/C++/Capstone/Programs/filetoberead/selfmadefiles/{file}")

lst = os.listdir("D:/C++/Capstone/Programs/filetoberead")
i = 0
cnames = dict()
for file in lst:
    if file.endswith(".csv"):
        with open(f"D:/C++/Capstone/Programs/filetoberead/{file}", 'r') as f:
            s = f.readline().split(',')[0]
            if s[-1].isdigit():
                rno = int(s[-1])
            elif 'HR' in s:
                rno = 4
            else:
                rno = 5
            temp = f.readline()
            name = f.readline().split(',')[4]
            year = f.readline().split(',')[9][-4:]
            if name in cnames:
                newname = 'company'+str(cnames[name])+'_round'+str(rno)+f'_{year}'+'.csv'
                su.copy(f"D:/C++/Capstone/Programs/filetoberead/{file}", f"D:/C++/Capstone/Programs/filetoberead/selfmadefiles/{newname}")
            else:
                i = i+1
                cnames[name] = i
                newname = 'company'+str(cnames[name])+'_round'+str(rno)+f'_{year}'+'.csv'
                su.copy(f"D:/C++/Capstone/Programs/filetoberead/{file}", f"D:/C++/Capstone/Programs/filetoberead/selfmadefiles/{newname}")

filenames = os.listdir("D:/C++/Capstone/Programs/filetoberead/selfmadefiles")
with open("fnames.txt", 'w') as f:
    for name in filenames:
        f.write(name+"\n")
