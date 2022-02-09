#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "exchange_info.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using namespace cs739;

class ExchangeInfoClient {
public:
    ExchangeInfoClient(std::shared_ptr<Channel> channel)
      : stub_(ExchangeInfo::NewStub(channel)) {}

    int32_t ExchangeInt(const int32_t& value) {
        Integer in, out;
        ClientContext context;

        in.set_data(value);
        Status status = stub_->ExchangeInteger(&context, in, &out);

        if (status.ok()) {
            return out.data();
        } else {
            std::cerr << status.error_code() << ": " << status.error_message() << std::endl;
            return INT_MIN;
        }
    }

private:
    std::unique_ptr<ExchangeInfo::Stub> stub_;
};

int main(int argc, char** argv) {
    std::string server_addr = "localhost:53706"; // royal-09=128.105.37.149:53706; royal-##=128.105.37.(140+##)

    if (argc > 1) {
        server_addr = argv[1];
    }

    ExchangeInfoClient client(grpc::CreateChannel(server_addr, grpc::InsecureChannelCredentials()));
    int32_t value = 1136;
    int32_t reply = client.ExchangeInt(value);
    std::cout << "ExchangeInt: input " << value << ", output " << reply << std::endl;

    return 0;
}
