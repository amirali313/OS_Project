#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h> //inet_addr
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIRST 6006
#define SEC 7006

void choosing_winner(int random_number1 , int random_number2 , int random_number3 , int n){

    int random_number[3] = {random_number1 , random_number2 , random_number3};
    int i = 0 , greatest = 0 , temp = 0 , winner = 0;
    for (i = 0 ; i < 3 ; i++) {
        if (random_number[i] > temp)
            temp = random_number[i];
            winner = i;
    }
    greatest = temp;
    printf("THE winner is who owned this number:  %d\n",greatest);
    // write(1,&greatest,sizeof(int));
    // char greatestt[100];
    // char winnerr[100];
    // char nn[100];
    // itoa(winner,winnerr,10);
    // itoa(greatest,greatestt,10);
    // itoa(n,nn,10);
    // int file;
    // file = open(nn , O_WRONLY | O_CREAT | O_APPEND , 0644);
    // write(file,&greatestt,sizeof(int));
    // write(file,&winnerr,sizeof(int));

}

int random_generate(int randy){
    int x = randy;
    int a = randy%30;
    int b = randy%55;
    int m = randy%85;
    int tzero = time(0);
    while(1) {
        x = (a * x + b) % m;
        int ezero = time(0);
        if(ezero - tzero > 1)
            break;
    }
    return x;
}

int fork_func(){
        int     fd[2], nbytes;
        pid_t   childpid;
        int    readbuffer[80];

        pipe(fd);

        if((childpid = fork()) == -1) {
                perror("fork");
                exit(1);
        }

        if(childpid == 0) {
                /* Child process closes up input side of pipe */
                close(fd[0]);
                int result = random_generate((int)time(0));
                /* Send "string" through the output side of pipe */
                write(fd[1], &result, sizeof(result));
                exit(0);
        }
        else {
                /* Parent process closes up output side of pipe */
                close(fd[1]);
                /* Read in a string from the pipe */
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                printf("Received number: %d \n", readbuffer);
                return readbuffer;
        }
}

