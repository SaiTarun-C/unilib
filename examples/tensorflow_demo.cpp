//Purpose: Performs inference using a TensorFlow model.

#include <tensorflow/core/public/session.h>
#include <tensorflow/core/protobuf/meta_graph.pb.h>
#include <tensorflow/core/platform/env.h>

int main() {
    tensorflow::Session* session;
    tensorflow::Status status = tensorflow::NewSession(tensorflow::SessionOptions(), &session);
    if (!status.ok()) {
        std::cerr << "Error creating session: " << status.ToString() << std::endl;
        return -1;
    }

    tensorflow::GraphDef graph_def;
    status = ReadBinaryProto(tensorflow::Env::Default(), "model.pb", &graph_def);
    if (!status.ok()) {
        std::cerr << "Error loading graph: " << status.ToString() << std::endl;
        return -1;
    }

    status = session->Create(graph_def);
    if (!status.ok()) {
        std::cerr << "
::contentReference[oaicite:0]{index=0}
 
