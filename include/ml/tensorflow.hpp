#pragma once

#include <tensorflow/core/public/session.h>
#include <tensorflow/core/protobuf/meta_graph.pb.h>
#include <iostream>
#include <memory>
#include <vector>

namespace unilib::ml {

class TensorFlowModel {
public:
    TensorFlowModel(const std::string& model_path) {
        // Load the model
        tensorflow::Status status = LoadModel(model_path);
        if (!status.ok()) {
            std::cerr << "Failed to load model: " << status.ToString() << std::endl;
            throw std::runtime_error("Model loading failed");
        }
    }

    ~TensorFlowModel() {
        if (session_) {
            session_->Close();
        }
    }

    tensorflow::Status RunInference(const std::vector<tensorflow::Tensor>& inputs,
                                    std::vector<tensorflow::Tensor>& outputs) {
        if (!session_) {
            return tensorflow::Status(tensorflow::error::INVALID_ARGUMENT, "Session is not initialized.");
        }

        // Run inference
        return session_->Run(inputs, output_names_, {}, &outputs);
    }

private:
    tensorflow::Status LoadModel(const std::string& model_path) {
        tensorflow::GraphDef graph_def;
        tensorflow::Status status = tensorflow::ReadBinaryProto(tensorflow::Env::Default(), model_path, &graph_def);
        if (!status.ok()) {
            return status;
        }

        session_ = std::make_unique<tensorflow::Session>(tensorflow::NewSession(tensorflow::SessionOptions()));
        if (!session_) {
            return tensorflow::Status(tensorflow::error::UNKNOWN, "Failed to create TensorFlow session.");
        }

        status = session_->Create(graph_def);
        if (!status.ok()) {
            return status;
        }

        return tensorflow::Status::OK();
    }

    std::unique_ptr<tensorflow::Session> session_;
    std::vector<std::string> output_names_ = {"output_tensor"}; // Change this as per your model
};

} // namespace unilib::ml
