// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: exchange_info.proto

#include "exchange_info.pb.h"
#include "exchange_info.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace cs739 {

static const char* ExchangeInfo_method_names[] = {
  "/cs739.ExchangeInfo/ExchangeInteger",
  "/cs739.ExchangeInfo/ExchangeDouble",
  "/cs739.ExchangeInfo/ExchangeString",
  "/cs739.ExchangeInfo/ExchangeComplex",
};

std::unique_ptr< ExchangeInfo::Stub> ExchangeInfo::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< ExchangeInfo::Stub> stub(new ExchangeInfo::Stub(channel, options));
  return stub;
}

ExchangeInfo::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_ExchangeInteger_(ExchangeInfo_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_ExchangeDouble_(ExchangeInfo_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_ExchangeString_(ExchangeInfo_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_ExchangeComplex_(ExchangeInfo_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status ExchangeInfo::Stub::ExchangeInteger(::grpc::ClientContext* context, const ::cs739::Integer& request, ::cs739::Integer* response) {
  return ::grpc::internal::BlockingUnaryCall< ::cs739::Integer, ::cs739::Integer, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_ExchangeInteger_, context, request, response);
}

void ExchangeInfo::Stub::async::ExchangeInteger(::grpc::ClientContext* context, const ::cs739::Integer* request, ::cs739::Integer* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::cs739::Integer, ::cs739::Integer, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ExchangeInteger_, context, request, response, std::move(f));
}

void ExchangeInfo::Stub::async::ExchangeInteger(::grpc::ClientContext* context, const ::cs739::Integer* request, ::cs739::Integer* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ExchangeInteger_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::cs739::Integer>* ExchangeInfo::Stub::PrepareAsyncExchangeIntegerRaw(::grpc::ClientContext* context, const ::cs739::Integer& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::cs739::Integer, ::cs739::Integer, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_ExchangeInteger_, context, request);
}

::grpc::ClientAsyncResponseReader< ::cs739::Integer>* ExchangeInfo::Stub::AsyncExchangeIntegerRaw(::grpc::ClientContext* context, const ::cs739::Integer& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncExchangeIntegerRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ExchangeInfo::Stub::ExchangeDouble(::grpc::ClientContext* context, const ::cs739::Double& request, ::cs739::Double* response) {
  return ::grpc::internal::BlockingUnaryCall< ::cs739::Double, ::cs739::Double, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_ExchangeDouble_, context, request, response);
}

void ExchangeInfo::Stub::async::ExchangeDouble(::grpc::ClientContext* context, const ::cs739::Double* request, ::cs739::Double* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::cs739::Double, ::cs739::Double, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ExchangeDouble_, context, request, response, std::move(f));
}

void ExchangeInfo::Stub::async::ExchangeDouble(::grpc::ClientContext* context, const ::cs739::Double* request, ::cs739::Double* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ExchangeDouble_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::cs739::Double>* ExchangeInfo::Stub::PrepareAsyncExchangeDoubleRaw(::grpc::ClientContext* context, const ::cs739::Double& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::cs739::Double, ::cs739::Double, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_ExchangeDouble_, context, request);
}

::grpc::ClientAsyncResponseReader< ::cs739::Double>* ExchangeInfo::Stub::AsyncExchangeDoubleRaw(::grpc::ClientContext* context, const ::cs739::Double& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncExchangeDoubleRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ExchangeInfo::Stub::ExchangeString(::grpc::ClientContext* context, const ::cs739::String& request, ::cs739::String* response) {
  return ::grpc::internal::BlockingUnaryCall< ::cs739::String, ::cs739::String, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_ExchangeString_, context, request, response);
}

void ExchangeInfo::Stub::async::ExchangeString(::grpc::ClientContext* context, const ::cs739::String* request, ::cs739::String* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::cs739::String, ::cs739::String, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ExchangeString_, context, request, response, std::move(f));
}

void ExchangeInfo::Stub::async::ExchangeString(::grpc::ClientContext* context, const ::cs739::String* request, ::cs739::String* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ExchangeString_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::cs739::String>* ExchangeInfo::Stub::PrepareAsyncExchangeStringRaw(::grpc::ClientContext* context, const ::cs739::String& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::cs739::String, ::cs739::String, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_ExchangeString_, context, request);
}

::grpc::ClientAsyncResponseReader< ::cs739::String>* ExchangeInfo::Stub::AsyncExchangeStringRaw(::grpc::ClientContext* context, const ::cs739::String& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncExchangeStringRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ExchangeInfo::Stub::ExchangeComplex(::grpc::ClientContext* context, const ::cs739::Complex& request, ::cs739::Complex* response) {
  return ::grpc::internal::BlockingUnaryCall< ::cs739::Complex, ::cs739::Complex, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_ExchangeComplex_, context, request, response);
}

void ExchangeInfo::Stub::async::ExchangeComplex(::grpc::ClientContext* context, const ::cs739::Complex* request, ::cs739::Complex* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::cs739::Complex, ::cs739::Complex, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ExchangeComplex_, context, request, response, std::move(f));
}

void ExchangeInfo::Stub::async::ExchangeComplex(::grpc::ClientContext* context, const ::cs739::Complex* request, ::cs739::Complex* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ExchangeComplex_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::cs739::Complex>* ExchangeInfo::Stub::PrepareAsyncExchangeComplexRaw(::grpc::ClientContext* context, const ::cs739::Complex& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::cs739::Complex, ::cs739::Complex, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_ExchangeComplex_, context, request);
}

::grpc::ClientAsyncResponseReader< ::cs739::Complex>* ExchangeInfo::Stub::AsyncExchangeComplexRaw(::grpc::ClientContext* context, const ::cs739::Complex& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncExchangeComplexRaw(context, request, cq);
  result->StartCall();
  return result;
}

ExchangeInfo::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ExchangeInfo_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ExchangeInfo::Service, ::cs739::Integer, ::cs739::Integer, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ExchangeInfo::Service* service,
             ::grpc::ServerContext* ctx,
             const ::cs739::Integer* req,
             ::cs739::Integer* resp) {
               return service->ExchangeInteger(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ExchangeInfo_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ExchangeInfo::Service, ::cs739::Double, ::cs739::Double, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ExchangeInfo::Service* service,
             ::grpc::ServerContext* ctx,
             const ::cs739::Double* req,
             ::cs739::Double* resp) {
               return service->ExchangeDouble(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ExchangeInfo_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ExchangeInfo::Service, ::cs739::String, ::cs739::String, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ExchangeInfo::Service* service,
             ::grpc::ServerContext* ctx,
             const ::cs739::String* req,
             ::cs739::String* resp) {
               return service->ExchangeString(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ExchangeInfo_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ExchangeInfo::Service, ::cs739::Complex, ::cs739::Complex, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ExchangeInfo::Service* service,
             ::grpc::ServerContext* ctx,
             const ::cs739::Complex* req,
             ::cs739::Complex* resp) {
               return service->ExchangeComplex(ctx, req, resp);
             }, this)));
}

ExchangeInfo::Service::~Service() {
}

::grpc::Status ExchangeInfo::Service::ExchangeInteger(::grpc::ServerContext* context, const ::cs739::Integer* request, ::cs739::Integer* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ExchangeInfo::Service::ExchangeDouble(::grpc::ServerContext* context, const ::cs739::Double* request, ::cs739::Double* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ExchangeInfo::Service::ExchangeString(::grpc::ServerContext* context, const ::cs739::String* request, ::cs739::String* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ExchangeInfo::Service::ExchangeComplex(::grpc::ServerContext* context, const ::cs739::Complex* request, ::cs739::Complex* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace cs739

