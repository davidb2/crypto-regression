cc_binary(
    name = "main",
    srcs = [
        "main.cc",
    ],
    deps = [
        "@com_github_gflags_gflags//:gflags",
        ":gdax",
    ],
)

cc_library(
    name = "gdax",
    hdrs = [
        "client.h",
        "manager.h",
        "server.h",
        "types.h",
    ],
    srcs = [
        "client.cc",
        "manager.cc",
        "server.cc",
    ],
    deps = [
        "@websocketpp//:websocketpp",
        "@json//:json",
    ],
    linkopts = [
        "-lboost_system",
        "-lcrypto",
        "-lssl",
    ],
)
