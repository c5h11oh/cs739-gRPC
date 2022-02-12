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


    int32_t xchg_int(const int32_t& value, bool roundtrip = false) {
        Integer in, out;
        ClientContext context;

        in.set_data(value);

        Status status;
        if (roundtrip) { 
            struct timespec t, u; 
            clock_gettime(CLOCK_MONOTONIC, &t);
            status = stub_->ExchangeInteger(&context, in, &out);
            clock_gettime(CLOCK_MONOTONIC, &u);
            std::cout << "Roundtrip takes: " << ((u.tv_nsec - t.tv_nsec) + (u.tv_sec - t.tv_sec) * 1000000000) << "ns. \n";
        } else {
            status = stub_->ExchangeInteger(&context, in, &out);
        }
        
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
        
        // struct timespec t, u; 
        // clock_gettime(CLOCK_MONOTONIC, &t);
        Status status = stub_->ExchangeDouble(&context, in, &out);
        // clock_gettime(CLOCK_MONOTONIC, &u);
        // std::cout << "Roundtrip takes: " << ((u.tv_nsec - t.tv_nsec) + (u.tv_sec - t.tv_sec) * 1e9) << "ns. \n";

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

        // struct timespec t, u; 
        // clock_gettime(CLOCK_MONOTONIC, &t);
        Status status = stub_->ExchangeString(&context, in, &out);
        // clock_gettime(CLOCK_MONOTONIC, &u);
        // std::cout << "Roundtrip takes: " << ((u.tv_nsec - t.tv_nsec) + (u.tv_sec - t.tv_sec) * 1e9) << "ns. \n";

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

        // struct timespec t, u; 
        // clock_gettime(CLOCK_MONOTONIC, &t);
        Status status = stub_->ExchangeComplex(&context, in, &out);
        // clock_gettime(CLOCK_MONOTONIC, &u);
        // std::cout << "Roundtrip takes: " << ((u.tv_nsec - t.tv_nsec) + (u.tv_sec - t.tv_sec) * 1e9) << "ns. \n";
        
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

std::string long_str = 
    "Ncgf9Xt9iQspMIssG4dJBbhM6iXUf2tGhZvVoOJtaP5ioaSy0FkjSBYbVO6BuLNb79gAAsYAfpYuMyTmnzqO3bWGl9"
    "J0UwT0ksCUXDFXkJGBOToX6hGvxcCBZK9ZYQx7IJORxRYZ8e1xLJ1YyeMB5fk8I6UiMdurCpSzdYb16quPnt4mpBGn"
    "MyKESi9JrEOMF6jdnn6WdL6iHLhOTOIagoOmLeg6w3eEm6mfdYyuInWdMKOX6JVfsohR9ZEdbh0vD4j72eAHPnMi7t"
    "NUMHEi69MrJ92WCFYTmCMdVWkJ2U67tv6AdL73ZhTFayQ3UWuNR0w0Tq8emAnVmxMnYJM5LIXaaAu85YEipy1WTqW9"
    "XYUHnNRrtBsyiZWacHS6eLEuz37mubiAis9nXH2KQqzoRRXLEdVSk0Agbbuwi1MOkRo5S9ZNqidKONpuOIN0PAKrXM"
    "w4eWt1cEJBvpWXWi4W4bTQ6H2BFaiXm8h1yK3gYEMDa2MWEpk9cprwDzFziGnftNzOnLOndTrsMtJozpZ9h7ywf90P"
    "mnfsKP19LDdJPS8NNQRF2hifvPjhC9OSgmpwT43dFZ8Hqw5uQL9oAgRjwzgHv9pKEy3m0yTk0qerlTaQKDN8Icfkbv"
    "g5gPkoTRrvndr9jDpbvL6FoVkg2M6fBMNCekX1L9iH7MHxOlFdMKjPUCR1ahJK1o73T9pouq5q4sOqA5FtjMUK8l36"
    "WcMKz8JPzyuOBFZZVjLZmvtJYWcPmQv4qIGDUDRtFmVqN4cocVJGpuf1uarE0SpuyHrFd3AT4kb02VyaRIzSJuW06u"
    "Ew9LSp847uAEj3fp0VSsSBdpsNg1wKdD1ix0xcINXenXDqJcWwppMuDqsaOhhMw7TINNH0jdygX8toOKYzvDpaFQud"
    "zweWQf4Tv3EWaJKXioCUXtkUvcGmiBU4SHBM44eHulgsL5NWgznDFovL0kmgyNRSOT4pFsRAGBdlzSjJFXecjN5TtH"
    "LW0YSEWF1LomlFxvATZAyarypqTSvSJPzHJVfqp8yr6KeAGxVAoKOkmvw4Lqeh4fKuJDp39A9kDt8dsgCCyDukjVjy"
    "9E7HeoiH0y37qnwTcF20CxDdQnpfTptxqP717ckpjgsBx6X3CVZTlTNagHgzBR1LePsarw8N8rk2wNGBybI3Hwgja9"
    "F0gCXw8jYFD5hVtdJXhIWcLWvrCPAuI9hsEeRqUg5dsWQPJ0PTeUx04y49CESPIPmqdvoeOKtOn2opNojxo0WW7bwu"
    "N2vFIUHMSO5iVhV96mDjlQKiHRo4EjXac6eP635YHakNitqWgBjaTIFBgAwGqBQWT5DEQ2W8uj2vkbeZvmXcEWk49J"
    "H1CcNdnWN41iXvqKtV1XIjn8UXXq7x8R31CmOb3POQ9p0xZxoJepUfWb6oi7cC6ywAKa0GZIofjkkcJhqEdEadFlD6";


int main(int argc, char** argv) {
    std::string server_addr = "localhost:53706"; // royal-09=128.105.37.149:53706; royal-##=128.105.37.(140+##)

    if (argc > 1) {
        server_addr = argv[1];
    }

    std::cout << "Connecting to server " << server_addr << std::endl << std::endl;
    ExchangeInfoClient client(grpc::CreateChannel(server_addr, grpc::InsecureChannelCredentials()));
    
    // only test marshal on localhost
    if (argc == 1) { 
        std::cout << "Marshal and unmarshal...\n";
        std::cout << "[Integer]\n";
        int32_t i = 5, ii;
        for (int j = 0; j < 5; ++j)
            ii = client.xchg_int(i, false);
        std::cout << "\n";

        std::cout << "[Double]\n";
        double d = 3.706;
        for (int j = 0; j < 5; ++j)
            double dd = client.xchg_double(d);
        std::cout << "\n";

        std::cout << "[String - 10 chars]\n";
        std::string s = long_str.substr(0, 10);
        for (int j = 0; j < 5; ++j)
            std::string ss = client.xchg_string(s);
        std::cout << "\n";

        std::cout << "[String - 1000 chars]\n";
        std::string longs = long_str.substr(0, 1000);
        for (int j = 0; j < 5; ++j)
            std::string longss = client.xchg_string(longs);
        std::cout << "\n";

        std::cout << "[Complex]\n";
        int comp_i;
        double comp_d;
        std::string comp_s;
        for (int j = 0; j < 5; ++j)
            client.xchg_complex(i, d, s, &comp_i, &comp_d, &comp_s);
        std::cout << "\n";
        
        // std::cout << comp_i << comp_d << comp_s << std::endl;
        // std::cout << "original: " << i << "\t" << d << "\t" << s << std::endl;
        // std::cout << "return: " << ii << "\t" << dd << "\t" << ss << std::endl;
    }

    // test round trip
    {
        std::cout << "Roundtrip...\n";
        std::cout << "[Integer]\n";
        int32_t i = 5, ii;
        for (int j = 0; j < 5; ++j)
            ii = client.xchg_int(i, true);
        std::cout << "\n";
        // TODO: req & resp time; breakdown.
    }

    return 0;
}
