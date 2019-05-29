CATCH2_BUILD = """
cc_library(
    name = "catch2",
    hdrs = glob(
        include = ["single_include/catch2/**/*.h", "single_include/catch2/**/*.hpp"],
    ),
    strip_include_prefix = "single_include",
    visibility = ["//visibility:public"],
)
"""

WEBSOCKETPP_BUILD = """
cc_library(
    name = "websocketpp",
    hdrs = glob(
        include = ["websocketpp/**/*.h", "websocketpp/**/*.hpp"],
    ),
    include_prefix = "",
    visibility = ["//visibility:public"],
)
"""

new_git_repository(
    name = "catch2",
    remote = "https://github.com/catchorg/Catch2.git",
    tag = "v2.6.1",
    build_file_content = CATCH2_BUILD,
)

new_git_repository(
    name = "websocketpp",
    remote = "https://github.com/zaphoyd/websocketpp.git",
    tag = "0.8.1",
    build_file_content = WEBSOCKETPP_BUILD,
)

git_repository(
    name = "com_github_nelhage_rules_boost",
    commit = "6d6fd834281cb8f8e758dd9ad76df86304bf1869",
    remote = "https://github.com/nelhage/rules_boost",
)

git_repository(
    name = "com_github_gflags_gflags",
    remote = "https://github.com/gflags/gflags.git",
    tag = "v2.2.2",
)

load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
boost_deps()
