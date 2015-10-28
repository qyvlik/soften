import qbs

CppApplication {
    type: "application" // To suppress bundle generation on Mac
    consoleApplication: true
    files: [
        "src/core/basetypebridge.h",
        "src/core/bridge.h",
        "src/core/bridge.cpp",
        "src/core/functionmeta.h",
        "src/core/metacall.h",
        "src/core/object.cpp",
        "src/core/object.h",
        "src/engine/assembler.cpp",
        "src/engine/assembler.h",
        "src/soften.h",
        // "test/function_meta/function_meta.h",
        "test/main.cpp",
        "test/polymorphism/myobject.cpp",
        "test/polymorphism/myobject.h",
        "test/polymorphism/myobjectchild.cpp",
        "test/polymorphism/myobjectchild.h",
    ]

    cpp.cxxFlags:"-std=c++11"

    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}

