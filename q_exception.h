#ifndef Q_EXCEPTION
#define Q_EXCEPTION


#include <errno.h>
#include <stdio.h>
#include "q_string.h"

class q_Exception{

    private:
        int ErrNo;
        q_String msg;
    
    public:
        q_Exception(const q_String _msg, int err = 0) : msg(_msg), ErrNo(err){}
        virtual ~q_Exception(){}
        int getError() const {return ErrNo;}
        virtual void printException() const;
        

};

inline void q_Exception::printException() const{
    fprintf(stderr, "%s", msg.getString());
    if (ErrNo != 0){
        errno = ErrNo;
        perror("--ERROR");
    }else{
        printf("\n");
    }
}

class q_RangeException : q_Exception{
    public:
        q_RangeException(const q_String _msg) : q_Exception(_msg, ERANGE){}
        virtual ~q_RangeException(){}

};

class q_FileException : q_Exception{
    public:
        q_FileException(const q_String _msg) : q_Exception(_msg, errno){}
        virtual ~q_FileException(){}

};

class q_NetException : q_Exception{

    public:
        q_NetException(const q_String _msg) : q_Exception(_msg, errno){}
        virtual ~q_NetException(){}

};

class q_NetIOException : q_NetException{
    public:
        q_NetIOException(const q_String _msg) : q_NetException(_msg){}
        virtual ~q_NetIOException(){}

};

class q_NetDNSException : q_NetException{
    public:
        q_NetDNSException(const q_String _msg) : q_NetException(_msg){}
        virtual ~q_NetDNSException(){}

};

class q_NetConfigException : q_NetException{
    public:
        q_NetConfigException(const q_String _msg) : q_NetException(_msg){}
        virtual ~q_NetConfigException(){}

};

class q_NetConnectException : q_NetException{
    public:
        q_NetConnectException(const q_String _msg) : q_NetException(_msg){}
        virtual ~q_NetConnectException(){}

};

class q_NetConversionException : q_NetException{
    public:
        q_NetConversionException(const q_String _msg) : q_NetException(_msg){}
        virtual ~q_NetConversionException(){}

};

#endif