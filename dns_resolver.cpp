#include<bits/stdc++.h>
#include<winsock2.h>//all the libraries of networking 
#include<ws2tcpip.h>
#include<chrono>//for lookup time


#pragma comment(lib , "ws2_32.lib")

using namespace std;


int main(){
    cout<<"=========================="<<endl;
    cout<<"NetScope DNS Resolver"<<endl;
    cout<<"=========================="<<endl;
    cout<<" "<<endl;
    string domain;
    cout<<"Domain: ";
    cin>>domain;

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    addrinfo hints = {};
    hints.ai_family = AF_INET;

    addrinfo* result = nullptr;
    auto start = chrono::high_resolution_clock::now();

    int status = getaddrinfo(
        domain.c_str(),
        nullptr,
        &hints,
        &result
    );
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(
        end-start
    );
    
    if(status !=0){
        cout<<"DNS lookup failed\n";
        WSACleanup();
        return 1;
    }

    cout<<"Lookup Time: "<<duration.count()<< " ms"<< endl;
    int cnt=0;//to check the number of ip's
    cout<<"IPv4 Addresses: "<<endl;

   addrinfo* temp =result;

while(temp!=NULL){
     
    sockaddr_in* addr = (sockaddr_in*)temp->ai_addr;


    char ip[INET_ADDRSTRLEN];

    inet_ntop(
        AF_INET,
        &(addr->sin_addr),
        ip,
        sizeof(ip)
    );
    cnt++;

    cout<< cnt <<". "<< ip << endl;
    temp=temp->ai_next;
}
cout<<"Total IPs: "<< cnt << endl;
    freeaddrinfo(result);
    WSACleanup();

    return 0;
}

