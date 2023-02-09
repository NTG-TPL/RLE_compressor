#pragma once

#include <string>
#include <fstream>

inline bool DecodeRLE(const std::string& src_name, const std::string& dst_name){
     using namespace std;

    ifstream in(src_name, ios::binary);
    if (!in) {
        return false;
    }

    ofstream out(dst_name, ios::binary);
    if (!out) {
        return false;
    }

    do {

        unsigned char header;
        auto b0 = in.get();
        if (b0 == std::istream::traits_type::eof()) {
            break;
        }
        header = static_cast<unsigned char>(b0);

        size_t size = (header >> 1) + 1;
        if (header & 0x01){ // компрессия
             auto ch = in.get();

            std::string buffer(size, ch);
            out.write(buffer.data(), buffer.size());

        }else{ // без компрессии

            char buff[128];
            in.read(buff, size);
            size_t read = in.gcount();
            out.write(buff, read);
        }

    } while (in);
    in.close();
    out.close();

    return true;
}
