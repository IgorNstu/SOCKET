#include "ad.h"

int create_tcp_local(void) {
    int id_soc,user_id=0,r;
    struct sockaddr_un server_address;
    int optval =1;
    int optlen = sizeof(optval);
    char msg[1024];
    char msg2[]="HAY_HAY_HAY,CLIENT!";
    int msg2_len=sizeof(msg2);
    int server_len;
    /*Разрываем связь с файлом, для возможности привязать к нему сокет повторно.
     * (REUSERADDR почему то не помогает с локальным вариантом)*/
    unlink("/home/igor/server_socket");
    id_soc=socket(AF_LOCAL,SOCK_STREAM,0);
    if (id_soc==-1){
        perror("Создание сокета\n");
        return 1;
    }
    server_address.sun_family = AF_LOCAL;
    strcpy(server_address.sun_path, "/home/igor/server_socket");
    server_len = sizeof(server_address);
    /*Устанавливаем параметр у сокета*/
    r=setsockopt(id_soc,SOL_SOCKET,SO_REUSEADDR,&optval,optlen);
    if (r==-1){
        perror("Установка параметра сокета");
        close(id_soc);
        return 1;
    }
    r = bind(id_soc, (struct sockaddr *)&server_address, server_len);
    if(r==-1){
        perror("Файл сокета с таким именем уже находится в директории\n");
        close(id_soc);
        return 1;
    }
    listen(id_soc,3);
    printf("Я сервер,ожидаю подключения клиента\n");
    user_id=accept(id_soc,NULL,NULL);
    if (user_id==-1){
        perror("Ассепт");
        return 1;
    }
    printf("Я сервер,ожидаю сообщения от клиента\n");
    int msg_len=sizeof(msg);
    recv(user_id,msg,msg_len,0);
    printf("Я сервер,получил эту строку:%s\n",msg);
    send(user_id,msg2,msg2_len,0);
    close(user_id);
    close(id_soc);
    return 0;

}

int create_tcp_inet(void){
    int id_soc,user_id=0,r;
    struct sockaddr_in server_address;
    int optval =1;
    int optlen = sizeof(optval);
    char msg[1024];
    char msg2[]="HAY_HAY_HAY";
    int msg2_len=sizeof(msg2);
    int server_len;
    id_soc=socket(AF_INET,SOCK_STREAM,0);
    if (id_soc==-1){
        perror("Создание сокета\n");
        return 1;
    }
    server_address.sin_family = AF_INET;
    server_address.sin_port = 5000;
    server_address.sin_addr.s_addr=  htonl(INADDR_LOOPBACK);
    server_len = sizeof(server_address);
    /*Устанавливаем параметр сокета,позволяющий повторное подключение к порту*/
    r=setsockopt(id_soc,SOL_SOCKET,SO_REUSEPORT,&optval,optlen);
    if (r==-1){
        perror("Установка параметра сокета");
        close(id_soc);
        return 1;
    }
    r = bind(id_soc, (struct sockaddr *)&server_address, server_len);
    if(r==-1){
        perror("Порт занят\n");
        close(id_soc);
        return 1;
    }
    listen(id_soc,3);
    printf("Я сервер,ожидаю подключения клиента\n");
    user_id=accept(id_soc,NULL,NULL);
    if (user_id==-1){
        perror("Ассепт");
        return 1;
    }

    int msg_len=sizeof(msg);
    recv(user_id,msg,msg_len,0);
    printf("Я сервер,получил эту строку:%s\n",msg);
    send(user_id,msg2,msg2_len,0);
    close(user_id);
    close(id_soc);
    return 0;
}

int create_udp_inet(void){
    int id_soc,user_id=0,r;
    struct sockaddr_in server_address,user_address;
    int optval =1;
    int optlen = sizeof(optval);
    char msg[1024];
    char msg2[]="HAY_HAY_HAY,USER!";
    int msg2_len=sizeof(msg2);
    int server_len;
    int user_len;
    server_len = sizeof(server_address);
    user_len=sizeof(user_address);

    id_soc=socket(AF_INET,SOCK_DGRAM,0);
    if (id_soc==-1){
        perror("Создание сокета\n");
        return 1;
    }
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5000);
    server_address.sin_addr.s_addr=  htonl(INADDR_LOOPBACK);
    r=setsockopt(id_soc,SOL_SOCKET,SO_REUSEADDR,&optval,optlen);
    if (r==-1){
        perror("Установка параметра сокета");
        close(id_soc);
        return 1;
    }
    r = bind(id_soc, (struct sockaddr *)&server_address, server_len);
    if(r==-1){
        perror("Порт занят\n");
        close(id_soc);
        return 1;
    }

    printf("Я сервер,ожидаю сообщения от клиента\n");
    int msg_len=sizeof(msg);

    /*Ожидаем сообщения. В закоментированной строчке вариант, при котором сервер не корректно сохраняет
     адресс отправителя, и отправляет сообщение через закоментированное sendto не ему*/
    recvfrom(id_soc,msg,msg_len,0,0,0);
    //recvfrom(id_soc,msg,msg_len,0,(struct sockaddr*)&server_address,(socklen_t*)server_len);

    printf("Я сервер,получил эту строку:%s\n",msg);
    /*
    r=sendto(id_soc,msg2,msg2_len,0,(struct sockaddr*)&user_address,(socklen_t)user_len);
    if (r<0){
        perror("отправка");
        return 1;
    }
    */
    close(user_id);
    close(id_soc);
    return 0;
}
