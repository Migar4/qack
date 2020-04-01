#ifndef Q_HOST_ADDR
#define Q_HOST_ADDR 


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <iostream>
#include "q_exception.h"

/*
    get a valid host name ath the end
*/

typedef enum{eIPv4 = PF_INET, eIPv6 = PF_INET6} ENetwork;

class q_HostAddress{ 

    private:
        static const int MaxHostName = 50;
        ENetwork network;
        char hostName[MaxHostName];
        sockaddr* Addr;
    
    public:
        q_HostAddress(const char* name = 0, int port = 5000, ENetwork net = eIPv4);
        q_HostAddress(q_HostAddress& address);
        virtual ~q_HostAddress();

        void setPort(int port);
        int getPort();
        ENetwork getNetwork() const {return network;}
        sockaddr* getAddress() const {return Addr;}

        int getSize() const;
        int operator == (q_HostAddress& address) const;
        int operator != (q_HostAddress& address) const {return !(operator == (address));}
        //const char* getHost(bool byName = 1); //implement later

};

#endif