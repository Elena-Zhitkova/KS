#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <algorithm>
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable: 4996)

int main()
{
    using namespace std;

    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2);
    if (WSAStartup(wVersionRequested, &wsaData) != 0) {//загрузилась ли библиотека
        cout << "Error!" << endl;
        return 1;
    }
    //ф-ция инициализации для полкючения WinSock

    SOCKADDR_IN local;//структура хранить физ адрес компа
    int sizeoflocal = sizeof(local);
    local.sin_family = AF_INET;//семейтсво протоколов
    local.sin_port = htons(1280);//порт для идентификации программы с споступающими данными
    local.sin_addr.s_addr = inet_addr("127.0.0.1");//хранит IP адрес

    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);//создание сокета(домен, тип сокета, протокол)
    bind(s, (SOCKADDR*)&local, sizeof(local));//связывание адреса с сокетом
    listen(s, 5);//установления соединения с клиентом, помещает сокет в состояние прослушивания
     
    SOCKET newConnection;
    newConnection = accept(s, (SOCKADDR*)&local, &sizeoflocal);

    if (newConnection != 0) {
        cout << "Client connected" << endl;
        system("pause");

        char b[255];
        while (recv(newConnection, b, sizeof(b), 0) != 0) {
            sort(b, b + strlen(b));

            send(newConnection, b, sizeof(b), 0);
        }
    }
    else {
        cout << "Error!" << endl;
    }

    closesocket(newConnection);
    WSACleanup();
    system("pause");
    
    return 0;
}