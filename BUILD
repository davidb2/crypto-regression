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
