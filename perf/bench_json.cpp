#include <benchmark/benchmark.h>

#include <sstream>

struct User {
    int64_t id;
    std::string username;
};

std::string ToJson(const User& user) {
    return std::string("{") +
           "\"id\":" + std::to_string(user.id) + "," +
           "\"username\":\"" + user.username + "\"" +
           "}";
}

struct Message {
    int64_t id;
    std::string subject;
    std::string body;

    User from, to;
};

// DO NOT change signature of this function.
// You may change signature of other functions.
std::string ToJson(const Message& msg) {
    return "{\"id\":" + std::to_string(msg.id) + ",\"subject\":\"" + msg.subject + "\",\"body\":\"" + msg.body + "\",\"from\":" + ToJson(msg.from) + ",\"to\":" + ToJson(msg.to) + "}";
}

void BM_MessageToJson(benchmark::State& state) {
    Message msg{
        1000,
        "About modules",
        "So, when is that 'modules' proposal coming?",
        User{12345, "Herb Sutter"},
        User{1, "Biern Stroustrup"}};

    for (auto _ : state) {
        benchmark::DoNotOptimize(ToJson(msg));
    }

    auto json = ToJson(msg);
    std::string expected = R"({"id":1000,"subject":"About modules","body":"So, when is that 'modules' proposal coming?","from":{"id":12345,"username":"Herb Sutter"},"to":{"id":1,"username":"Biern Stroustrup"}})";
    if (json != expected) {
        state.SkipWithError("Wrong output");
    }
}

BENCHMARK(BM_MessageToJson);

BENCHMARK_MAIN();
