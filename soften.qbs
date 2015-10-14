import qbs

CppApplication {
    type: "application" // To suppress bundle generation on Mac
    consoleApplication: true
    files: [
        "src/core/bridge.h",
        "src/core/metaobject.h",
        "src/core/object.cpp",
        "src/core/object.h",
        "src/engine/context.cpp",
        "src/engine/context.h",
        "src/engine/engine.cpp",
        "src/engine/engine.h",
        "src/engine/handle.cpp",
        "src/engine/handle.h",
        "src/engine/scope.cpp",
        "src/engine/scope.h",
        "src/soften.h",
        "test/main.cpp",
        "test/test-object-call/myobject.cpp",
        "test/test-object-call/myobject.h",
    ]

    cpp.cxxFlags:"-std=c++11"

    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}

