#include "ml/tensorflow.hpp"

#ifdef UNILIB_TENSORFLOW_ENABLED
#include <tensorflow/core/public/session.h>
#include <tensorflow/core/platform/env.h>

using namespace tensorflow;

namespace unilib::ml {

TensorFlowWrapper::TensorFlowWrapper() {
    Status status = NewSession(SessionOptions(), &session_);
    if (!status.ok()) {
        throw std::runtime_error("Failed to create TensorFlow session: " + status.ToString());
    }
}

TensorFlowWrapper::~TensorFlowWrapper() {
    if (session_) {
        session_->Close();
        delete session_;
        session_ = nullptr;
    }
}

bool TensorFlowWrapper::loadGraph(const std::string& graph_path) {
    GraphDef graph_def;
    Status status = ReadBinaryProto(Env::Default(), graph_path, &graph_def);
    if (!status.ok()) {
        std::cerr << "Error reading graph: " << status.ToString() << "\n";
        return false;
    }

    status = session_->Create(graph_def);
    if (!status.ok()) {
        std::cerr << "Error creating graph: " << status.ToString() << "\n";
        return false;
    }
    return true;
}

std::vector<Tensor> TensorFlowWrapper::run(const std::vector<std::pair<std::string, Tensor>>& inputs,
                                           const std::vector<std::string>& output_tensor_names) {
    std::vector<Tensor> outputs;
    Status status = session_->Run(inputs, output_tensor_names, {}, &outputs);
    if (!status.ok()) {
        throw std::runtime_error("Error during TensorFlow run: " + status.ToString());
    }
    return outputs;
}

}  // namespace unilib::ml

#endif // UNILIB_TENSORFLOW_ENABLED
