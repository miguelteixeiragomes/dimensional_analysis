import subprocess
import os
import random
from multiprocessing import Pool

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

def compile_run(lines, suffix = "", skip_dim_anl = False):
    cpp_name = "temp-test%s.cpp" % (suffix,)
    exe_name = "temp-test%s.exe" % (suffix,)
    cpl_out  = "temp-compiler_output%s.txt" % (suffix,)
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
    
    os.system("(g++ -std=c++11 " + cpp_name + " -o " + exe_name + ") 2> " + cpl_out)
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

def test_add_sub_unit(lhs_dims, rhs_dims, lhs_t, rhs_t):
    lines = ["std::cout << (%s<%s>(16) + %s<%s>(32)) << std::endl;" % (my_types[lhs_t], lhs_dims, my_types[rhs_t], rhs_dims),
             "std::cout << (%s<%s>(32) - %s<%s>(16));" % (my_types[lhs_t], lhs_dims, my_types[rhs_t], rhs_dims)]
    cmp_msg, run_msg = compile_run(lines, "__%s_%s_%s_%s__" % (lhs_dims, rhs_dims, lhs_t, rhs_t))

    if lhs_dims == rhs_dims:
        if cmp_msg == "":
            if [float(i) for i in run_msg.split('\n')] != [32+16, 16]:
                return "Incorrect output obtained:\n\n>>> " + run_msg.replace('\n', '\n>>> ') + "\n\nwhile running the following lines:\n    " + '\n    '.join(lines)
        else:
            return "Unexpected compilation error:\n\n>>> " + cmp_msg.replace('\n', '\n>>> ') + "\n\nwhile running the following lines:\n    " + '\n    '.join(lines)

    return ""

def test_add_sub(pool = None):
    size = len(Dims)**2 * len(built_in_types_numeric)**2
    i = 0
    cases = []
    for lhs_dims in Dims:
        for rhs_dims in Dims:
            for lhs_t in built_in_types_numeric:
                for rhs_t in built_in_types_numeric:
                    cases.append( (lhs_dims, rhs_dims, lhs_t, rhs_t) )

    random.shuffle(cases)

    if pool is None:
        for case in cases:
            print("\rRunning binary + and - test: " + str(round(100*i/size, 1)) + "%\t\t", end = '')
            msg = test_add_sub_unit(*case)
            if msg != "":
                raise Exception(msg)
            i += 1

        print("\rRunning binary + and - test: passed!")

    else:
        print("Running binary + and - test: ", end = "")
        aux_func = lambda x: test_add_sub_unit(*x)
        for msg in pool.map(aux_func, cases):
            if msg != "":
                raise Exception(msg)
        print("passed!")



if __name__ == "__main__":
    pool = Pool(4)

    test_add_sub(pool)