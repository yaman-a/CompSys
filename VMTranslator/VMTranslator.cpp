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

    if (segment == "constant") {
        translate.append("@" + off + "\n"); 
        translate.append("D=A\n");        
    } else {
        if (segment == "this") {
            regis = "THIS";
        } else if (segment == "that") {
            regis = "THAT";
        } else if (segment == "argument") {
            regis = "ARG";
        } else if (segment == "local") {
            regis = "LCL";
        } else if (segment == "static") {
            regis = to_string(16 + offset);
            translate.append("@" + regis + "\n");
            translate.append("D=M\n");
        } else if (segment == "pointer") {
            regis = "R" + to_string(3 + offset);
            translate.append("@" + regis + "\n");
            translate.append("D=M\n");
        } else if (segment == "temp") {
            regis = "R" + to_string(5 + offset);
            translate.append("@" + regis + "\n");
            translate.append("D=M\n");
        }

        if (segment == "local" || segment == "argument" || segment == "this" || segment == "that") {
            translate.append("@" + regis + "\n");
            translate.append("D=M\n");        
            translate.append("@" + off + "\n");
            translate.append("A=D+A\n");      
            translate.append("D=M\n");        
        }
    }

    // Push value to stack
    translate.append("@SP\n");
    translate.append("A=M\n");  // Point to the top of the stack
    translate.append("M=D\n");  // Store D (the value) at the top of the stack
    translate.append("@SP\n");
    translate.append("M=M+1\n"); // Increment SP

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
    string translate;

    translate.append("@SP\n");
    translate.append("AM=M-1\n");
    translate.append("D=M\n");
    translate.append("A=A-1\n");

    translate.append("M=M+D");

    return translate;
}

/** Generate Hack Assembly code for a VM sub operation */
string VMTranslator::vm_sub(){
    string translate;
    
    translate.append("@SP\n");
    translate.append("AM=M-1\n");
    translate.append("D=M\n");
    translate.append("A=A-1\n");

    translate.append("M=M-D");

    return translate;
}

/** Generate Hack Assembly code for a VM neg operation */
string VMTranslator::vm_neg(){
    string translate;
    
    translate.append("@SP\n");
    translate.append("A=M-1\n");

    translate.append("M=-M\n");

    return translate;
}

/** Generate Hack Assembly code for a VM eq operation */
string VMTranslator::vm_eq() {
    static int eq_count = 0;
    string unique_eq_label = "EQUAL_" + to_string(eq_count);
    string end_label = "END_" + to_string(eq_count);
    eq_count++;

    string translate;
    
    translate.append("@SP\n");
    translate.append("AM=M-1\n");  
    translate.append("D=M\n");     
    translate.append("A=A-1\n");  
    
    translate.append("D=M-D\n");  
    translate.append("@" + unique_eq_label + "\n"); 
    translate.append("D;JEQ\n");
    

    translate.append("@SP\n");
    translate.append("A=M-1\n");
    translate.append("M=0\n");     
    translate.append("@" + end_label + "\n");
    translate.append("0;JMP\n"); 
    
    translate.append("(" + unique_eq_label + ")\n");
    translate.append("@SP\n");
    translate.append("A=M-1\n");
    translate.append("M=-1\n");
    
 
    translate.append("(" + end_label + ")\n");

    return translate;
}


/** Generate Hack Assembly code for a VM gt operation */
string VMTranslator::vm_gt() {
    static int gt_count = 0; 
    string unique_gt_label = "GREATER_" + to_string(gt_count);
    string end_label = "END_" + to_string(gt_count);
    gt_count++; 

    string translate;
    
    translate.append("@SP\n");
    translate.append("AM=M-1\n");  
    translate.append("D=M\n");     
    translate.append("A=A-1\n");   
    
    translate.append("D=M-D\n");   
    translate.append("@" + unique_gt_label + "\n"); 
    translate.append("D;JGT\n");
    
  
    translate.append("@SP\n");
    translate.append("A=M-1\n");
    translate.append("M=0\n");    
    translate.append("@" + end_label + "\n");
    translate.append("0;JMP\n");   
    
    
    translate.append("(" + unique_gt_label + ")\n");
    translate.append("@SP\n");
    translate.append("A=M-1\n");
    translate.append("M=-1\n");    
    
    
    translate.append("(" + end_label + ")\n");

    return translate;
}


/** Generate Hack Assembly code for a VM lt operation */
string VMTranslator::vm_lt() {
    static int lt_count = 0; 
    string unique_lt_label = "LESS_" + to_string(lt_count);
    string end_label = "END_" + to_string(lt_count);
    lt_count++; 

    string translate;
    
    translate.append("@SP\n");
    translate.append("AM=M-1\n");  
    translate.append("D=M\n");    
    translate.append("A=A-1\n");  
    
    translate.append("D=M-D\n");  
    translate.append("@" + unique_lt_label + "\n"); 
    translate.append("D;JLT\n");
    
    
    translate.append("@SP\n");
    translate.append("A=M-1\n");
    translate.append("M=0\n");     
    translate.append("@" + end_label + "\n");
    translate.append("0;JMP\n");   
    
    
    translate.append("(" + unique_lt_label + ")\n");
    translate.append("@SP\n");
    translate.append("A=M-1\n");
    translate.append("M=-1\n");   
    
    translate.append("(" + end_label + ")\n");

    return translate;
}


/** Generate Hack Assembly code for a VM and operation */
string VMTranslator::vm_and(){
    string translate;
    
    translate.append("@SP\n");
    translate.append("AM=M-1\n");
    translate.append("D=M\n");
    translate.append("A=A-1\n");
    translate.append("M=M&D\n");

    return translate;
}

/** Generate Hack Assembly code for a VM or operation */
string VMTranslator::vm_or(){
    string translate;
    
    translate.append("@SP\n");
    translate.append("AM=M-1\n");
    translate.append("D=M\n");
    translate.append("A=A-1\n");
    translate.append("M=M|D\n");

    return translate;
}

/** Generate Hack Assembly code for a VM not operation */
string VMTranslator::vm_not(){
    string translate;
    
    translate.append("@SP\n");
    translate.append("A=M-1\n");
    translate.append("M=!M\n");

    return translate;
}

/** Generate Hack Assembly code for a VM label operation */
string VMTranslator::vm_label(string label) {
    return "(" + label + ")\n";
}


/** Generate Hack Assembly code for a VM goto operation */
string VMTranslator::vm_goto(string label) {
    string translate;
    translate.append("@" + label + "\n"); 
    translate.append("0;JMP\n");          
    return translate;
}


/** Generate Hack Assembly code for a VM if-goto operation */
string VMTranslator::vm_if(string label){
    string translate;
    translate.append("@SP\n");
    translate.append("AM=M-1\n"); 
    translate.append("D=M\n");     
    translate.append("@" + label + "\n");
    translate.append("D;JNE\n");   
    return translate;
}

/** Generate Hack Assembly code for a VM function operation */
string VMTranslator::vm_function(string function_name, int n_vars){
    string translate;
    
    translate.append("(" + function_name + ")\n");
    
    for (int i = 0; i < n_vars; ++i) {
        translate.append("@0\n");
        translate.append("D=A\n");
        translate.append("@SP\n");
        translate.append("A=M\n");
        translate.append("M=D\n");  
        translate.append("@SP\n");
        translate.append("M=M+1\n");
    }

    return translate;
}

/** Generate Hack Assembly code for a VM call operation */
string VMTranslator::vm_call(string function_name, int n_args){
    return "";
}

/** Generate Hack Assembly code for a VM return operation */
string VMTranslator::vm_return(){
    return "";
}