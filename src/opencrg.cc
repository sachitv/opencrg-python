#include "opencrg.h"

#include <iostream>
#include <stdexcept>

extern "C" {
    #include <crgBaseLib.h>
}

namespace opencrg {
OpenCRG::OpenCRG(const std::string& crg_file) {
    // Load the file.
    data_set_id_ = crgLoaderReadFile(crg_file.c_str());
    if (data_set_id_ <= 0)
    {
        throw std::runtime_error("Failed to read " + crg_file);
    }

    // Check CRG data for consistency and accuracy.
    if ( !crgCheck( data_set_id_ ) )
    {
        throw std::runtime_error("could not validate crg data in " + crg_file);
    }
    
    // Apply (default) modifiers.
    crgDataSetModifiersApply(data_set_id_);
}

OpenCRG::~OpenCRG() {
    crgDataSetRelease(data_set_id_);

    // Release remaining data set list.
    crgMemRelease();
}

std::tuple<double, double> OpenCRG::ConvertXYtoUV(const double x, const double y) {
    // Create a contact point.
    int cp_id = crgContactPointCreate(data_set_id_);

    // Perform the conversion.
    std::tuple<double, double> retval;
    int result = crgEvalxy2uv(cp_id, x, y, &std::get<0>(retval), &std::get<1>(retval));
    crgContactPointDelete(cp_id);
    
    if(result == 0) {
        throw std::runtime_error("Could not convert xy (" + std::to_string(x) + "," + std::to_string(y) + ") to uv");
    }
    return retval;
}

std::tuple<double, double> OpenCRG::ConvertUVtoXY(const double u, const double v) {
    // Create a contact point.
    int cp_id = crgContactPointCreate(data_set_id_);

    // Perform the conversion.
    std::tuple<double, double> retval;
    int result = crgEvaluv2xy(cp_id, u, v, &std::get<0>(retval), &std::get<1>(retval));
    crgContactPointDelete(cp_id);

    if(result == 0) {
        throw std::runtime_error("Could not convert uv (" + std::to_string(u) + "," + std::to_string(v) + ") to xy");
    }

    return retval;
}

std::tuple<double, double> OpenCRG::GetHeadingAndCurvatureAtXY(const double x, const double y) {
    // Create a contact point.
    int cp_id = crgContactPointCreate(data_set_id_);

    // Perform the conversion.
    std::tuple<double, double> retval;
    int result = crgEvalxy2pk(cp_id, x, y, &std::get<0>(retval), &std::get<1>(retval));
    crgContactPointDelete(cp_id);
    
    if(result == 0) {
        throw std::runtime_error("Could not get heading and curvature at xy(" + std::to_string(x) + "," + std::to_string(y) + ")");
    }
    return retval;
}

std::tuple<double, double> OpenCRG::GetHeadingAndCurvatureAtUV(const double u, const double v) {
    // Create a contact point.
    int cp_id = crgContactPointCreate(data_set_id_);

    // Perform the conversion.
    std::tuple<double, double> retval;
    int result = crgEvaluv2pk(cp_id, u, v, &std::get<0>(retval), &std::get<1>(retval));
    crgContactPointDelete(cp_id);

    if(result == 0) {
        throw std::runtime_error("Could not get heading and curvature at uv(" + std::to_string(u) + "," + std::to_string(v) + ")");
    }

    return retval;
}
}