int main(int argc , char *argv[])
{
    int sock , client_sock , client_sock2 , read_size ;
    struct sockaddr_in server ,client;
    socklen_t c;
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    // if (sock == -1)
    //     printf("Could not create socket");
    bzero(&client , sizeof(client));
    // puts("Socket created");

    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons( FIRST );
    int first_bind , second_bind , third_bind;
    first_bind = bind(sock,(struct sockaddr *)&server , sizeof(server));
    // first_bind = connect(sock , (struct sockaddr *)&server , sizeof(server));
    //Bind
    // if(first_bind < 0){
    //     printf("khaaaar\n");
    //     exit(-1);
    // }
    printf("%d\n" , first_bind);
    if( first_bind >= 0) //in baraye avalin nafar mishe
    {
        struct sockaddr_in cli_adr , cli_adr2;
        printf("first person is connected. welcome \n");
        //Listen
        listen(sock , 3);
        int random_number1_1;
        int random_number1_2;
        int random_number1_3;
        //Accept and incoming connection
        puts("Waiting for incoming connections...\n");
        //c = sizeof(server);
        socklen_t size1 = sizeof(cli_adr);
        socklen_t size2 = sizeof(cli_adr2);
        //accept connection from an incoming client
        bzero(&cli_adr, sizeof(cli_adr));
        printf("before accept no 1\n");
        client_sock = accept(sock, (struct sockaddr *)&cli_adr,&size1);
        printf("some one connected to me NO1\n");
        client_sock2 = accept(sock, (struct sockaddr *)&cli_adr2, &size2);
        printf("some one connnected to me NO2\n");
        //if (client_sock > 0 && client_sock2 > 0)
        int i=0;
        for(i= 0 ; i < 10 ; i++){
            printf("ROUND NO %d\n",i);
            random_number1_1 = fork_func();
        // puts("Connection accepted");
        printf("kheili\n");

        write(client_sock , &random_number1_1 , sizeof(int));
        printf("kheili\n");

        write(client_sock2 , &random_number1_1 , sizeof(int));
        printf("kheili\n");

        read(client_sock , &random_number1_2 , sizeof(int));
        printf("kheili\n");

        read(client_sock2 , &random_number1_3 , sizeof(int));
        printf("kheili\n");

        printf("PERSON ONE \nnumber from connection one is : %d\n", random_number1_2);
        printf("PERSON ONE \nnumber from connection one is : %d\n", random_number1_3);

        // printf()
        choosing_winner(random_number1_1 , random_number1_2 , random_number1_3 , 1);
    }
    }
    else {
        int sock1;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_family = AF_INET;
        server.sin_port = htons( SEC );
        // int second_bind;
        second_bind = bind(sock,(struct sockaddr *)&server , sizeof(server));

        if( second_bind >= 0) //in baraye nafare dovom!
        {
            printf("second person is connected. welcome \n");
            //Listen
            listen(sock , 3);
            int random_number2_1;
            int random_number2_2;
            int random_number2_3;
            //Accept and incoming connection
            puts("Waiting for incoming connections...\n");
            //c = sizeof(struct sockaddr_in);
            //make a connection with port one!
            server.sin_addr.s_addr = INADDR_ANY;
            server.sin_family = AF_INET;
            server.sin_port = htons( FIRST );
            sock1 = socket(AF_INET, SOCK_STREAM,0);
            printf("salllllllllam %d\n",connect(sock1 , (struct sockaddr *)&server , sizeof(server)));
            socklen_t clilen;
            clilen = sizeof(client);
            //accept connection from an incoming client
            client_sock = accept(sock, (struct sockaddr *)&client, &clilen);
            printf("some one connected to me !\n");
            printf("%d\n",client_sock);
            // client_sock2 = accept(sock, (struct sockaddr *)&server, (socklen_t*)&c);
            //if (client_sock > 0)
            int i=0;
            for(i= 0 ; i < 10 ; i++){
                printf("ROUND NO %d\n",i);
                random_number2_2 = fork_func();

            write(client_sock , &random_number2_2 , sizeof(int));
            write(sock1 , &random_number2_2 , sizeof(int));
            read(client_sock , &random_number2_1 , sizeof(int));
            read(sock1 , &random_number2_3 , sizeof(int));
            printf("P2\nnumber from connection one is : %d\n", random_number2_1);
            printf("P2\nnumber from connection one is : %d\n", random_number2_3);
        // puts("Connection accepted");
            choosing_winner(random_number2_1 , random_number2_2 , random_number2_3 , 2);
        }


        }
        else {
            printf("third person is connected. welcome\n");
            int sock1 = socket(AF_INET, SOCK_STREAM, 0);
            int sock2 = socket(AF_INET, SOCK_STREAM, 0);
            struct sockaddr_in server1;
            struct sockaddr_in server2;
            // server.sin_addr.s_addr = INADDR_ANY;
            // server.sin_family = AF_INET;
            // server.sin_port = htons( 9212 );
            // int third_bind;
            //third_bind = bind(sock,(struct sockaddr *)&server , sizeof(server));
            //if( third_bind >= 0) {
                int random_number3_1;
                int random_number3_2;
                int random_number3_3;
                //connecting to others
                //connection with port one!
                server1.sin_addr.s_addr = INADDR_ANY;
                server1.sin_family = AF_INET;
                server1.sin_port = htons( FIRST );
                printf("RRRRRR%d\n",connect(sock1 , (struct sockaddr *)&server1 , sizeof(server1)));
                //connection with port two!
                server2.sin_addr.s_addr = INADDR_ANY;
                server2.sin_family = AF_INET;
                server2.sin_port = htons( SEC );
                printf("RRRRRR%d\n",connect(sock2 , (struct sockaddr *)&server2 , sizeof(server2)));
                //and send start button
                int i=0;
                for(i= 0 ; i < 10 ; i++){
                    printf("ROUND NO %d\n",i);
                random_number3_3 = fork_func();
                printf("WWWWWWw%d" , write(sock1, &random_number3_3, sizeof(int)));

                write(sock2, &random_number3_3, sizeof(int));
                read(sock1, &random_number3_1, sizeof(int));
                read(sock2,&random_number3_2, sizeof(int));
                printf("P3\nnumber from connection one is : %d\n", random_number3_1);
                printf("P3\nnumber from connection one is : %d\n", random_number3_2);

                choosing_winner(random_number3_1 , random_number3_2 , random_number3_3 , 3);
            }
        }

    }
    close(sock);
    close(first_bind);
    close(second_bind);
    close(third_bind);
    close(client_sock);
    close(client_sock2);
}
