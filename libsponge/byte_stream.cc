#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity):
    _buffer(),
    _buffer_capacity(capacity),
    _buffer_present_size(0),
    _written_size(0),
    _read_size(0),
    _input_ended_flag(false),
    _error(false) {}

size_t ByteStream::write(const string &data) {
    size_t len = min(data.size(), remaining_capacity());
    for (size_t i = 0; i < len; i++) {
        _buffer.push_back(data[i]);
    }
    _buffer_present_size += len;
    _written_size += len;
    return len;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    return string(_buffer.begin(), _buffer.begin() + min(len, _buffer_present_size));
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    _buffer_present_size -= len;
    _read_size += len;
    _buffer.erase(_buffer.begin(), _buffer.begin() + len);
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    size_t read_len = min(len, _buffer_present_size);
    string ret = peek_output(read_len);
    pop_output(read_len);
    return ret;
}

void ByteStream::end_input() {
    _input_ended_flag = true;
}

bool ByteStream::input_ended() const { return _input_ended_flag; }

size_t ByteStream::buffer_size() const { return _buffer_present_size; }

bool ByteStream::buffer_empty() const { return _buffer_present_size == 0; }

bool ByteStream::eof() const { return input_ended() && buffer_empty(); }

size_t ByteStream::bytes_written() const { return _written_size; }

size_t ByteStream::bytes_read() const { return _read_size; }

size_t ByteStream::remaining_capacity() const { return _buffer_capacity - _buffer_present_size; }
