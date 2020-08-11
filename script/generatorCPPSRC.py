import os

def dealFile(path, cb):
    for fileName in os.listdir(path):
        filePath = os.path.join(path, fileName)
        if os.path.isdir(filePath):
            dealFile(filePath, cb)
        else:
            cb(filePath)

def removeFile(fileName):
    if os.path.exists(fileName):
        st = os.path.splitext(fileName)
    if len(st) >= 2:
        if st[1] != '.h' and st[1] != '.js' and st[1] != '.inl' and st[1] != '.py' and st[1] != '.cpp':
            os.remove(fileName)

def createFile(fileName):
    fp = open(fileName, 'w', encoding='utf-8')
    fp.close()

def getFileNameSpace(fileName):
    if os.path.exists(fileName):
        st = str.split(fileName, '\\')
        if len(st) == 2:
            return 'Three'
        else:
            return 'Three::' + st[1]

def getFileName(filePath):
    if os.path.exists(filePath):
        st = os.path.splitext(filePath)[0]
        st = str.split(st, '\\')
        return st[-1]

def generatorHeaderContext(fileName):
    if os.path.exists(fileName):
        if os.path.splitext(fileName)[1] == '.h':
            if os.path.getsize(fileName) == 0:
                fp = open(fileName, 'w', encoding='utf-8')
                fp.write("#pragma once\n")
                fp.write('\n')
                fp.write('namespace ' + getFileNameSpace(fileName) + '{\n')
                fp.write('class ' + getFileName(fileName) + "{} \n")
                fp.write('}\n')

def generateCPPHeaderAndSrc(fileName):
    if os.path.exists(fileName):
        st = os.path.splitext(fileName)
        if len(st) >= 2:
            if st[1] == '.js':
                os.remove(fileName)
                createFile(st[0] + '.h')
                createFile(st[0] + '.cpp')
            if st[1] == '.h':
                print (st[1])
                if not os.path.exists(st[0] + '.inl') and not os.path.exists(st[0] + '.cpp'):
                    createFile(st[0] + '.cpp')


def changeCppToInl(fileName):
    if os.path.exists(fileName):
        st = os.path.splitext(fileName)
        if len(st) >= 2 and st[1] == '.cpp':
            os.remove(fileName)
            createFile(st[0] + '.inl')
dealFile('..\\src\\', removeFile)
dealFile('..\\src\\', generateCPPHeaderAndSrc)
dealFile('..\\src\\', generatorHeaderContext)
dealFile('..\\src\\Math\\', changeCppToInl)