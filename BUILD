cc_binary(
    name = "kmp",
    srcs = [
        "src/main.cc",
    ],
    deps = [
        "@com_github_gflags_gflags//:gflags",
        "@boost//:algorithm",
    ],
)

cc_binary(
    name = "echo",
    srcs = [
        "echo_client.cpp",
    ],
    deps = [
        "@com_github_gflags_gflags//:gflags",
        "@websocketpp//:websocketpp",
        "@json//:json",
    ],
    linkopts = [
        "-lboost_system",
    ],
)

cc_library(
    name = "gdax",
    hdrs = [
        "backend/client.h",
        "backend/server.h",
        "backend/types.h",
    ],
    srcs = [
        "backend/server.cc",
        "backend/client.cc",
    ],
    deps = [
        "@com_github_gflags_gflags//:gflags",
        "@websocketpp//:websocketpp",
        "@json//:json",
    ],
    linkopts = [
        "-lboost_system",
    ],
)
