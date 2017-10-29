import subprocess
import os
import tempfile
from shutil import copyfile

dir_name = "Z:\\"
compiler = "Z:\\compiler\\mingw64\\bin\\g++"
source_code = [i for i in [i for i in os.listdir() if '.' in i] if i.split('.')[-1] in ['c', 'cpp', 'h', 'hpp']]
for i in source_code: copyfile(i, dir_name + i)

Dims = ["Adimensional", "Time", "Length"]
built_in_types_integer = ["std::int8_t", "std::int16_t", "std::int32_t", "std::int64_t", "std::uint8_t", "std::uint16_t", "std::uint32_t", "std::uint64_t"]
built_in_types_int_bool = built_in_types_integer + ["bool"]
built_in_types_numeric = built_in_types_integer + ["float", "double", "long double"]
my_types = {"std::int8_t"   : "int8",
            "std::int16_t"  : "int16",
            "std::int32_t"  : "int32",
            "std::int64_t"  : "int64",
            "std::uint8_t"  : "uint8",
            "std::uint16_t" : "uint16",
            "std::uint32_t" : "uint32",
            "std::uint64_t" : "uint64",
            "float"         : "float32",
            "double"        : "float64",
            "long double"   : "float128"}


is_var_char = lambda c: True if 'a' <= c <= 'z' or 'A' <= c <= 'Z' or c == '_' else False

def compile_run(lines, skip_dim_anl = False):
    cpp_name = dir_name + "temp-test.cpp"
    exe_name = dir_name + "temp-test.exe"
    cpl_out  = dir_name + "temp-compiler_output.txt"
    program = '''
        #include <iostream>
        #include "dimensional_analysis.h"
        %s

        class A {};

        int main(int argc, char* argv[]) {
            %s
            return 0;
        }
        '''
    program = program % ("#define SKIP_DIMENSIONAL_ANALYSIS" if skip_dim_anl else "", ";".join([lines] if type(lines) == str else lines) + ';')

    file = open(cpp_name, 'w')
    file.write(program)
    file.close()
    
    os.system("(" + compiler + " -std=c++11 " + cpp_name + " -o " + exe_name + ") 2> " + cpl_out)
    file = open(cpl_out, 'r')
    compile_message = file.read()
    file.close()
    subprocess.run("rm " + cpl_out, stdout=subprocess.PIPE)
    run_message = ""

    if compile_message == "":
        run_message = subprocess.run(exe_name, stdout = subprocess.PIPE).stdout.decode('utf-8')

    subprocess.run("rm " + cpp_name, stdout = subprocess.PIPE)
    if compile_message == "": subprocess.run("rm " + exe_name, stdout = subprocess.PIPE)
    return compile_message, run_message

def interpret_compile_error(error_msg):
    token = "error: invalid use of incomplete type 'struct "
    idx = error_msg.find(token)
    if idx == -1:
        return ""
    err = error_msg[ + len(token):]
    i = 0
    while is_var_char(err[i]): i += 1
    return err[:i]

def test_add_sub(op):
    size = len(Dims)**2 * len(built_in_types_numeric)**2
    i = 0
    for lhs_dims in Dims:
        for rhs_dims in Dims:
            for lhs_t in built_in_types_numeric:
                for rhs_t in built_in_types_numeric:
                    print("\rRunning binary " + op + " test: " + ("%d/%d" % (i, size)) + " - " + str(int(round(100*i/size))) + "%\t\t", end = '')

                    lines = [""]
                    cmp_msg, run_msg = compile_run(lines)
                    cmp_msg_skip, run_msg_skip = compile_run(lines, True)

                    i += 1


test_add_sub("+")
print(compile_run('std::cout << "Hello"'))

for i in source_code: os.system("rm " + str(dir_name + i))