#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <string>
#include <time.h> // clock_gettime
#include <limits.h> // LONG_MAX
#include <unistd.h> // argument parsing

#include <grpcpp/grpcpp.h>
#include "send_file.grpc.pb.h"
#include "exec.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientWriter;
using grpc::Status;
using namespace cs739;

#define MAXBUFSIZE 2097152 // 2MB
/* Protobuf ():
    bytes 	May contain any arbitrary sequence of bytes no longer than 2^32.
*/

class SendFileClient {
public:
    SendFileClient(std::shared_ptr<Channel> channel)
      : stub_(SendFile::NewStub(channel)) {}

    SendFileClient(std::shared_ptr<Channel> channel, char* filepath) 
     : stub_(SendFile::NewStub(channel)), filepath_(filepath) { }

    void send(std::ifstream& file) {
        ClientContext context;
        Reply reply;
        Data d;
        uint64_t count = 0;

        std::unique_ptr<ClientWriter<Data>> writer(
            stub_->Send(&context, &reply));

        // read file to buf and send it
        // https://en.cppreference.com/w/cpp/io/basic_istream/read
        file.seekg(0, std::ios::end);
        uint64_t filesize = file.tellg();
        file.seekg(0);
        uint64_t bufsize = std::min(filesize, (uint64_t)MAXBUFSIZE);
        
        std::string buf(bufsize, '\0');
        struct timespec t, u;
        clock_gettime(CLOCK_REALTIME, &t);

        while (file.read(&buf[0], bufsize)) {
            d.set_b(buf);
            if (!writer->Write(d))
                break;
            count += d.b().size();
        }
        if (file.eof()) {
            buf.resize(file.gcount());
            d.set_b(buf);
            writer->Write(d);
            count += d.b().size();
        }
        writer->WritesDone();
        Status status = writer->Finish();
        if (status.ok()) {
            clock_gettime(CLOCK_REALTIME, &u);
            std::cout << "Success sending data. stop timer and checksum...\n";
            std::stringstream md5cmd; 
            md5cmd << "md5sum " << filepath_;
            std::string c_md5 = exec(md5cmd.str().c_str()).substr(0, 32);
            std::string s_md5 = reply.md5sum();
            std::cout << "client: filesize=" << filesize << ", md5sum=" << c_md5 << "\n";
            std::cout << "server: filesize=" << reply.r() << ", md5sum=" << s_md5 << "\n";
            if (c_md5 != s_md5 || filesize != reply.r()) {
                std::cout << "Fail to send correct data.\n";
                return;
            }
            
            printf("round-trip time = %8lu ms.\n", ((u.tv_nsec - t.tv_nsec) / 1000000 + (u.tv_sec - t.tv_sec) * 1000));
        } else {
            std::cout << "Fail to send file\n";
        }
    }

private:
    std::unique_ptr<SendFile::Stub> stub_;
    char* filepath_;
};

void print_usage(char* proc_name = nullptr) {
    std::cout << (proc_name ? proc_name : "send_file_client") << " [-s <server_ip:port>] <file_to_be_send>\n";
}

int main(int argc, char** argv) {
    std::string server_addr = "localhost:53706"; // royal-09=128.105.37.149:53706; royal-##=128.105.37.(140+##)

    int opt;
    while ((opt = getopt(argc, argv, "hs:")) != -1) {
        switch (opt) {
            case 's':
                server_addr = optarg;
                break;
            case 'h':
                print_usage(argv[0]);
                exit(0);
            case '?':
            default:
                std::cerr << argv[0] << ": invalid argument\n";
                print_usage(argv[0]);
                exit(1);
        }
    }
    if (optind >= argc) {
        std::cerr << argv[0] << ": specify file\n";
        print_usage(argv[0]);
        exit(1);
    }
    std::ifstream file(argv[optind], std::ios::binary);
    SendFileClient client(grpc::CreateChannel(server_addr, grpc::InsecureChannelCredentials()), argv[optind]);
    client.send(file);
    file.close();

    return 0;
}
