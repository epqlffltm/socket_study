// chapter01/hello_server.cpp

/*
 * 단방향 hello 서버
 * 접속한 클라이언트에게 문자열 하나를 보내고 종료한다.
 */

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <iostream>

// 소멸 시 fd를 닫는다.
class UniqueFd {
public:
    explicit UniqueFd(int fd);
    ~UniqueFd();

    UniqueFd(const UniqueFd&) = delete;
    UniqueFd& operator=(const UniqueFd&) = delete;

    int get() const;
    bool valid() const;

private:
    int fd_;
};

void error_handling(const char* message);

int main(int argc, char* argv[]) {
    const char message[] = "Hello World!";

    if (argc != 2) {
        std::cerr << "usage : " << argv[0] << " <port>" << std::endl;
        std::exit(1);
    }

    UniqueFd serv_sock(::socket(PF_INET, SOCK_STREAM, 0));
    if (!serv_sock.valid())
        error_handling("socket");

    const int optval = 1;
    ::setsockopt(serv_sock.get(), SOL_SOCKET, SO_REUSEADDR,&optval, sizeof(optval));

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = ::htonl(INADDR_ANY);
    serv_addr.sin_port = ::htons(atoi(argv[1]));

    if (::bind(serv_sock.get(), (sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind");

    if (::listen(serv_sock.get(), 5) == -1)
        error_handling("listen");

    sockaddr_in clnt_addr{};
    socklen_t clnt_addr_size = sizeof(clnt_addr);

    UniqueFd clnt_sock(::accept(serv_sock.get(),
                                (sockaddr*)&clnt_addr, &clnt_addr_size));
    if (!clnt_sock.valid())
        error_handling("accept");

    ::write(clnt_sock.get(), message, sizeof(message) - 1);

    return 0;
}

UniqueFd::UniqueFd(int fd) : fd_(fd) {}

UniqueFd::~UniqueFd() {
    if (fd_ >= 0)
        ::close(fd_);
}

int UniqueFd::get() const {
    return fd_;
}

bool UniqueFd::valid() const {
    return fd_ >= 0;
}

void error_handling(const char* message) {
    std::cerr << message << ": " << std::strerror(errno) << std::endl;
    std::exit(1);
}