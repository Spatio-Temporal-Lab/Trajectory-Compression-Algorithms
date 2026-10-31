#include "algorithm/cost_compressor.h"
#include <fstream>
#include <iostream>
#include <vector>

int main() {
    std::ifstream in("sample_input.txt");
    if (!in) { std::cerr << "无法打开 sample_input.txt\n"; return 1; }
    std::vector<CoSTCompressor::GpsPoint> points;
    double lon, lat; unsigned long long ts;
    while (in >> lon >> lat >> ts)
        points.emplace_back(lon, lat, static_cast<uint64_t>(ts));
    if (points.size() < 2) { std::cerr << "测试数据不足\n"; return 1; }

    CoSTCompressor compressor(10000, 1e-5);
    for (const auto& p : points) compressor.AddGpsPoint(p);
    compressor.Close();
    Array<uint8_t> encoded = compressor.GetCompressedData();
    std::ofstream out("sample_output.cost", std::ios::binary);
    out.write(reinterpret_cast<const char*>(encoded.begin()), encoded.length());
    out.close();

    std::cout << "CoST测试通过\n";
    std::cout << "输入点数: " << points.size() << "\n";
    std::cout << "编码大小: " << encoded.length() << " bytes\n";
    std::cout << "压缩率(编码大小/原始文本大小): "
              << static_cast<double>(encoded.length()) /  
                 static_cast<double>(std::ifstream("sample_input.txt", std::ios::binary).seekg(0, std::ios::end).tellg())
              << "\n";
    return 0;
}
