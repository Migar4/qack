#ifndef Q_STRING
#define Q_STRING


#include <string.h>

//a simple string class that will not throw any exceptions
class q_String{

    private:
        char *buffer;
        int length;
    
    public:
        q_String(const char *S);
        q_String(const q_String& s);
        virtual ~q_String();
        q_String& operator +(const char* s) {append(s); return *this;}
        q_String& operator +(const q_String& s) {append(s); return *this;};

        const char* getString() const {return buffer;}
        int getLength() const {return length;}

    protected:
        void append(const char* s);
        void append(const q_String& s);
};



#endif