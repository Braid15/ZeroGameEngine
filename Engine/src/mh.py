from os import chdir
from os import listdir
from os.path import isfile
from os.path import join
import sys


def get_vs_proj_file():
    files = [f for f in listdir() if isfile(f)]
    file = None
    for f in files:
        if ".vcxproj" in f:
            file = f
            break
    return file

def get_filter_file():
    files = [f for f in listdir() if isfile(f)]
    file = None
    for f in files:
        if ".vcxproj.filters" in f:
            file = f
            break
    return file



def make_header(file_name):
    if '/' in file_name:
        file_name = file_name.replace('/', "\\")
        print(file_name)
    header = open(file_name, "w")

    header.write('#pragma once\n\nnamespace ZeroEngine {\n\n}')
    header.close()
    return file_name

def main():

    if (len(sys.argv) > 1):
        file_to_add = sys.argv[1]

        file_to_add = make_header(file_to_add)

        proj_file = get_vs_proj_file()
        while proj_file is None:
            chdir("..")
            proj_file = get_vs_proj_file()
        f = open(proj_file, "r")
        contents = f.readlines()
        f.close()

        element = ""
        if ".h" in file_to_add:
            element = "ClInclude"
        elif ".cpp" in file_to_add:
            element = "ClCompile"

        index = -1
        for i in range(len(contents)):
            if element in contents[i]:
                index = i
                break

        if index != -1:
            new_line = '    <' + element + ' Include="src\\' + file_to_add  + '" />\n' 
            contents.insert(i, new_line)
            f = open(proj_file, "w")
            contents = "".join(contents)
            f.write(contents)
            f.close()
        else:
            print("Could not find")
    else:
        print("Must specify file to include")




main()


