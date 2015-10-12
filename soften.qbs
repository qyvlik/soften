import qbs

CppApplication {
    type: "application" // To suppress bundle generation on Mac
    consoleApplication: true
    files: [
        "test/main.cpp",
        "src/metaobject.cpp",
        "src/metaobject.h",
        "src/object.cpp",
        "src/object.h",
        "src/soften.h",
    ]

    cpp.cxxFlags:"-std=c++11"

    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}

