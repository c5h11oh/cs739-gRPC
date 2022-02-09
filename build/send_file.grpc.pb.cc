// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: send_file.proto

#include "send_file.pb.h"
#include "send_file.grpc.pb.h"

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

static const char* SendFile_method_names[] = {
  "/cs739.SendFile/Send",
};

std::unique_ptr< SendFile::Stub> SendFile::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< SendFile::Stub> stub(new SendFile::Stub(channel, options));
  return stub;
}

SendFile::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_Send_(SendFile_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::CLIENT_STREAMING, channel)
  {}

::grpc::ClientWriter< ::cs739::Data>* SendFile::Stub::SendRaw(::grpc::ClientContext* context, ::cs739::Reply* response) {
  return ::grpc::internal::ClientWriterFactory< ::cs739::Data>::Create(channel_.get(), rpcmethod_Send_, context, response);
}

void SendFile::Stub::async::Send(::grpc::ClientContext* context, ::cs739::Reply* response, ::grpc::ClientWriteReactor< ::cs739::Data>* reactor) {
  ::grpc::internal::ClientCallbackWriterFactory< ::cs739::Data>::Create(stub_->channel_.get(), stub_->rpcmethod_Send_, context, response, reactor);
}

::grpc::ClientAsyncWriter< ::cs739::Data>* SendFile::Stub::AsyncSendRaw(::grpc::ClientContext* context, ::cs739::Reply* response, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncWriterFactory< ::cs739::Data>::Create(channel_.get(), cq, rpcmethod_Send_, context, response, true, tag);
}

::grpc::ClientAsyncWriter< ::cs739::Data>* SendFile::Stub::PrepareAsyncSendRaw(::grpc::ClientContext* context, ::cs739::Reply* response, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncWriterFactory< ::cs739::Data>::Create(channel_.get(), cq, rpcmethod_Send_, context, response, false, nullptr);
}

SendFile::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      SendFile_method_names[0],
      ::grpc::internal::RpcMethod::CLIENT_STREAMING,
      new ::grpc::internal::ClientStreamingHandler< SendFile::Service, ::cs739::Data, ::cs739::Reply>(
          [](SendFile::Service* service,
             ::grpc::ServerContext* ctx,
             ::grpc::ServerReader<::cs739::Data>* reader,
             ::cs739::Reply* resp) {
               return service->Send(ctx, reader, resp);
             }, this)));
}

SendFile::Service::~Service() {
}

::grpc::Status SendFile::Service::Send(::grpc::ServerContext* context, ::grpc::ServerReader< ::cs739::Data>* reader, ::cs739::Reply* response) {
  (void) context;
  (void) reader;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace cs739
