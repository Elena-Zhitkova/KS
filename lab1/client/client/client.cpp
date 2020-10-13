#pragma comment(lib, "ws2_32.lib")
#include <iostream>
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
        exit(1);
    }
    //ф-ция инициализации для полкючения WinSock

    SOCKADDR_IN local;//структура хранить физ адрес компа
    int sizeoflocal = sizeof(local);
    local.sin_family = AF_INET;//семейтсво протоколов
    local.sin_port = htons(1280);//порт для идентификации программы с споступающими данными
    local.sin_addr.s_addr = inet_addr("127.0.0.1");//хранит IP адрес

    system("pause");

    SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
    if (connect(Connection, (SOCKADDR*)&local, sizeof(local)) != 0) {
        cout << "Error: failde connect to server." << endl;
        return 1;
    } 
    cout << "Connected!" << endl;
    system("pause");
    
    char buf[255], b[255];
    cout << "Enter the string, please" << endl;
    cin.getline(buf, 100, '\n');
    send(Connection, buf, sizeof(buf), 0);
    if (recv(Connection, b, sizeof(b), 0) != 0) {
        b[strlen(b)] = '\0';

        cout << b << endl;
    }

    closesocket(Connection);
    WSACleanup();

    return 0;
}