import qbs

CppApplication {
    type: "application" // To suppress bundle generation on Mac
    consoleApplication: true
    files: [
        "src/bridge.h",
        "src/objectmetacall.h",
        "src/sobject.cpp",
        "src/sobject.h",
        "src/variant.h",
        "test/main.cpp",
        "test/myobject.cpp",
        "test/myobject.h",
        "test/objectfactory.h",
    ]

    cpp.defines: {
        if(qbs.buildVariant == "debug") {
            return "QBS_DEBUG";
        } else {
            // release
            return "QBS_RELEASE";
        }
    }

    cpp.cxxFlags:"-std=c++11"

    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}

