#include <benchmark/benchmark.h>

#include <mutex>
#include <system_error>
#include <cstring>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

class Logger {
public:
    Logger(const std::string& path) : buff(10000) {
        fd_ = ::open(path.c_str(), O_CREAT | O_APPEND | O_WRONLY | O_TRUNC, 0644);
        if (fd_ == -1) {
            throw std::system_error(errno, std::system_category(), "open");
        }
    }

    void flush() {
        if (::write(fd_, buff.data(), size) != static_cast<ssize_t>(size)) {
            throw std::system_error(errno, std::system_category(), "write");
        }
        size = 0;
    }

    ~Logger() {
        flush();
        if (fd_ != -1) {
            ::close(fd_);
            fd_ = -1;
        }
    }

    void Write(const std::string& msg) {
        if (size + msg.size() >= buff.size()) {
            flush();
        }
        std::memcpy(buff.data() + size, msg.data(), msg.size());
        size += msg.size();
    }

private:
    std::mutex mtx;
    std::vector<char> buff;
    size_t size = 0;
    int fd_ = -1;
};

static Logger TestLogger{"/tmp/benchmark_logger"};

void BM_Logger(benchmark::State& state) {
    for (auto _ : state) {
        TestLogger.Write("Test Message\n");
    }
}

BENCHMARK(BM_Logger)
    ->Threads(4);

BENCHMARK_MAIN();
