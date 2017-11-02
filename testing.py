import subprocess
import os
import random
from multiprocessing import Pool
random.seed(0)

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
binary_operators = ['+', '-', '*', '/', '%', '|', '^', '&', '<<', '>>', '==', '!=', '<', '>', '<=', '>=']
compound_assignment = ['+=', '-=', '*=', '/=', '%=', '|=', '^=', '&=', '<<=', '>>=']

def type_is_float(tp):         return tp in built_in_types_integer and tp not in built_in_types_integer
def op_requires_same_unit(op): return op in ['+', '-', '|', '^', '&', '<<', '>>', '==', '!=', '<', '>', '<=', '>=', '+=', '-=', '|=', '^=', '&=', '<<=', '>>=']
def op_is_bitwise(op):         return op in ['|', '^', '&', '<<', '>>', '|=', '^=', '&=', '<<=', '>>=']
def op_is_compound(op):        return op in ['+=', '-=', '|=', '^=', '&=', '<<=', '>>=']


is_var_char = lambda c: True if 'a' <= c <= 'z' or 'A' <= c <= 'Z' or c == '_' else False

def compile_run(lines, suffix = "", skip_dim_anl = False, explicit_contr = False):
    cpp_name = "testing_temp\\temp-test%s.cpp" % (suffix,)
    exe_name = "testing_temp\\temp-test%s.exe" % (suffix,)
    cpl_out  = "testing_temp\\temp-compiler_output%s.txt" % (suffix,)
    program = '''
        #include <iostream>
        %s
        %s
        #include "../dimensional_analysis.h"


        class A {};

        int main(int argc, char* argv[]) {
            %s
            return 0;
        }
        '''
    program = program % ("#define SKIP_DIMENSIONAL_ANALYSIS" if skip_dim_anl else "",
                         "#define EXPLICIT_CONSTRUCTOR" if explicit_contr else "",
                         ";\n".join([lines] if type(lines) == str else lines) + ';')

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

def unexpected_compile_error(compile_error, lines):
    return "Unexpected compilation error:\n\n>>> " + compile_error.replace('\n', '\n>>> ') + "\n\nwhile running the following lines:\n    " + '\n    '.join(lines)

def unexpected_output(output, lines):
    return "Incorrect output obtained:\n\n>>> " + output.replace('\n', '\n>>> ') + "\n\nwhile running the following lines:\n    " + '\n    '.join(lines)

def test_binary_operator_unit(args):
    lhs_dims, rhs_dims, lhs_t, rhs_t, operator, skip_dim_anl, expl_constr  =  args
    num_a, num_b = "7", "3"

    lines = ["%s bi_a = %s" % (lhs_t, num_a),
             "%s bi_b = %s" % (rhs_t, num_b),
             "auto bi_c = (bi_a %s bi_b)" % (operator,),
             "%s<%s> lt_a(%s)" % (my_types[lhs_t], lhs_dims, num_a),
             "%s<%s> lt_b(%s)" % (my_types[rhs_t], rhs_dims, num_b),
             "auto lt_c = (lt_a %s lt_b)" % (operator,),
             "std::cout << (bi_a == lt_a.value) << std::endl",
             "std::cout << (bi_b == lt_b.value) << std::endl",
             "std::cout << (bi_c == lt_c.value) << std::endl",
             "std::cout << (std::is_same<decltype(bi_c), decltype(lt_c.value)>::value)"]

    cmp_msg, run_msg = compile_run(lines, "__%s_%s_%s_%s_%s_%s_%s_%s_%s__" % (lhs_dims, rhs_dims, my_types[lhs_t], my_types[rhs_t], skip_dim_anl, expl_constr, hash(operator), skip_dim_anl, expl_constr))
    """
    if (not type_is_float(lhs_t)) and (not type_is_float(rhs_t)): # both types are integer
        if op_is_bitwise(operator): # bitwise bitwise operation between integers
            if op_is_compound(operator): # compound bitwise operation between integers
                pass
            else: # binary bitwise operation between integers
                pass
        elif op_requires_same_unit(operator):
            if op_is_compound(operator): pass
            else: pass
        else:
            if op_is_compound(operator): pass
            else: pass
    else: # there is at least one float
        if op_is_bitwise(operator):
            if op_is_compound(operator): pass
            else: pass
        elif op_requires_same_unit(operator):
            if op_is_compound(operator): pass
            else: pass
        else:
            if op_is_compound(operator): pass
            else: pass
    """
    if run_msg != "":
        if sum([int(i) for i in run_msg.split('\n')]) < 4:
            return unexpected_output(run_msg, lines)

    return ""

def test_binary_operators(pool, Dimensions, types, operators):
    size = len(Dims)**2 * len(built_in_types_numeric)**2
    i = 0
    cases = []
    for lhs_dims in Dimensions:
        for rhs_dims in Dimensions:
            for lhs_t in types:
                for rhs_t in types:
                    for op in operators:
                        for skip_dimensional_analysis in [False, True]:
                            for explicit_constructor in [False, True]:
                                cases.append( (lhs_dims, rhs_dims, lhs_t, rhs_t, op, skip_dimensional_analysis, explicit_constructor) )

    random.shuffle(cases)

    n = len(cases)//1000
    I = 0
    for seq in [i for i in [cases[i:i+n if i+n < len(cases) else -1] for i in range(0, len(cases), n)] if i != []]:
        print("\rRunning binary + and - test: " + str(I/10) + "%\t\t", end = "")
        for msg in pool.map(test_binary_operator_unit, seq):
            if msg != "":
                raise Exception(msg)
        I += 1

    print("\rRunning binary + and - test: passed!")


if __name__ == "__main__":
    pool = Pool(8)

    test_binary_operators(pool, Dims, built_in_types_numeric, binary_operators + compound_assignment)
    #test_binary_operators(pool, ["Adimensional"], ["std::int32_t"], ['+='])
