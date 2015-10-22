import qbs

CppApplication {
    type: "application" // To suppress bundle generation on Mac
    consoleApplication: true
    files: [
        "src/core/basetypebridge.h",
        "src/core/bridge.h",
        "src/core/metaobject.h",
        "src/core/metacall.h",
        "src/core/object.cpp",
        "src/core/object.h",
        "src/soften.h",
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

