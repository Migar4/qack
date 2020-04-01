#include "q_string.h"

q_String::q_String(const char* s){
    length = strlen(s);
    buffer = new char[length + 1];
    strcpy(buffer, s);
}

q_String::q_String(const q_String& s){
    length = s.getLength();
    buffer = new char[length + 1];
    strcpy(buffer, s.getString());
}

q_String::~q_String(){
    delete buffer;
}

void q_String::append(const char* s){
    length += strlen(s);
    char* temp = new char[length+1];
    strcpy(temp, buffer);
    strcat(buffer, s);
    delete buffer;
    buffer = temp;
}

void q_String::append(const q_String& s){
    length += s.getLength();
    char* temp = new char[length+1];
    strcpy(temp, buffer);
    strcat(buffer, s.getString());
    delete buffer;
    buffer = temp;
}