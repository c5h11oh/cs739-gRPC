#include <iostream>
#include <memory>

#include <grpc/grpc.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include "exchange_info.grpc.pb.h"
#include "exchange_info.pb.h"

using namespace cs739;
using namespace grpc;


class ExchangeInfoServerImpl final : public cs739::ExchangeInfo::Service {
public:
    explicit ExchangeInfoServerImpl() {}
    
    Status ExchangeInteger(ServerContext* context, const Integer* in, Integer* out) {
        std::cout << "^v [Integer]\n";
        out->set_data(in->data() + 1);
        return Status::OK;
    }

    Status ExchangeDouble(ServerContext* context, const Double* in, Double* out) {
        std::cout << "^v [Double]\n";
        out->set_data(in->data() + 1.0);
        return Status::OK;
    }

    Status ExchangeString(ServerContext* context, const String* in, String* out) {
        std::cout << "^v [String]\n";
        std::string str = in->data();
        for (char& c : str) {
            c = c + 1;
        }
        out->set_data(str);
        return Status::OK;
    }

    Status ExchangeComplex(ServerContext* context, const Complex* in, Complex* out) {
        std::cout << "^v [Complex]\n";
        int32_t i = in->i();
        double d = in->d();
        std::string s = in->s();
        
        out->set_i(2357);
        out->set_d(0.2357);
        out->set_s("Madison, Wisconsin");
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:53706");
    ExchangeInfoServerImpl service;
    
    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server ExchangeInfoServerImpl listening on " << server_address << std::endl;
    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();
    
    return 0;
}