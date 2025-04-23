#pragma once

#include <dlib/mlp.h>
#include <dlib/svm.h>
#include <dlib/data_io.h>
#include <iostream>
#include <vector>

namespace unilib::ml {

// Example: MLP (Multi-layer Perceptron) Neural Network Wrapper using Dlib
class MLPModel {
public:
    MLPModel() {
        // Define the structure of the neural network (input, hidden, output layers)
        net_.set_layer_sizes(2, 3, 1);
    }

    void Train(const std::vector<std::vector<double>>& inputs, const std::vector<double>& outputs) {
        dlib::matrix<double> X(inputs.size(), inputs[0].size());
        dlib::matrix<double> y(outputs.size(), 1);

        for (size_t i = 0; i < inputs.size(); ++i) {
            for (size_t j = 0; j < inputs[i].size(); ++j) {
                X(i, j) = inputs[i][j];
            }
            y(i) = outputs[i];
        }

        // Train the network with backpropagation
        dlib::sgd sol;
        net_.train(X, y, sol);
    }

    std::vector<double> Predict(const std::vector<std::vector<double>>& inputs) {
        dlib::matrix<double> X(inputs.size(), inputs[0].size());
        for (size_t i = 0; i < inputs.size(); ++i) {
            for (size_t j = 0; j < inputs[i].size(); ++j) {
                X(i, j) = inputs[i][j];
            }
        }

        std::vector<double> predictions;
        for (size_t i = 0; i < X.nr(); ++i) {
            predictions.push_back(net_(X(i)));
        }

        return predictions;
    }

private:
    dlib::mlp::kernel_2d net_;
};

// Support for SVM using Dlib (Support Vector Machine)
class SVMModel {
public:
    SVMModel() : svm_(dlib::svm_c_trainer<dlib::linear_kernel<dlib::matrix<double>>>()), model_trained_(false) {}

    void Train(const std::vector<std::vector<double>>& inputs, const std::vector<double>& labels) {
        dlib::matrix<double> X(inputs.size(), inputs[0].size());
        dlib::matrix<double> y(labels.size(), 1);

        for (size_t i = 0; i < inputs.size(); ++i) {
            for (size_t j = 0; j < inputs[i].size(); ++j) {
                X(i, j) = inputs[i][j];
            }
            y(i) = labels[i];
        }

        model_ = svm_.train(X, y);
        model_trained_ = true;
    }

    std::vector<double> Predict(const std::vector<std::vector<double>>& inputs) {
        if (!model_trained_) {
            throw std::runtime_error("SVM model has not been trained yet");
        }

        dlib::matrix<double> X(inputs.size(), inputs[0].size());
        for (size_t i = 0; i < inputs.size(); ++i) {
            for (size_t j = 0; j < inputs[i].size(); ++j) {
                X(i, j) = inputs[i][j];
            }
        }

        std::vector<double> predictions;
        for (size_t i = 0; i < X.nr(); ++i) {
            predictions.push_back(model_(X(i)));
        }

        return predictions;
    }

private:
    dlib::svm_c_trainer<dlib::linear_kernel<dlib::matrix<double>>> svm_;
    dlib::decision_function<dlib::linear_kernel<dlib::matrix<double>>> model_;
    bool model_trained_;
};

} // namespace unilib::ml
