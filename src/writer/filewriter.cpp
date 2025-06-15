#include "filewriter.hpp"

namespace metrics
{
    FileWriter::FileWriter(const std::string& filename): _filename(filename), _file(filename) {
        if(!_file.is_open()) {
            _file.close();
            throw std::runtime_error("Can`t open file");
        }
    }

    void FileWriter::write(const std::string& log) {
        if(!_file.is_open()) throw std::runtime_error("Can`t open file");
        _file<<log<<'\n';
    }

    std::unique_ptr<IWriter> FileWriter::clone() const {
        return std::make_unique<FileWriter>(_filename);
    }

    FileWriter::~FileWriter() {
        _file.close();
    }
}