#include <string>
#include <tuple>

namespace opencrg {
class OpenCRG{
    public:
    OpenCRG(const std::string& crg_file);
    ~OpenCRG();
    std::tuple<double, double> ConvertXYtoUV(double x, double y);
    std::tuple<double, double> ConvertUVtoXY(double u, double v);
    std::tuple<double, double> GetHeadingAndCurvatureAtXY(double x, double y);
    std::tuple<double, double> GetHeadingAndCurvatureAtUV(double u, double v);
    
    private:
    int data_set_id_;
};
}