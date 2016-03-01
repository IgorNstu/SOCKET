#include "ad.h"


int main(void)
{   int r;
    switch (TYPE_OF_SOCKET) {
    case 0:
        r=create_tcp_local();
        if (r==1){
            printf("Не удалось создать клиента\n");
        }
        break;
    case 1:
        r=create_tcp_inet();
        if (r==1){
            printf("Не удалось создать клиента\n");
        }
        break;
    case 2:
        r=create_udp_inet();
        if (r==1){
            printf("Не удалось создать клиента\n");
        }
        break;
    default:
        printf("Неверное значение константы TYPE_OF_SOCKET:%d\n",TYPE_OF_SOCKET);
        break;
    }

    return 0;
}

