#include "q_host_addr.h"

inline q_HostAddress::q_HostAddress(const char* name, int port, ENetwork net){
    network = net;
    sockaddr_in* addr = new sockaddr_in(); //create memory for the Addr

    switch(network){    //based on the network family

        case eIPv4: {
            if(name != 0){ //if there is a name make the ip binary for it 
                if(inet_aton(name, &addr->sin_addr) == 0)   //must add a dns lookup
                    throw q_NetConversionException(q_String("inet_aton() failed")); //failed to convert to binary
            }
            else{
                addr->sin_addr.s_addr = INADDR_ANY; //if there is no name it will take any ip address
            }

            addr->sin_family = network;
            addr->sin_port = htons(port);

            Addr = reinterpret_cast<sockaddr*> (addr); // make it a sockaddr* before making Addr point to it
            break;
        }
        
        case eIPv6: {
            sockaddr_in6 * addr = new sockaddr_in6(); //get for the ip version 6

            addr->sin6_family = network;
            addr->sin6_port = 0; // no port

            if(name == 0)
                name = "0::0";
            
            if(inet_pton(eIPv6, name, &addr->sin6_addr) == 0) //convert for ipv6 binary
                throw q_NetConversionException(q_String("inet_pton() failed"));
            
            Addr = reinterpret_cast<sockaddr*> (addr);
            break;
        }
        
        default:
            throw q_Exception(q_String("invalid networktype"), ENOTSUP); //neither ipv4 nor ipv6

    }
}

inline q_HostAddress::q_HostAddress(q_HostAddress& Address){
    network = Address.network;

    switch(network){
        case eIPv4:{
            sockaddr_in* addr = new sockaddr_in(); //make a pointer to a new memory location
            memcpy(addr, Address.Addr, sizeof(*addr)); //copy what is in the Address to that location
            Addr = reinterpret_cast<sockaddr*> (addr); //make it sockaddr* befor making Addr point to it
            break;
        }
        
        case eIPv6:{
            sockaddr_in6* addr = new sockaddr_in6();
            memcpy(addr, Address.Addr, sizeof(*addr));
            Addr = reinterpret_cast<sockaddr*> (addr);
            break;
        }
    }
}

inline q_HostAddress::~q_HostAddress(){
    delete Addr;
}

inline void q_HostAddress::setPort(int port){
    switch(network){
        case eIPv4: {
            sockaddr_in * tmp = reinterpret_cast<sockaddr_in*> (Addr); //make Addr interpret as sockaddr_in* before tmp point to it
            tmp->sin_port = htons(port);//set the port to the converted Addr
            break;
        }

        case eIPv6: {
            sockaddr_in6 * tmp = reinterpret_cast<sockaddr_in6*> (Addr);
            tmp->sin6_port = htons(port);
            break;
        }
    }
}

inline int q_HostAddress::getPort(){
    switch(network){
        case eIPv4: return (reinterpret_cast<sockaddr_in*> (Addr))->sin_port;
        case eIPv6: return (reinterpret_cast<sockaddr_in6*> (Addr))->sin6_port;
    }
}

inline int q_HostAddress::getSize() const{
    switch(network){
        case eIPv4: return sizeof(sockaddr_in);
        case eIPv6: return sizeof(sockaddr_in6);
    }
}

inline int q_HostAddress::operator== (q_HostAddress& address) const{
    if (address.network != network)
        return 0;
    return memcmp(Addr, address.Addr, getSize()); //compare the two memory and send back the result
}

