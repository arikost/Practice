//
// Created by USER on 8/31/2022.
//

#ifndef PRACTICE_BRIDGE_H
#define PRACTICE_BRIDGE_H
using namespace std;
class NetConnectionImp{
public:
    virtual ~NetConnectionImp(){}
    virtual string connect() const = 0;
};
class ImplementationWin: public NetConnectionImp{
public:
    string connect() const override{
        return "implement on Windows platform\n";
    }
};
class ImplementationLinux: public NetConnectionImp{
public:
    string connect() const override{
        return "implement on Linux platform\n";
    }
};
class NetConnection{
protected:
    NetConnectionImp *anImplementation_;
public:
    NetConnection(NetConnectionImp * imp): anImplementation_(imp){}
    virtual ~NetConnection(){}
    virtual string connectionViaProtocol() const{
        return "making UDP Net Connection " + anImplementation_->connect();
    };
};


class TCPNetConnection: public NetConnection{
public:
    TCPNetConnection(NetConnectionImp * imp): NetConnection(imp){}
    string connectionViaProtocol()const override{
        cout<< "waiting for server...\n";
        return "making TCP Net Connection "+ this->anImplementation_->connect();
    }
};
void testBridge(){
    NetConnectionImp * imp1 = new ImplementationWin;
    NetConnection *protocolUDP = new NetConnection(imp1);
    cout << protocolUDP->connectionViaProtocol();
    NetConnectionImp * imp2 = new ImplementationLinux;
    NetConnection *protocolTCP = new TCPNetConnection(imp2);
    cout << protocolTCP->connectionViaProtocol();

}

#endif //PRACTICE_BRIDGE_H
