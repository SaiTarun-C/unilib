#include "ml/dlib.hpp"

#ifdef UNILIB_DLIB_ENABLED
#include <dlib/dnn.h>
#include <dlib/image_io.h>
#include <dlib/image_processing.h>

namespace unilib::ml {

DlibWrapper::DlibWrapper() = default;

bool DlibWrapper::loadFaceDetector() {
    try {
        detector_ = dlib::get_frontal_face_detector();
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Failed to load face detector: " << e.what() << std::endl;
        return false;
    }
}

std::vector<dlib::rectangle> DlibWrapper::detectFaces(const std::string& image_path) {
    std::vector<dlib::rectangle> faces;
    try {
        dlib::array2d<dlib::rgb_pixel> img;
        dlib::load_image(img, image_path);
        faces = detector_(img);
    } catch (const std::exception& e) {
        std::cerr << "Face detection error: " << e.what() << std::endl;
    }
    return faces;
}

}  // namespace unilib::ml

#endif // UNILIB_DLIB_ENABLED
