#include <iostream>
#include <memory>
#include <string>
#include <time.h> // clock_gettime
#include <limits.h> // LONG_MAX

#include <grpcpp/grpcpp.h>
#include "exchange_info.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using namespace cs739;

/*
    Files in include/ changed:
*/

/*
    In include/grpcpp/impl/codegen/proto_utils.h:
    // This class provides a protobuf serializer. It translates between protobuf
    // objects and grpc_byte_buffers. More information about SerializationTraits can
    // be found in include/grpcpp/impl/codegen/serialization_traits.h.
    template <class T>
    class SerializationTraits<
        T, typename std::enable_if<
            std::is_base_of<grpc::protobuf::MessageLite, T>::value>::type>
*/

/*
    call stack:
    SerializationTraits<M, void>::Serialize (this is in include/grpcpp/impl/codegen/proto_utils.h)
    CallOpSendMessage::serializer_
    (somehow) CallOpSendMessage::AddOp (call serializer_)
    CallOpSendMessage::SendMessagePtr (set serializer_)
    CallOpSet::SendMessagePtr
    BlockingUnaryCallImpl::(constructor)
    BlockingUnaryCall::(constructor)
    ExchangeInfo::Stub::ExchangeInteger
    ExchangeInfoClient::xchg_int
    main
*/

/*
    Inheritance: ::cs739::Integer -> google::protobuf::Message -> google::protobuf::MessageLite
*/

class ExchangeInfoClient {
public:
    ExchangeInfoClient(std::shared_ptr<Channel> channel)
      : stub_(ExchangeInfo::NewStub(channel)) {}


    int32_t xchg_int(const int32_t& value) {
        Integer in, out;
        ClientContext context;

        in.set_data(value);

        struct timespec t, u; 
        clock_gettime(CLOCK_REALTIME, &t);
        Status status = stub_->ExchangeInteger(&context, in, &out);
        clock_gettime(CLOCK_REALTIME, &u);
        std::cout << "Roundtrip takes: " << ((u.tv_nsec - t.tv_nsec) + (u.tv_sec - t.tv_sec) * 1e9) << "ns. \n";

        if (status.ok()) {
            return out.data();
        } else {
            std::cerr << status.error_code() << ": " << status.error_message() << std::endl;
            return INT_MIN;
        }
    }
    double xchg_double(const double& value) {
        Double in, out;
        ClientContext context;

        in.set_data(value);
        
        struct timespec t, u; 
        clock_gettime(CLOCK_REALTIME, &t);
        Status status = stub_->ExchangeDouble(&context, in, &out);
        clock_gettime(CLOCK_REALTIME, &u);
        std::cout << "Roundtrip takes: " << ((u.tv_nsec - t.tv_nsec) + (u.tv_sec - t.tv_sec) * 1e9) << "ns. \n";

        if (status.ok()) {
            return out.data();
        } else {
            std::cerr << status.error_code() << ": " << status.error_message() << std::endl;
            return -1.0;
        }
    }

    std::string xchg_string(const std::string& value) {
        String in, out;
        ClientContext context;

        in.set_data(value);

        struct timespec t, u; 
        clock_gettime(CLOCK_REALTIME, &t);
        Status status = stub_->ExchangeString(&context, in, &out);
        clock_gettime(CLOCK_REALTIME, &u);
        std::cout << "Roundtrip takes: " << ((u.tv_nsec - t.tv_nsec) + (u.tv_sec - t.tv_sec) * 1e9) << "ns. \n";

        if (status.ok()) {
            return out.data();
        } else {
            std::cerr << status.error_code() << ": " << status.error_message() << std::endl;
            return "FAIL!";
        }
    }

    void xchg_complex(const int32_t& i, const double& d, const std::string& s,
                    int32_t* ii, double* dd, std::string* ss) {
        Complex in, out;
        ClientContext context;

        in.set_i(i);
        in.set_d(d);
        in.set_s(s);

        struct timespec t, u; 
        clock_gettime(CLOCK_REALTIME, &t);
        Status status = stub_->ExchangeComplex(&context, in, &out);
        clock_gettime(CLOCK_REALTIME, &u);
        std::cout << "Roundtrip takes: " << ((u.tv_nsec - t.tv_nsec) + (u.tv_sec - t.tv_sec) * 1e9) << "ns. \n";
        
        if (status.ok()) {
            *ii = out.i();
            *dd = out.d();
            *ss = out.s();
        } else {
            std::cerr << status.error_code() << ": " << status.error_message() << std::endl;
        }
        return;
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
    
    std::cout << "vv[Integer]\n";
    int32_t i = 5;
    int32_t ii = client.xchg_int(i);

    std::cout << "vv[Double]\n";
    double d = 3.706;
    double dd = client.xchg_double(d);

    std::cout << "vv[String - 7 chars]\n";
    std::string s = "Madison";
    std::string ss = client.xchg_string(s);

    std::cout << "vv[String - 100 chars]\n";
    std::string longs = "F2cSJuSQfHR00dl6s6KH"
                    "6lquRIhBvpQic6VgM6nZ"
                    "D3vOkkOGE6qzs5JiLypr"
                    "0jffOHXyjCSJuOtFqAtO"
                    "OHuvgKrZnlAoEYKyVQT7";
    std::string longss = client.xchg_string(longs);

    std::cout << "vv[Complex]\n";
    int comp_i;
    double comp_d;
    std::string comp_s;
    client.xchg_complex(i, d, longs, &comp_i, &comp_d, &comp_s);
    
    std::cout << comp_i << comp_d << comp_s << std::endl;
    // std::cout << "original: " << i << "\t" << d << "\t" << s << std::endl;
    // std::cout << "return: " << ii << "\t" << dd << "\t" << ss << std::endl;

    return 0;
}
