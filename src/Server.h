/*************************************************************************
	> File Name:    Server.h
	> Author:       sk 
	> Mail:         skctvc15@gmail.com
	> Created Time: 2014年11月05日 星期三 19时08分56秒
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <iostream>
#include <sstream>
#include <memory>
#include "./Request/HTTPRequest.h"
#include "./Response/HTTPResponse.h"

#define SERV_ROOT "../www"
#define MAX_EVENTS 1024

class HTTPServer {
public: 
    HTTPServer();
    HTTPServer( int );
    ~HTTPServer();

    static void init_daemon(const char*,int);

    int run( void );
    int setPort( size_t );
    int initSocket( void );

    int recvRequest( void );
    int handleRequest( void );
    int parseRequest( void );
    int processRequest( void );

    int prepareResponse( void );
    int sendResponse( void );
    void init_epfd( int );
    void init();

    int handleGET();
    void handlePUT();

    static void * worker(void *);   //worker thread func
private:


    string getMimeType( string );
    static const int buf_size = 512;

    size_t servPort;
    int listenfd,m_sockfd ;

    socklen_t clilen;
    struct sockaddr_in servaddr , cliaddr;

    static int m_epollfd;
    struct epoll_event ev;
    struct epoll_event evlist[MAX_EVENTS];

    string m_url;
    string m_mimeType;
    std::shared_ptr<HttpRequest>  m_httpRequest;
    std::shared_ptr<HttpResponse> m_httpResponse;

};
#endif  /*_HTTP_SERVER_H_*/
