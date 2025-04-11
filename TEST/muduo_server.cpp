#include<muduo/net/TcpServer.h>
#include<muduo/net/EventLoop.h>
#include<iostream>
#include<functional>
#include<string>
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;

class ChatServer
{
public:
    ChatServer(EventLoop *loop,const InetAddress &listenAddr,const string &nameArg)
    :_server(loop,listenAddr,nameArg),_loop(loop)
    {
        //给服务器注册用户链接的创建和断开回调
        _server.setConnectionCallback(std::bind(&ChatServer::onConnection,this,_1));
        
        //给服务器注册用户读写回调
        _server.setMessageCallback(std::bind(&ChatServer::onMessage,this,_1,_2,_3));    
        
        //设服务器端的线程数量
        _server.setThreadNum(4);
    }

    //开启事件循环
    void start(){
        _server.start();
    }

private:
    //处理链接创建和断开
    void onConnection(const TcpConnectionPtr &conn){
        if(conn->connected())
        {
            cout<<conn->peerAddress().toIpPort()<<"->"<<conn->localAddress().toIpPort()<<"state:online"<<endl;
        }
        else
        {
            cout<<conn->peerAddress().toIpPort()<<"->"<<conn->localAddress().toIpPort()<<"state:offline"<<endl;
            conn->shutdown();
            _loop->quit();
        }
    }
    
    
    //处理读写事件
    void onMessage(const TcpConnectionPtr &conn,//链接
                    Buffer *buffer,//缓冲区
                    Timestamp time)//接收数据的时间信息
    {
        string buf=buffer->retrieveAllAsString();
        cout<<"recv data:"<<buf<<"time:"<<time.toString()<<endl;
        conn->send(buf);
    }


    TcpServer _server;
    EventLoop *_loop;
};

int main()
{
    EventLoop loop;
    InetAddress addr("127.0.0.1",6000);
    ChatServer server(&loop,addr,"ChatServer");

    server.start();//listenfd,epoll
    loop.loop();//epoll_wait以阻塞方式等待新用户链接，已连接用户的读写事件等

    return 0;
}
