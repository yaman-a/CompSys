#include <string>

#include "VMTranslator.h"

using namespace std;

/**
 * VMTranslator constructor
 */
VMTranslator::VMTranslator() {
    // Your code here
}

/**
 * VMTranslator destructor
 */
VMTranslator::~VMTranslator() {
    // Your code here
}


/** Generate Hack Assembly code for a VM push operation */
string VMTranslator::vm_push(string segment, int offset){
    string translate;
    string regis;
    string off = to_string(offset);

    if (segment == "this") {
        regis = "THIS";
    } else if (segment == "that") {
        regis = "THAT";
    } else if (segment == "argument") {
        regis = "ARG";
    } else if(segment == "local") {
        regis = "LCL";
    } else if(segment == "static") {
        regis = to_string(16 + offset);
    } else if(segment == "pointer") {
        regis = "R" + to_string(3 + offset);
    } else if(segment == "temp") {
        regis = "R" + to_string(5 + offset);
    } else if(segment == "constant") {
        regis = to_string(offset);
    } else {
        return "";
    }

    if (segment == "constant" || segment == "pointer" || segment == "temp" || segment == "static") {
        translate.append("@" + regis + "\n");
        translate.append("push " + segment + " " + off + "\n");
        if (segment == "constant") {
            translate.append("D=A\n");
        } else {
            translate.append("D=M\n");
        }
    } else if (segment == "this" || segment == "that" || segment == "argument" || segment == "local") {
        translate.append("@" + regis + "\n");
        translate.append("D=M\n");
        translate.append("@" + off + "\n");
        translate.append("A=D+A\n");
        translate.append("D=M\n");
    }

    translate.append("@SP\n");
    translate.append("A=M\n");
    translate.append("M=D\n");
    translate.append("@SP\n");
    translate.append("M=M+1\n");

    return translate;
}

/** Generate Hack Assembly code for a VM pop operation */
string VMTranslator::vm_pop(string segment, int offset){  
    string translate;
    string regis;
    string off = to_string(offset);

    if (segment == "this") {
        regis = "THIS";
    } else if (segment == "that") {
        regis = "THAT";
    } else if (segment == "argument") {
        regis = "ARG";
    } else if(segment == "local") {
        regis = "LCL";
    } else if(segment == "static") {
        regis = to_string(16 + offset);
    } else if(segment == "pointer") {
        regis = "R" + to_string(3 + offset);
    } else if(segment == "temp") {
        regis = "R" + to_string(5 + offset);
    } else if(segment == "constant") {
        regis = to_string(offset);
    } else {
        return "";
    }

    if (segment == "constant") {
        return "";
    }

    translate.append("@" + regis + "\n");

    if ( segment == "static" ||  segment == "temp" || segment == "pointer") {
        translate.append("D=A\n");
    } else if (segment == "this" || segment == "that" || segment == "argument" || segment == "local") {
        translate.append("D=M\n");
        translate.append("@" + off + "\n");
        translate.append("D=D+A\n");
    }

    translate.append("@R13\n");
    translate.append("M=D\n");
    translate.append("@SP\n");
    translate.append("AM=M-1\n");
    translate.append("D=M\n");
    translate.append("@R13\n");
    translate.append("A=M\n");
    translate.append("M=D\n");

    return translate;
}

/** Generate Hack Assembly code for a VM add operation */
string VMTranslator::vm_add(){
    return "";
}

/** Generate Hack Assembly code for a VM sub operation */
string VMTranslator::vm_sub(){
    return "";
}

/** Generate Hack Assembly code for a VM neg operation */
string VMTranslator::vm_neg(){
    return "";
}

/** Generate Hack Assembly code for a VM eq operation */
string VMTranslator::vm_eq(){
    return "";
}

/** Generate Hack Assembly code for a VM gt operation */
string VMTranslator::vm_gt(){
    return "";
}

/** Generate Hack Assembly code for a VM lt operation */
string VMTranslator::vm_lt(){
    return "";
}

/** Generate Hack Assembly code for a VM and operation */
string VMTranslator::vm_and(){
    return "";
}

/** Generate Hack Assembly code for a VM or operation */
string VMTranslator::vm_or(){
    return "";
}

/** Generate Hack Assembly code for a VM not operation */
string VMTranslator::vm_not(){
    return "";
}

/** Generate Hack Assembly code for a VM label operation */
string VMTranslator::vm_label(string label){
    return "";
}

/** Generate Hack Assembly code for a VM goto operation */
string VMTranslator::vm_goto(string label){
    return "";
}

/** Generate Hack Assembly code for a VM if-goto operation */
string VMTranslator::vm_if(string label){
    return "";
}

/** Generate Hack Assembly code for a VM function operation */
string VMTranslator::vm_function(string function_name, int n_vars){
    return "";
}

/** Generate Hack Assembly code for a VM call operation */
string VMTranslator::vm_call(string function_name, int n_args){
    return "";
}

/** Generate Hack Assembly code for a VM return operation */
string VMTranslator::vm_return(){
    return "";
}